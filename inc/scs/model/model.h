// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Tom Spink tcs6@st-andrews.ac.uk
#pragma once

#include <scs/model/access-target.h>
#include <map>
#include <optional>

namespace scs::model
{
    class main_memory;
    class cache;
    class cpu;

    class model
    {
    public:
        model() {}
        ~model() {}

        main_memory &add_main_memory(const std::string &id);
        cache &add_cache(const std::string &id, int cache_size, int line_size, int assoc);
        cpu &add_cpu(const std::string &id);

        access_target &get_target(const std::string &id)
        {
            return *access_targets_[id];
        }

        cpu &get_cpu(const std::string &id)
        {
            return *cpus_[id];
        }

        std::optional<cpu *> get_first_cpu()
        {
            auto i = cpus_.begin();
            if (i == cpus_.end())
            {
                return std::nullopt;
            }

            return i->second;
        }

        friend std::ostream &operator<<(std::ostream &os, const model &m)
        {
            m.dump(os);
            return os;
        }

    private:
        std::map<std::string, access_target *> access_targets_;
        std::map<std::string, cpu *> cpus_;

        void dump(std::ostream &os) const;
    };
}
