// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Tom Spink tcs6@st-andrews.ac.uk
#pragma once

namespace scs::io
{
    /**
     * @brief An indicator of event types.
     */
    enum class event_type
    {
        error,
        fetch,
        read,
        write,
        eof
    };

    /**
     * @brief Represents a single memory operation.
     */
    class event
    {
    public:
        /**
         * @brief Construct a new event object
         *
         * @param et The type of memory operation.
         * @param ea The effective address of the memory operation.
         * @param size The effective size of the memory operation.
         */
        event(event_type et, unsigned long ea, int size) : et_(et), ea_(ea), sz_(size) {}

        event_type type() const { return et_; }
        unsigned long addr() const { return ea_; }
        int size() const { return sz_; }

    private:
        event_type et_;
        unsigned long ea_;
        int sz_;
    };
}
