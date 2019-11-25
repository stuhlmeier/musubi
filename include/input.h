//
// Created by stuhlmeier on 11/23/19.
//

#ifndef LIBMUSUBI_INPUT_H
#define LIBMUSUBI_INPUT_H

#include <unordered_map>
#include "util/common.h"
#include "window.h"

namespace musubi {
    struct input_state final {
        bool request_close{false};
    };

    struct application_input_state final {
        input_state global_state;
        std::unordered_map<window::id_type, input_state> window_states;
    };

    class input_poller {
    public:
        virtual ~input_poller() = default;

        virtual void poll(application_input_state &inputState) = 0;
    };
}

#endif //LIBMUSUBI_INPUT_H
