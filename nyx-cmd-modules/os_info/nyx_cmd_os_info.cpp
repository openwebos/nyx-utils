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

#include "nyx_cmd_os_info.h"
#include "nyx_cmd_os_info_query.h"

#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// Name of the device type
string NyxCmdOSInfo::Name()
{
	return string("OSInfo");
}

// Usage information for the device type.
string NyxCmdOSInfo::Usage()
{
	const map<string,commandUsage> queryArgs =  queryArgsTable::initialize();

	ostringstream usage;
	usage << "COMMAND" << endl;
	usage << left << "  " << setw(30) << "query QUERY" << setw(30) << "Returns OS information" << endl;
	usage << "QUERY" << endl;

	for(std::map<string, commandUsage>::const_iterator itr = queryArgs.begin(); itr != queryArgs.end(); ++itr)
	{
		usage << left << "  " << setw(30) <<  itr->first << setw(30) << itr->second.commandStr << endl;
	}

	return usage.str();
}

// Human readable description of the device type.
string NyxCmdOSInfo::Description()
{
	return string("Nyx 'OS Info' device type.");
}

/*
* Returns the command object instance by for defined name.
* Implemented command names and their class initiations are added here.
*/
NyxCmdCommand* NyxCmdOSInfo::getCommand(string commandName)
{
	if(commandName == "query")
	{
		return new NyxCmdOSInfoQuery();
	}

	return NULL;
}

extern "C"
{
	NyxCmdDeviceType* getNyxCmdDeviceTypeInstance()
	{
		return new NyxCmdOSInfo();
	}
}


