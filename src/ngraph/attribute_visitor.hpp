//*****************************************************************************
// Copyright 2017-2019 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//*****************************************************************************

#pragma once

#include <string>
#include <utility>

#include "ngraph/partial_shape.hpp"
#include "ngraph/type.hpp"
#include "ngraph/type/element_type.hpp"

namespace ngraph
{
    template <typename T>
    class ValueAccessor;

    /// \brief Visits the attributes of a node.
    ///
    /// Attributes are the values set when building a graph which are not
    /// computed as the graph executes. Values computed from the graph topology and attributes
    /// during compilation are not attributes.
    class AttributeVisitor
    {
    public:
        virtual ~AttributeVisitor() {}
        virtual void on_attribute(const std::string& name, std::string& value) = 0;
        virtual void on_attribute(const std::string& name, bool& value) = 0;
        virtual void on_attribute(const std::string& name, double& value) = 0;
        virtual void on_attribute(const std::string& name, int64_t& value) = 0;
        virtual void on_attribute(const std::string& name, uint64_t& value) = 0;
        virtual void on_adapter(const std::string& name, ValueAccessor<void>& adapter) = 0;
        virtual void on_adapter(const std::string& name, ValueAccessor<std::string>& adapter) = 0;
        virtual void on_adapter(const std::string& name,
                                ValueAccessor<std::vector<int64_t>>& adapter) = 0;

        template <typename T>
        typename std::enable_if<std::is_enum<T>::value, void>::type
            on_attribute(const std::string& name, T& value)
        {
            EnumAdapter<T> adapter(value);
            on_adapter(name, adapter);
        }
        template <typename T>
        typename std::enable_if<std::is_integral<T>::value, void>::type
            on_attribute(const std::string& name, std::vector<T>& value)
        {
            IntegralVectorAdapter<T> adapter(value);
            on_adapter(name, adapter);
        }
        template <typename T>
        typename std::enable_if<std::is_class<T>::value, void>::type
            on_attribute(const std::string& name, T& value)
        {
            AttributeAdapter<T> adapter(value);
            on_adapter(name, adapter);
        }
    };
}
