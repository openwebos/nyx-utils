# @@@LICENSE
#
#      Copyright (c) 2012 Hewlett-Packard Development Company, L.P.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# LICENSE@@@

cmake_minimum_required(VERSION 2.8.7)
project(nyx-utils CXX)

include(webOS/webOS)
include(FindPkgConfig)

webos_modules_init(1 0 0 QUALIFIER RC4)
webos_component(1 0 0 QUALIFIER RC2)

pkg_check_modules(NYXLIB REQUIRED nyx)
include_directories(${NYXLIB_INCLUDE_DIRS})
webos_add_compiler_flags(ALL ${NYXLIB_CFLAGS_OTHER})

function(nyx_get_pkgconfig_var varname nyx_pkgconfig_var usecache)
        execute_process(COMMAND ${PKG_CONFIG_EXECUTABLE} --variable=${nyx_pkgconfig_var} nyx
                        OUTPUT_VARIABLE pkgconfig_output
                        RESULT_VARIABLE pkgconfig_failed)

        if(NOT pkgconfig_failed)
                STRING(REGEX REPLACE "(/?\r?\n)+$" "" pkgconfig_output "${pkgconfig_output}")
                if(usecache)
                        set(${varname} ${pkgconfig_output} CACHE PATH ${nyx_pkgconfig_var})
                else()
                        set(${varname} ${pkgconfig_output} PARENT_SCOPE)
                endif()
        else()
                message(FATAL_ERROR "Error in fetching '${nyx_pkgconfig_var}' from nyx.pc, execute_process() returned ${pkgconfig_failed}")
        endif()
endfunction()

nyx_get_pkgconfig_var(NYX_CMD_MODULE_DIR nyx_cmd_module_dir TRUE)
set(NYX_CMD_MODULE_PREFIX "nyxcmdModule" CACHE STRING "Prefix for nyx-cmd modules")

add_definitions(-DNYX_CMD_MODULE_DIR="${NYX_CMD_MODULE_DIR}")
add_definitions(-DNYX_CMD_MODULE_PREFIX="${NYX_CMD_MODULE_PREFIX}")
add_definitions(-DNYX_CMD_VERSION_INFO="${WEBOS_COMPONENT_VERSION}")

add_subdirectory(nyx-cmd)
add_subdirectory(nyx-cmd-modules)

webos_build_configured_tree(${CMAKE_SOURCE_DIR}/files/launch UPSTARTCONFDIR)
