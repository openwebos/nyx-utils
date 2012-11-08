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
webos_component(1 0 0 QUALIFIER RC1)

pkg_check_modules(NYXLIB REQUIRED nyx)
include_directories(${NYXLIB_INCLUDE_DIRS})
webos_add_compiler_flags(ALL ${NYXLIB_CFLAGS_OTHER})
add_definitions(-DNYXCMD_VERSION_INFO="${WEBOS_COMPONENT_VERSION}")

add_subdirectory(nyx-cmd)
add_subdirectory(nyx-cmd-modules)
