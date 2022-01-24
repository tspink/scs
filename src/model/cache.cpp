// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Tom Spink tcs6@st-andrews.ac.uk
#include <scs/model/cache.h>
#include <iostream>

using namespace scs::model;

/**
 * @brief Construct a new cache::cache object
 *
 * @param id The identifier for the cache object.
 * @param cache_size The power-of-two size of the cache.
 * @param line_size The size of a cache line in bytes
 * @param assoc The power-of-two associativity.
 */
cache::cache(const std::string &id, int cache_size, int line_size, int assoc)
    : access_target(id),
      next_(nullptr),
      cache_size_(cache_size),
      line_size_(line_size),
      assoc_(assoc),
      nr_lines_((1 << cache_size_) / line_size_),
      lines_(nullptr)
{
    lines_ = new cache_line[nr_lines_];
}

/**
 * @brief Destroy the cache::cache object
 *
 */
cache::~cache()
{
    delete[] lines_;
}

/**
 * @brief Runs a memory operation through the cache
 *
 * @param event The event describing the operation being simulated.
 */
void cache::access(const io::event &event)
{
    // TODO: Implement set-associative logic

    // TODO: Figure out if the addr/size combination requires a multiaccess

    // TODO: Convert these div/mods to shifts etc
    // unsigned long offset = event.addr() % line_size_;
    unsigned long tag = event.addr() / line_size_;  // Hmm - not quite sure this is right, need to think more.
    unsigned long slot = tag % nr_lines_;

    //std::cout << "access addr=" << std::hex << event.addr() << ", offset=" << offset << ", tag=" << tag << ", slot=" << slot << std::endl;

    cache_line *line = &lines_[slot];

    if (!line->valid() || line->tag() != tag)
    {
        line->valid(true);
        line->tag(tag);
        record_access(true);
        //std::cout << "miss"<< std::endl;

        next_->access(event);
    }
    else
    {
        //std::cout << "hit"<< std::endl;
        record_access(false);
    }
}
