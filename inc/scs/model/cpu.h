// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Tom Spink tcs6@st-andrews.ac.uk
#pragma once

#include <string>
#include <scs/io/event.h>
#include <scs/model/access-target.h>

namespace scs::model
{
    class cpu : public access_target
    {
    public:
        cpu(const std::string &id) : access_target(id), icount_(0), fi_(nullptr), ri_(nullptr), wi_(nullptr) {}

        unsigned long icount() const { return icount_; }

        virtual void access(const io::event &event) override
        {
            record_access(false);

            switch (event.type())
            {
            case io::event_type::fetch:
                icount_++;
                fi_->access(event);
                break;

            case io::event_type::read:
                ri_->access(event);
                break;

            case io::event_type::write:
                wi_->access(event);
                break;

            default:
                break;
            }
        }

        access_target *fetch_interface() const { return fi_; }
        access_target *read_interface() const { return ri_; }
        access_target *write_interface() const { return wi_; }

        void fetch_interface(access_target *target) { fi_ = target; }
        void read_interface(access_target *target) { ri_ = target; }
        void write_interface(access_target *target) { wi_ = target; }

        friend std::ostream &operator<<(std::ostream &os, const cpu &at)
        {
            os << at.id() << ": "
               << "instructions=" << at.icount()
               << ", accesses=" << at.accesses()
               << ", hits=" << at.hits()
               << ", misses=" << at.misses()
               << ", miss-rate=" << (((double)at.misses() * 100.) / at.accesses()) << "%"
               << std::endl;

            return os;
        }

    private:
        unsigned long icount_;
        access_target *fi_;
        access_target *ri_;
        access_target *wi_;
    };
}
