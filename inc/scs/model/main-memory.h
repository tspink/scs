// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Tom Spink tcs6@st-andrews.ac.uk
#pragma once

#include <scs/model/access-target.h>

namespace scs::model
{
    class main_memory : public access_target
    {
    public:
        main_memory(const std::string &id) : access_target(id) {}

        virtual void access(const io::event &event) override
        {
            record_access(false);
        }
    };
}
