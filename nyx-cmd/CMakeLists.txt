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

include_directories(${CMAKE_SOURCE_DIR}/include/internal/nyx-cmd)

set(nyxcmd_lib_dir "${WEBOS_INSTALL_LIBDIR}/nyx-cmd")
set(CMAKE_INSTALL_RPATH ${nyxcmd_lib_dir})
add_definitions(-DNYXCMD_LIB_DIR="${nyxcmd_lib_dir}")
unset(nyxcmd_lib_dir)

add_executable(nyx-cmd ${SRC} main.cpp
                              nyx_cmd_devicetype.cpp
                              nyx_cmd_command.cpp)

target_link_libraries(nyx-cmd dl ${NYXLIB_LDFLAGS})

webos_config_build_doxygen(doc nyx_cmd.doxy)
webos_build_program(NAME nyx-cmd)
