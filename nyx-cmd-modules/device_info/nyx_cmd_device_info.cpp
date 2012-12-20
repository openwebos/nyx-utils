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

#include "nyx_cmd_device_info.h"
#include "nyx_cmd_device_info_get_info.h"

#include <string>
#include <sstream>

using namespace std;

static string nameStr = "DeviceInfo";
static string descriptionStr = "Nyx 'Device Info' device type.";

// Name of the device type
string NyxCmdDeviceInfo::Name()
{
	return nameStr;
}

// Usage information for the device type.
string NyxCmdDeviceInfo::Usage()
{
	ostringstream usage;
	usage << "COMMAND" << endl;
	usage << "  get [GET_ARGS]\t\tGet device information" << endl;
	usage << "GET_ARGS" << endl;
	usage << "  nduid\t\t\t\tReturn device NDUID" << endl;
	usage << "  name\t\t\t\tReturn device name" << endl;
	return usage.str();
}


// Human readable description of the device type.
string NyxCmdDeviceInfo::Description()
{
	return descriptionStr;
}

/*
* Returns the command object instance by for defined name.
* Implemented command names and their class initiations are added here.
*/
NyxCmdCommand* NyxCmdDeviceInfo::getCommand(string commandName)
{
	if(commandName == "get")
	{
		return new NyxCmdDeviceInfoGetInfo();
	}

	return NULL;
}

extern "C"
{
	NyxCmdDeviceType* getNyxCmdDeviceTypeInstance()
	{
		return new NyxCmdDeviceInfo();
	}
}


