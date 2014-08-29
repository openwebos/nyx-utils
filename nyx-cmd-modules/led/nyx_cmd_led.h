// @@@LICENSE
//
// Copyright (c) 2014 LG Electronics, Inc.
//
// Confidential computer software. Valid license from LG required for
// possession, use or copying. Consistent with FAR 12.211 and 12.212,
// Commercial Computer Software, Computer Software Documentation, and
// Technical Data for Commercial Items are licensed to the U.S. Government
// under vendor's standard commercial license.
//
// LICENSE@@@

#ifndef NYXCMDLED_H
#define NYXCMDLED_H

/**
 * @file nyx_cmd_led.h
 *
 * @brief Implementation class for nyx-cmd Led device type.
 *
 */

#include "nyx_cmd_devicetype.h"

#include <string>

class NyxCmdLed : public NyxCmdDeviceType
{
	/**
	* @defgroup nyx_cmd_led_module nyx-cmd Led module
	* @ingroup nyx_cmd_modules
	* @defgroup nyx_cmd_led_devicetype nyx-cmd Led device type implementation
	* @ingroup nyx_cmd_led_module
	* @{
	*/
protected:
	/**
	 * Get the correct command based on input string.
	 *
	 * @param[in]   cmdName - command name
	 *
	 * @return Pointer to the command
	 *
	 */
	NyxCmdCommand *getCommand(std::string cmdName);

public :
	/**
	 * Get the device type specific usage.
	 *
	 * @return Usage info for the device type
	 *
	 */
	std::string Usage(void);

	/**
	 * Get the device type specific name.
	 *
	 * @return Name for the device type
	 *
	 */
	std::string Name(void);

	/**
	 * Get the device type specific description.
	 *
	 * @return Description for the device type
	 *
	 */
	std::string Description(void);
	/** @} */
};

#endif // NYXCMDLED_H
