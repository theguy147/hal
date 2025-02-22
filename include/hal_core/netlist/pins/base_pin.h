// MIT License
// 
// Copyright (c) 2019 Ruhr University Bochum, Chair for Embedded Security. All Rights reserved.
// Copyright (c) 2019 Marc Fyrbiak, Sebastian Wallat, Max Hoffmann ("ORIGINAL AUTHORS"). All rights reserved.
// Copyright (c) 2021 Max Planck Institute for Security and Privacy. All Rights reserved.
// Copyright (c) 2021 Jörn Langheinrich, Julian Speith, Nils Albartus, René Walendy, Simon Klix ("ORIGINAL AUTHORS"). All Rights reserved.
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include "hal_core/defines.h"
#include "hal_core/netlist/data_container.h"
#include "hal_core/netlist/gate_library/enums/pin_direction.h"
#include "hal_core/netlist/gate_library/enums/pin_type.h"
#include "hal_core/netlist/pins/pin_group.h"

#include <string>

namespace hal
{
    /**
     * Base class for gate and module pins.
     * 
     * @ingroup pins
     */
    template<class T>
    class BasePin
    {
    public:
        virtual ~BasePin() = default;

        /**
         * Check whether two pins are equal.
         *
         * @param[in] other - The pin to compare against.
         * @returns True if both pins are equal, false otherwise.
         */
        bool operator==(const BasePin& other) const
        {
            return m_id == other.get_id() && m_name == other.get_name() && m_direction == other.get_direction() && m_type == other.get_type()
                   && m_group.first->get_name() == other.get_group().first->get_name() && m_group.second == other.get_group().second;
        }

        /**
         * Check whether two pins are unequal.
         *
         * @param[in] other - The pin to compare against.
         * @returns True if both pins are unequal, false otherwise.
         */
        bool operator!=(const BasePin& other) const
        {
            return !operator==(other);
        }

        /**
         * TODO test, pybind
         * Get the ID of the pin. The ID is unique within an entity, e.g., a module or a gate type.
         * 
         * @returns The ID of the pin.
         */
        u32 get_id() const
        {
            return m_id;
        }

        /**
         * Set the name of the pin.
         * 
         * @param[in] name - The name of the pin.
         */
        void set_name(const std::string& name)
        {
            m_name = name;
        }

        /**
         * Get the name of the pin.
         * 
         * @returns The name of the pin.
         */
        const std::string& get_name() const
        {
            return m_name;
        }

        /**
         * Set the direction of the pin.
         * 
         * @param[in] direction - The pin direction.
         */
        void set_direction(PinDirection direction)
        {
            m_direction = direction;
        }

        /**
         * Get the direction of the pin.
         * 
         * @returns The direction of the pin.
         */
        PinDirection get_direction() const
        {
            return m_direction;
        }

        /**
         * Set the type of the pin.
         * 
         * @param[in] type - The pin type.
         */
        void set_type(PinType type)
        {
            m_type = type;
        }

        /**
         * Get the type of the pin.
         * 
         * @returns The type of the pin.
         */
        PinType get_type() const
        {
            return m_type;
        }

        /**
         * Get the group of the pin as well as the index of the pin within the group.
         * 
         * @returns The group and the index of the pin.
         */
        const std::pair<PinGroup<T>*, u32>& get_group() const
        {
            return m_group;
        }

    private:
        friend PinGroup<T>;

        BasePin(const BasePin&) = delete;
        BasePin(BasePin&&)      = delete;
        BasePin& operator=(const BasePin&) = delete;
        BasePin& operator=(BasePin&&) = delete;

    protected:
        u32 m_id;
        std::string m_name;
        PinDirection m_direction;
        PinType m_type;
        std::pair<PinGroup<T>*, u32> m_group = {nullptr, 0};

        /**
         * Construct a new pin from its name, direction, and type.
         * 
         * @param[in] id - The ID of the pin.
         * @param[in] name - The pin name.
         * @param[in] direction - The direction of the pin.
         * @param[in] type - The type of the pin.
         */
        BasePin(const u32 id, const std::string& name, PinDirection direction, PinType type = PinType::none) : m_id(id), m_name(name), m_direction(direction), m_type(type)
        {
        }
    };
}    // namespace hal