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

#include "hal_core/plugin_system/plugin_interface_base.h"
#include "hal_core/utilities/result.h"
#include "hal_core/netlist/boolean_function.h"

#include <map>
#include <set>

namespace hal
{
    /* forward declaration */
    class Gate;
    class Netlist;
    class Net;

    class PLUGIN_API SolveFsmPlugin : public BasePluginInterface
    {
    public:
        std::string get_name() const override;
        std::string get_version() const override;
        void initialize() override;

        /**
         * Generates the state graph of a finite state machine and returns a mapping from each state to a all its possible transitions.
         * The transitions are another mapping from all the possible successor states to the corresponding condition under which the transition is taken.
         * This function uses an SMT solver to find all possible successors and afterwards computes the necessary conditions.
         * 
         * @param[in] nl - Pointer to the netlist.
         * @param[in] state_reg - A vector containing all the gates of the fsm representing the state register.
         * @param[in] transition_logic - A vector containing all the gates of the fsm representing the transition_logic.
         * @param[in] initial_state - A mapping from the state registers to their initial value. If omitted the intial state will be set to 0.
         * @param[in] graph_path - Path where the transition state graph in dot format is saved.
         * @param[in] timeout - Timeout value for the sat solvers. Defaults to 600000 ms.
         * @returns A mapping from each state to all its possible transitions.
         */
        static Result<std::map<u64, std::map<u64, BooleanFunction>>> solve_fsm(Netlist* nl,
                                                                               const std::vector<Gate*> state_reg,
                                                                               const std::vector<Gate*> transition_logic,
                                                                               const std::map<Gate*, bool> initial_state = {},
                                                                               const std::string graph_path              = "",
                                                                               const u32 timeout                         = 600000);

        /**
         * Generates the state graph of a finite state machine and returns a mapping from each state to a all its possible transitions.
         * The transitions are another mapping from all the possible successor states to the corresponding condition under which the transition is taken.
         * This function uses a burte force search to find all possible successors and afterwards computes the necessary conditions.
         * 
         * @param[in] nl - Pointer to the netlist.
         * @param[in] state_reg - A vector containing all the gates of the fsm representing the state register.
         * @param[in] transition_logic - A vector containing all the gates of the fsm representing the transition_logic.
         * @param[in] graph_path - Path where the transition state graph in dot format is saved.
         * @returns A mapping from each state to all its possible transitions.
         */
        static Result<std::map<u64, std::map<u64, BooleanFunction>>>
            solve_fsm_brute_force(Netlist* nl, const std::vector<Gate*> state_reg, const std::vector<Gate*> transition_logic, const std::string graph_path = "");

        /**
         * Generates the state graph of a finite state machine from the transitions of that fsm.
         *
         * @param[in] state_reg - Vector contianing the state registers.
         * @param[in] transitions - Transitions of the fsm given as a map from origin state to all possible successor states and the corresponding condition.
         * @param[in] graph_path - Path where the transition state graph in dot format is saved.
         * @param[in] max_condition_length - The maximum character length that is printed for boolean functions representing the conditions.
         * @param[in] base - The base with that the states are formatted and printed.
         * @returns A string representing the dot graph.
         */
        static Result<std::string> generate_dot_graph(const std::vector<Gate*>& state_reg,
                                                      const std::map<u64, std::map<u64, BooleanFunction>>& transitions,
                                                      const std::string& graph_path  = "",
                                                      const u32 max_condition_length = 128,
                                                      const u32 base                 = 10);

        /**
         * Generates the state graph of a finite state machine from the transitions of that fsm.
         *
         * @param[in] state_reg - Vector contianing the state registers.
         * @param[in] transitions - Transitions of the fsm given as a map from origin state to all possible successor states and the corresponding condition.
         * @param[in] graph_path - Path where the transition state graph in dot format is saved.
         * @param[in] max_condition_length - The maximum character length that is printed for boolean functions representing the conditions.
         * @param[in] base - The base with that the states are formatted and printed.
         * @returns A string representing the dot graph.
         */
        /*
        static Result<std::string> generate_dot_graph(const std::vector<Gate*>& state_reg,
                                                      const std::map<u64, std::set<u64>>& transitions,
                                                      const std::string& graph_path  = "",
                                                      const u32 max_condition_length = 128,
                                                      const u32 base                 = 10);
        */
    };
}    // namespace hal
