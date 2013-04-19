// @@@LICENSE
//
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

#ifndef __NYXCMDOSINFOQUERY_H__
#define __NYXCMDOSINFOQUERY_H__

/**
 * @file nyx_cmd_os_info_query.h
 *
 * @brief Implementation class for nyx-cmd OS info device type query command.
 *
 */

#include <string>
#include <map>
#include <nyx/nyx_client.h>
#include <nyx/common/nyx_device.h>

#include "nyx_cmd_command.h"
#include "nyx_cmd_os_info.h"

struct queryArgsTable
{
	static const std::map<std::string,commandUsage> initialize()
	{
		const std::map<std::string,commandUsage> queryArgsMap;
		queryArgsMap["core_os_kernel_config"] = commandUsage(NYX_OS_INFO_CORE_OS_KERNEL_CONFIG, "Return webOS kernel config");
		queryArgsMap["core_os_kernel_version"] = commandUsage(NYX_OS_INFO_CORE_OS_KERNEL_VERSION, "Return webOS kernel version info");
		queryArgsMap["core_os_name"] = commandUsage(NYX_OS_INFO_CORE_OS_NAME, "Return Core OS name");
		queryArgsMap["core_os_release"] = commandUsage(NYX_OS_INFO_CORE_OS_RELEASE, "Return Core OS release info");
		queryArgsMap["core_os_release_codename"] = commandUsage(NYX_OS_INFO_CORE_OS_RELEASE_CODENAME, "Return Core OS release codename");
		queryArgsMap["webos_api_version"] = commandUsage(NYX_OS_INFO_WEBOS_API_VERSION, "Return webOS API version");
		queryArgsMap["webos_build_id"] = commandUsage(NYX_OS_INFO_WEBOS_BUILD_ID, "Return webOS build ID");
		queryArgsMap["webos_imagename"] = commandUsage(NYX_OS_INFO_WEBOS_IMAGENAME, "Return webOS imagename");
		queryArgsMap["webos_name"] = commandUsage(NYX_OS_INFO_WEBOS_NAME, "Return webOS name");
		queryArgsMap["webos_prerelease"] = commandUsage(NYX_OS_INFO_WEBOS_PRERELEASE, "Return webOS prerelease info");
		queryArgsMap["webos_release"] = commandUsage(NYX_OS_INFO_WEBOS_RELEASE, "Return webOS release info");
		queryArgsMap["webos_release_codename"] = commandUsage(NYX_OS_INFO_WEBOS_RELEASE_CODENAME, "Return webOS release codename");
		return queryArgsMap;
	}
};


class NyxCmdOSInfoQuery : public NyxCmdCommand
{
/**
* @defgroup nyx_cmd_os_info_query nyx-cmd OS info device type query command
* @ingroup nyx_cmd_os_info_module
* @{
*/
	private:
/**
 * Resolve arguments given to Execute function.
 *
 * @param[in]   argc - number of arguments
 * @param[in]   argv - list of arguments
 * @param[out]  query - OS info query value
 *
 * @return true if known argument found
 *
 */
		bool resolveArguments(int argc, char **argv, nyx_os_info_query_t * query);
	public:
/**
 * Class constructor.
 *
 */
		NyxCmdOSInfoQuery(void);
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
 * @return -1 if error.
 *
 */
		int Execute(const char *deviceId, int argc, char** argv);
/** @} */
};

#endif // __NYXCMDOSINFOQUERY_H__
