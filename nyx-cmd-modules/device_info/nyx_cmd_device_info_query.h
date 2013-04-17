// @@@LICENSE
//
//      Copyright (c) 2012 Hewlett-Packard Development Company, L.P.
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

#ifndef __NYXCMDDEVICEINFOQUERY_H__
#define __NYXCMDDEVICEINFOQUERY_H__

/**
 * @file nyx_cmd_device_info_query.h
 *
 * @brief Implementation class for nyx-cmd Device info device type query command.
 *
 */

#include <string>
#include <map>
#include <nyx/nyx_client.h>
#include <nyx/common/nyx_device.h>

#include "nyx_cmd_command.h"
#include "nyx_cmd_device_info.h"

struct queryArgsTable
{
	static const std::map<std::string,commandUsage> initialize()
	{
		const std::map<std::string,commandUsage> getArgsMap;
		getArgsMap["board_type"] = commandUsage(NYX_DEVICE_INFO_BOARD_TYPE, "Return board type");
		getArgsMap["bt_addr"] = commandUsage(NYX_DEVICE_INFO_BT_ADDR, "Return BT address");
		getArgsMap["device_name"] = commandUsage(NYX_DEVICE_INFO_DEVICE_NAME, "Return name");
		getArgsMap["hardware_id"] = commandUsage(NYX_DEVICE_INFO_HARDWARE_ID, "Return hardware ID");
		getArgsMap["hardware_revision"] = commandUsage(NYX_DEVICE_INFO_HARDWARE_REVISION, "Return hardware revision");
		getArgsMap["installer"] = commandUsage(NYX_DEVICE_INFO_INSTALLER, "Return installer");
		getArgsMap["keyboard_type"] = commandUsage(NYX_DEVICE_INFO_KEYBOARD_TYPE, "Return keyboard type");
		getArgsMap["modem_present"] = commandUsage(NYX_DEVICE_INFO_MODEM_PRESENT, "Return modem availability");
		getArgsMap["nduid"] = commandUsage(NYX_DEVICE_INFO_NDUID, "Return NDUID");
		getArgsMap["product_id"] = commandUsage(NYX_DEVICE_INFO_PRODUCT_ID, "Return product ID");
		getArgsMap["radio_type"] = commandUsage(NYX_DEVICE_INFO_RADIO_TYPE, "Return radio type");
		getArgsMap["ram_size"] = commandUsage(NYX_DEVICE_INFO_RAM_SIZE, "Return RAM size");
		getArgsMap["serial_number"] = commandUsage(NYX_DEVICE_INFO_SERIAL_NUMBER, "Return serial number");
		getArgsMap["storage_free"] = commandUsage(NYX_DEVICE_INFO_STORAGE_FREE, "Return free storage size");
		getArgsMap["storage_size"] = commandUsage(NYX_DEVICE_INFO_STORAGE_SIZE, "Return storage size");
		getArgsMap["wifi_addr"] = commandUsage(NYX_DEVICE_INFO_WIFI_ADDR, "Return WiFi MAC address");
		return getArgsMap;
	}
};

class NyxCmdDeviceInfoQuery : public NyxCmdCommand
{
/**
* @defgroup nyx_cmd_device_info_query nyx-cmd Device info device type query command
* @ingroup nyx_cmd_device_info_module
* @{
*/
	private:
/**
 * Resolve arguments given to Execute function.
 *
 * @param[in]   argc - number of arguments
 * @param[in]   argv - list of arguments
 * @param[out]  type - Type of information queried if function successful
 *
 * @return true if 'type' was set, false if not
 *
 */
		bool resolveArguments(int argc, char **argv, nyx_device_info_type_t *type);
	public:
/**
 * Class constructor.
 *
 */
		NyxCmdDeviceInfoQuery(void);
/**
 * Get the description of the command functionality.
 *
 * @return String containing description of the functionality.
 *
 */
		std::string Description();

/**
 * Get the name for command. This will be compared against the command line arguments
 *
 * @return String containing command name.
 *
 */
		std::string Name();

/**
 * Execute the command. Full argument list is expected.
 *
 * @param[in]   deviceId - device identifier
 * @param[in]   argc     - number of arguments
 * @param[in]   argv     - list of arguments
 *
 * @return -1 if error, 0 if no error.
 *
 */
		int Execute(const char *deviceId, int argc, char** argv);
/** @} */
};

#endif // __NYXCMDDEVICEINFOQUERY_H__
