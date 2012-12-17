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

#include "nyx_cmd_command.h"
#include "nyx_cmd_device_info_get_info.h"

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <getopt.h>

using namespace std;

static string nameStr = "device_info_get_info";
static string descriptionStr =  "Returns device info.";

/*
* Class constructor
*/

NyxCmdDeviceInfoGetInfo::NyxCmdDeviceInfoGetInfo()
{
}

/*
* Command usage description as a string.
*/
string NyxCmdDeviceInfoGetInfo::Description()
{
	return descriptionStr;
}

/*
* Command name as it will be written on the command line.
*/
string NyxCmdDeviceInfoGetInfo::Name()
{
	return nameStr;
}

/*
* Execute command.
* Resolves command parameters from the command line arguments.
*/
int NyxCmdDeviceInfoGetInfo::Execute(const char *deviceId, int argc, char **argv)
{
	nyx_device_handle_t device = NULL;
	nyx_device_info_type_t infoType;
	nyx_error_t error = NYX_ERROR_NONE;

	infoType = resolveArguments(argc, argv);

	if(infoType != -1)
	{
		error = nyx_init();

		if(error == NYX_ERROR_NONE)
		{
			error = nyx_device_open(NYX_DEVICE_DEVICE_INFO, deviceId, &device);

			if(device != NULL)
			{
				// use NDUID_STRLEN as max length for any returned string
				char retVal[NOVACOM_NDUID_STRLEN];

				if(retVal)
				{
					error = nyx_device_info_get_info(device, infoType,
					                                 retVal, NOVACOM_NDUID_STRLEN);

					if(NYX_ERROR_NONE == error )
					{
						cout << retVal << endl;
					}
				}

				nyx_device_close(device);
			}
		}
		else
		{
			cerr << "Error initializing Nyx" << endl;
		}

		nyx_deinit();

	}

	if(error == NYX_ERROR_NONE)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

/*
* Parses the command line arguments and resolves them to proper variables.
*/
nyx_device_info_type_t NyxCmdDeviceInfoGetInfo::resolveArguments(int argc, char **argv)
{
	nyx_device_info_type_t retVal = (nyx_device_info_type_t) -1;

	if (optind < argc)
	{
		//Arguments
		char *argumentStr = argv[optind++];

		if( strcmp(argumentStr, "nduid") == 0)
		{
			retVal = NYX_DEVICE_INFO_NDUID;
		}
		else if( strcmp(argumentStr, "name") == 0 )
		{
			retVal = NYX_DEVICE_INFO_DEVICE_NAME;
		}
		else
		{
			cerr << "Unknown argument" << endl;
			retVal = (nyx_device_info_type_t) -1;
		}
	}
	else
	{
		cerr << "Not enough arguments" << endl;
		retVal = (nyx_device_info_type_t) -1;
	}


	return retVal;
}
