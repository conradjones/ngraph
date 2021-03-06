# ******************************************************************************
# Copyright 2017-2020 Intel Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ******************************************************************************

if (NGRAPH_IE_STATIC_LIB_ENABLE)
    set(LIBRARY_TYPE STATIC)
else()
    set(LIBRARY_TYPE SHARED)
endif()

set(SRC
    ie_backend.cpp
    ie_backend.hpp
    ie_backend_visibility.hpp
    ie_tensor.cpp
    ie_tensor.hpp
    ie_executable.cpp
    ie_executable.hpp
)

add_library(ie_backend ${LIBRARY_TYPE} ${SRC})
add_dependencies(ie_backend inference_engine)
target_compile_definitions(ie_backend PRIVATE IE_BACKEND_DLL_EXPORTS)
target_include_directories(ie_backend PUBLIC ${IE_MAIN_SOURCE_DIR}/include)
target_link_libraries(ie_backend PUBLIC ngraph inference_engine)

install(TARGETS ie_backend LIBRARY DESTINATION ${NGRAPH_INSTALL_LIB})
