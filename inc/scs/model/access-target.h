// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Tom Spink tcs6@st-andrews.ac.uk
#pragma once

#include <scs/io/event.h>

#include <string>
#include <iostream>

namespace scs::model
{
    class access_target
    {
    public:
        access_target(const std::string &id) : id_(id), accesses_(0), misses_(0) {}

        const std::string &id() const { return id_; }

        virtual void access(const io::event &event) = 0;

        unsigned long accesses() const { return accesses_; }
        unsigned long hits() const { return accesses_ - misses_; }
        unsigned long misses() const { return misses_; }

        friend std::ostream &operator<<(std::ostream &os, const access_target &at)
        {
            os << at.id() << ": "
               << "accesses=" << at.accesses()
               << ", hits=" << at.hits()
               << ", misses=" << at.misses()
               << ", miss-rate=" << (((double)at.misses() * 100.) / at.accesses()) << "%"
               << std::endl;

            return os;
        }

    protected:
        void record_access(bool is_miss)
        {
            accesses_++;

            if (is_miss)
            {
                misses_++;
            }
        }

    private:
        const std::string id_;
        unsigned long accesses_;
        unsigned long misses_;
    };
}
