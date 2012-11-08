// @@@LICENSE
//
//      Copyright (c) 2012 Hewlett-Packard Development Company, L.P.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// LICENSE@@@

#include <stdio.h>
#include <getopt.h>
#include <dlfcn.h>

#include <cstdlib>
#include <map>
#include <string>
#include <iostream>

#include "nyx_cmd_devicetype.h"

#include <nyx/nyx_client.h>
#include <nyx/common/nyx_device.h>

#ifndef NYXCMD_LIB_DIR
#error nyx-cmd library directory not defined!
#endif

#ifndef NYXCMD_VERSION_INFO
#error nyx-cmd version info not defined!
#endif

using namespace std;

static char *deviceId = NULL;
static const char *defaultDevId = "Main";

static bool versionQuery = false;

static nyx_device_handle_t device = NULL;
static nyx_system_shutdown_type_t argument;

static void usage(void)
{
	printf("usage:\n");
	printf("nyx-cmd [OPTION] [DEVICE-TYPE [COMMAND [ARGS]...]]\n");
	printf("OPTION\n\tOptional arguments\n");
	printf("\t-v, --version\n\t\tDisplay version of nyx-cmd when no other arguments are present\n");
	printf("\t\tDisplay version of device type module when DEVICE-TYPE is specified\n");
	printf("\t-i, --id\n\t\tSet the device identifier (e.g. -iMyDevId)\n");
	printf("\t\tUnless specified, uses 'Main'\n");
	printf("DEVICE-TYPE\n");
	printf("\tE.g. System\n");
	printf("COMMAND\n");
	printf("\tMaps onto one of the functions within the selected API (not all functions are supported). Requires a value for DEVICE-TYPE.\n");
	printf("ARGS\n");
	printf("\tCOMMAND specific argument lists\n");
	exit(EXIT_SUCCESS);
}

static void printVersion()
{
	fprintf(stderr, "%s\n", NYXCMD_VERSION_INFO);
}

char *resolveArguments(int argc, char **argv)
{
	int c;
	char *devType = NULL;

	static struct option long_options[] =
	{
		{"version", optional_argument, 0, 'v' },
		{"id", required_argument, 0, 'i' },
		{0, 0, 0, 0 }
	};

	if (argc < 2) // Not enough arguments, minimum command is "nyx-cmd [OPTION]"
	{
		// calling usage exits the program
		usage();
	}

	while (1)
	{
		int option_index = 0;

		c = getopt_long(argc, argv, "vi:?", long_options, &option_index);

		if (c == -1)
		{
			break;
		}

		switch (c)
		{
			case 'i':
				deviceId = optarg;
				break;
			case 'v':
				versionQuery = true;
				break;
			case '?':
				usage();
				break;
		}

	} //while(1)

	if (optind < argc)
	{
		//Device type
		devType = argv[optind++];
	}

	// initialize 'deviceId' if not found in parameters
	if (NULL == deviceId)
	{
		deviceId = const_cast<char*>(defaultDevId);
	}

	return devType;
}


int main(int argc, char **argv)
{
	int retVal = -1;
	char *devType = resolveArguments(argc, argv);

	// Resolve all libraries. Load the device type which name is specified in the arguments.
	// Call execute for that library.
	map<string, string> deviceTypes;

	if(devType)
	{
		char *error;
		void *lib_handle;
		NyxCmdDeviceType* devTypeInstance = NULL;
		NyxCmdDeviceType* (*initialize)(void);

		//create the library path and name
		string libName(NYXCMD_LIB_DIR);
		libName.append("/");
		libName.append("libNyxCmdModule");
		libName.append(devType);
		libName.append(".so");

		lib_handle = dlopen( libName.c_str(), RTLD_LAZY);

		if (lib_handle)
		{
			//Clear the error log
			dlerror();

			// Get pointer to Instance creation function.
			// The funtion name is used to identify that we are dealing with
			// the type of library we are interested in.
			initialize = (NyxCmdDeviceType* (*)(void)) dlsym( lib_handle, "getNyxCmdDeviceTypeInstance" );

			if (initialize)
			{
				try
				{
					devTypeInstance = (*initialize)();
					if (versionQuery)
					{
						cout << devTypeInstance->Version() << endl;
					}
					else
					{
						devTypeInstance->executeCommand(deviceId, argc, argv);
					}

					// either version query or command, it was still successful
					retVal = 0;

				} catch (...)
				{
					cout << "Error executing command." << endl;
				}

				if(devTypeInstance)
					delete devTypeInstance;
			}
			else
			{
				cerr << error << endl;
			}

			dlclose(lib_handle);
		}
		else
		{
			cerr << "Error opening the library" << endl;
		}
	}
	else
	{
		if(versionQuery)
			printVersion();
		else
			cout << "No available device types" << endl;
	}

	return retVal;
}
