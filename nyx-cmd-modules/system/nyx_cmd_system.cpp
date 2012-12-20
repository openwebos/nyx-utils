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

#include "nyx_cmd_system.h"
#include "nyx_cmd_system_reboot.h"

#include <string>
#include <sstream>

using namespace std;

static string nameStr = "System";
static string descriptionStr = "Nyx 'System' device type.";


// Name of the device type
string NyxCmdSystem::Name()
{
	return nameStr;
}

// Human readable description of the device type.
string NyxCmdSystem::Description()
{
	return descriptionStr;
}

//! [Usage info]
// Usage information for the device type.
string NyxCmdSystem::Usage()
{
	ostringstream usage;
	usage << "COMMAND" << endl;
	usage << "  system_reboot [REBOOT_ARGS]\tReboots the device" << endl;
	usage << "\t\t\t\tIf [REBOOT_ARGS] is not set, defaults to" << endl;
	usage << "\t\t\t\t'NYX_SYSTEM_NORMAL_SHUTDOWN'" << endl;
	usage << "REBOOT_ARGS" << endl;
	usage << "  NYX_SYSTEM_NORMAL_SHUTDOWN\tNormal shutdown" << endl;
	usage << "  NYX_SYSTEM_EMERG_SHUTDOWN\tEmergency shutdown" << endl;
	usage << "  NYX_SYSTEM_TEST_SHUTDOWN\tTest shutdown" << endl;
	return usage.str();
}
//! [Usage info]

/*
* Returns the command object instance by for defined name.
* Implemented command names and their class initiations are added here.
*/
NyxCmdCommand* NyxCmdSystem::getCommand(string commandName)
{
	if(commandName == "system_reboot")
	{
		return new NyxCmdSystemReboot();
	}

	return NULL;
}

extern "C"
{
	NyxCmdDeviceType* getNyxCmdDeviceTypeInstance()
	{
		return new NyxCmdSystem();
	}
}


