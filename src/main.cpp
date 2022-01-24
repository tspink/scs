// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Tom Spink tcs6@st-andrews.ac.uk
#include <iostream>
#include <scs/model/model.h>
#include <scs/model/cpu.h>
#include <scs/model/model-builder.h>
#include <scs/io/event-stream.h>

using namespace scs::model;
using namespace scs::io;

int main(int argc, char **argv)
{
    // Check command-line
    if (argc != 3)
    {
        std::cerr << "usage: " << argv[0] << " <model descriptor> <events>" << std::endl;
        return 1;
    }

    // Construct and build the simulation model.
    model m;

    yaml_model_builder mb(argv[1]);
    mb.build(m);

    // Acquire the first CPU object - we only support single CPU simulation just now.
    auto c = m.get_first_cpu();
    if (!c.has_value())
    {
        std::cerr << "no configured cpu" << std::endl;
        return 1;
    }

    // Load the input event stream.
    event_stream events(argv[2]);

    // Simulate!
    std::cout << "RUNNING SIMULATION..." << std::flush;

    event e = events.next_event();
    while (e.type() != event_type::eof)
    {
        (*c)->access(e);
        e = events.next_event();
    }

    // Print results
    std::cout << "DONE!" << std::endl
              << std::endl;

    std::cout << m;

    return 0;
}
