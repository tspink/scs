// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Tom Spink tcs6@st-andrews.ac.uk
#pragma once

#include <scs/model/access-target.h>

namespace scs::model
{
    class cache_line
    {
    public:
        cache_line() : tag_(0), valid_(false), dirty_(false) {}

        unsigned long tag() const { return tag_; }
        void tag(unsigned long value) { tag_ = value; }

        bool valid() const { return valid_; }
        void valid(bool value) { valid_ = value; }

        bool dirty() const { return dirty_; }
        void dirty(bool value) { dirty_ = value; }

    private:
        unsigned long tag_;
        bool valid_;
        bool dirty_;
    };

    class cache : public access_target
    {
    public:
        cache(const std::string &id, int cache_size, int line_size, int assoc);
        ~cache();

        virtual void access(const io::event &event) override;

        access_target *next() const { return next_; }
        void next(access_target *target) { next_ = target; }

    private:
        access_target *next_;
        int cache_size_;
        int line_size_;
        int assoc_;

        int nr_lines_;
        cache_line *lines_;
    };
}
