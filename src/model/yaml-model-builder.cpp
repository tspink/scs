// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Tom Spink tcs6@st-andrews.ac.uk
#include <scs/model/model-builder.h>
#include <scs/model/model.h>
#include <scs/model/cpu.h>
#include <scs/model/cache.h>
#include <scs/model/main-memory.h>

#include <yaml-cpp/yaml.h>

using namespace scs::model;

/**
 * @brief Builds the simulation model from the given YAML description.
 *
 * @param model The model to populate.
 */
void yaml_model_builder::build(model &model)
{
    YAML::Node defs = YAML::Load(file());

    // TODO: Error checking.

    // (1) Create root objects
    for (const auto &cpudef : defs["cpus"])
    {
        model.add_cpu(cpudef.first.as<std::string>());
    }

    for (const auto &memdef : defs["memory"])
    {
        model.add_main_memory(memdef.first.as<std::string>());
    }

    for (const auto &cachedef : defs["caches"])
    {
        model.add_cache(cachedef.first.as<std::string>(),
                        cachedef.second["cache_size"].as<int>(),
                        cachedef.second["line_size"].as<int>(),
                        cachedef.second["assoc"].as<int>());
    }

    // (2) Connect objects together
    for (const auto &cpudef : defs["cpus"])
    {
        cpu &cpu = model.get_cpu(cpudef.first.as<std::string>());

        cpu.fetch_interface(&model.get_target(cpudef.second["fetch"].as<std::string>()));
        cpu.read_interface(&model.get_target(cpudef.second["read"].as<std::string>()));
        cpu.write_interface(&model.get_target(cpudef.second["write"].as<std::string>()));
    }

    for (const auto &cachedef : defs["caches"])
    {
        cache &c = (cache &)model.get_target(cachedef.first.as<std::string>());
        c.next(&model.get_target(cachedef.second["next"].as<std::string>()));
    }
}
