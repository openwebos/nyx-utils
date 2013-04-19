// @@@LICENSE
//
//      Copyright (c) 2012 Hewlett-Packard Development Company, L.P.
//      Copyright (c) 2013 LG Electronics, Inc.
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
	ostringstream usage;
	usage << "COMMAND" << endl;
	usage << left << "  " << setw(30) << "system_reboot [ARGS]" << setw(30)
	      << "Reboots the device" << endl;
	usage << setw(32) << "  " << setw(50) << "If [ARGS] is not set, defaults to"
	      << endl;
	usage << setw(32) << "  " << setw(30) << "'NYX_SYSTEM_NORMAL_SHUTDOWN'"
	      << endl;
	usage << "  " << setw(30) << "system_shutdown [ARGS]" << setw(30)
	      << "Shuts down the device" << endl;
	usage << setw(32) << "  " << setw(50) << "If [ARGS] is not set, defaults to"
	      << endl;
	usage << setw(32) << "  " << setw(30) << "'NYX_SYSTEM_NORMAL_SHUTDOWN'"
	      << endl;
	usage << "ARGS" << endl;
	usage << "  " << setw(30) << "NYX_SYSTEM_NORMAL_SHUTDOWN"  << setw(30)
	      << "Normal shutdown" << endl;
	usage << "  " << setw(30) << "NYX_SYSTEM_EMERG_SHUTDOWN"  << setw(30)
	      << "Emergency shutdown" << endl;
	usage << "  " << setw(30) << "NYX_SYSTEM_TEST_SHUTDOWN"  << setw(30)
	      << "Test shutdown" << endl;
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
	else if(commandName == "system_shutdown")
	{
		return new NyxCmdSystemShutdown();
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


