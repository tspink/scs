// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Tom Spink tcs6@st-andrews.ac.uk
#pragma once

#include <fstream>

namespace scs::model
{
    class model;

    class model_builder
    {
    public:
        virtual void build(model &m) = 0;
    };

    class file_based_model_builder : public model_builder
    {
    public:
        file_based_model_builder(const std::string &filename) : file_(filename) {
            if (!file_.is_open()) {
                throw std::runtime_error("unable to open file '" + filename + "'");
            }
        }

    protected:
        std::ifstream &file() { return file_; }

    private:
        std::ifstream file_;
    };

    class yaml_model_builder : public file_based_model_builder
    {
    public:
        yaml_model_builder(const std::string &filename) : file_based_model_builder(filename) {}
        virtual void build(model &m) override;
    };
}
