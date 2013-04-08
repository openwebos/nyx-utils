// @@@LICENSE
//
//      Copyright (c) 2013 LG Electronics
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

#include "nyx_cmd_os_info_query.h"

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <map>
#include <getopt.h>

using namespace std;

/*
* Class constructor
*/

NyxCmdOSInfoQuery::NyxCmdOSInfoQuery()
{
}

/*
* Command usage description as a string.
*/
string NyxCmdOSInfoQuery::Description()
{
	return string("Returns OS information");
}

/*
* Command name as it will be written on the command line.
*/
string NyxCmdOSInfoQuery::Name()
{
	return string("query");
}

/*
* Execute command.
* Resolves command parameters from the command line arguments.
*/
int NyxCmdOSInfoQuery::Execute(const char *deviceId, int argc, char **argv)
{
	nyx_device_handle_t device = NULL;
	nyx_os_info_query_t infoType;
	nyx_error_t error = NYX_ERROR_GENERIC;

	bool argSuccess = resolveArguments(argc, argv, &infoType);

	if(argSuccess)
	{
		error = nyx_init();

		if(NYX_ERROR_NONE == error)
		{
			error = nyx_device_open(NYX_DEVICE_OS_INFO, deviceId, &device);

			if(NULL != device)
			{
				const char* retVal;

				error = nyx_os_info_query(device, infoType, &retVal);

				switch(error)
				{
					case NYX_ERROR_NONE:
						cout << retVal << endl;
						break;
					case NYX_ERROR_NOT_IMPLEMENTED:
						cerr << "Error: Query not implemented" << endl;
						break;
					case NYX_ERROR_DEVICE_UNAVAILABLE:
						cerr << "Error: Device or value not available" << endl;
						break;
					default:
						cerr << "Error: Error " << error << " in executing query" << endl;
						break;
				}

				nyx_device_close(device);
			}
		}
		else
		{
			cerr << "Error: Error initializing Nyx" << endl;
		}

		nyx_deinit();

	}

	return (NYX_ERROR_NONE == error)? 0 : -1;
}

/*
* Parses the command line arguments and resolves them to proper variables.
* If return value is 'false', query might not hold a valid value.
*/
bool NyxCmdOSInfoQuery::resolveArguments(int argc, char **argv, nyx_os_info_query_t *query)
{
	bool retVal = true;
	const map<string,commandUsage> queryArgs =  queryArgsTable::initialize();

	if (optind < argc && NULL != query)
	{
		//Arguments
		char *argumentStr = argv[optind++];

		// get the iterator
		map<string, commandUsage>::const_iterator iter = queryArgs.find(string(argumentStr));

		if (queryArgs.end() != iter)
		{
			*query = iter->second.commandEnum;
			retVal = true;
		}
		else
		{
			cerr << "Error: Unknown argument" << endl;
			retVal = false;
		}
	}
	else
	{
		cerr << "Error: Not enough arguments" << endl;
		retVal = false;
	}

	return retVal;
}
