// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Tom Spink tcs6@st-andrews.ac.uk
#pragma once

#include <scs/io/event.h>

#include <string>
#include <fstream>

namespace scs::io
{
    /**
     * @brief Represents a stream of memory events.
     */
    class event_stream
    {
    public:
        /**
         * @brief Construct a new event stream object
         *
         * @param filename A path to the file containing the trace events.
         */
        event_stream(const std::string &filename) : file_(filename, std::ios_base::binary)
        {
            if (!file_.is_open())
            {
                throw std::runtime_error("unable to open file '" + filename + "'");
            }
        }

        /**
         * @brief Destroy the event stream object
         *
         */
        ~event_stream() { file_.close(); }

        /**
         * @brief Read an event from the trace file, and return an event descriptor.
         *
         * @return event Returns the next event from the trace file.  If the end of the
         * trace file is reached, the event object has the 'eof' type.
         */
        event next_event()
        {
            if (file_.eof())
            {
                return event{event_type::eof, 0, 0};
            }
            else
            {
                unsigned long event_data;
                file_.read((char *)&event_data, sizeof(event_data));

                int type = (event_data >> 60) & 0xf;
                int size = (event_data >> 48) & 0xff;
                unsigned long addr = event_data & ~(0xffffull << 48);

                switch (type)
                {
                case 1: // fetch
                    return event{event_type::fetch, addr, size};

                case 2: // read
                    return event{event_type::read, addr, size};

                case 3: // write
                    return event{event_type::write, addr, size};

                default: // unknown
                    return event{event_type::error, 0, 0};
                }
            }
        }

    private:
        std::ifstream file_;
    };
}
