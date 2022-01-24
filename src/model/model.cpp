// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Tom Spink tcs6@st-andrews.ac.uk
#include <scs/model/model.h>
#include <scs/model/main-memory.h>
#include <scs/model/cpu.h>
#include <scs/model/cache.h>

using namespace scs::model;

/**
 * @brief Creates a new main memory object in the model.
 *
 * @param id The identifier for the main memory object.
 * @return main_memory& A reference to the newly created main memory object.
 */
main_memory &model::add_main_memory(const std::string &id)
{
    main_memory *m = new main_memory(id);
    access_targets_[m->id()] = m;

    return *m;
}

/**
 * @brief Creates a new cache object in the model.
 *
 * @param id The identifier for the cache object.
 * @param cache_size The power-of-two size of the cache.
 * @param line_size The byte size of a cache line
 * @param assoc The power-of-two associativity.
 * @return cache& Returns a reference to the newly created cache object.
 */
cache &model::add_cache(const std::string &id, int cache_size, int line_size, int assoc)
{
    cache *m = new cache(id, cache_size, line_size, assoc);
    access_targets_[m->id()] = m;

    return *m;
}

/**
 * @brief Creates a new CPU object in the model.
 *
 * @param id The identifier for the CPU object.
 * @return cpu& Returns a reference to the newly created CPU object.
 */
cpu &model::add_cpu(const std::string &id)
{
    cpu *c = new cpu(id);
    cpus_[c->id()] = c;

    return *c;
}

/**
 * @brief Dumps a summary of the model as it stands to the given output stream.
 *
 * @param os The output stream to write the summary to.
 */
void model::dump(std::ostream &os) const
{
    for (auto cpu : cpus_)
    {
        os << *cpu.second;
    }

    for (auto at : access_targets_)
    {
        os << *at.second;
    }
}
