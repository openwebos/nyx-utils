// @@@LICENSE
//
//      Copyright (c) 2012-2013 LG Electronics, Inc.
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
#include "nyx_cmd_system_shutdown.h"
#include "nyx_cmd_system_erase.h"

#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// Name of the device type
string NyxCmdSystem::Name()
{
	return string("System");
}

// Human readable description of the device type.
string NyxCmdSystem::Description()
{
	return string("Nyx 'System' device type.");
}

//! [Usage info]
// Usage information for the device type.
string NyxCmdSystem::Usage()
{
    const char * const usage =
        "COMMAND\n"
        "  system_reboot [ARGS]          Reboots the device\n"
        "                                If [ARGS] is not set, defaults to\n"
        "                                'NYX_SYSTEM_NORMAL_SHUTDOWN'\n"
        "  system_shutdown [ARGS]        Shuts down the device\n"
        "                                If [ARGS] is not set, defaults to\n"
        "                                'NYX_SYSTEM_NORMAL_SHUTDOWN'\n"
        "  erase_parition TYPE           Mark one or more partitions to be\n"
        "                                erased on the next reboot\n"
        "\n"
        "ARGS\n"
        "  NYX_SYSTEM_NORMAL_SHUTDOWN    Normal shutdown\n"
        "  NYX_SYSTEM_EMERG_SHUTDOWN     Emergency shutdown\n"
        "  NYX_SYSTEM_TEST_SHUTDOWN      Test shutdown\n"
        "\n"
        "TYPE\n"
        "  media                         Erase user created files, including photos and videos\n"
        "  var                           Erase installed apps and all app settings and data\n"
        "  all                           Full erase (factory reset)\n"
        "  developer                     Erase developer data\n"
        ;

	return string(usage);
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
	else if(commandName == "system_shutdown")
	{
		return new NyxCmdSystemShutdown();
	}
    else if(commandName == "erase_partition")
    {
        return new NyxCmdSystemErase();
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


