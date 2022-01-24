# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Tom Spink tcs6@st-andrews.ac.uk
q := @
top-dir := $(CURDIR)
src-dir := $(top-dir)/src
inc-dir := $(top-dir)/inc

out := scs

src := $(shell find $(src-dir) | grep -E "\.cpp$$")
obj := $(src:.cpp=.o)
dep := $(src:.cpp=.d)

cxxflags := -g -Wall -O3 -I $(inc-dir)
ldflags := -lyaml-cpp

BUILD-TARGET = $(patsubst $(top-dir)/%,%,$@)

all: $(out)

clean: .FORCE
	rm -f $(obj) $(dep) $(out)

$(out): $(obj)
	@echo "  LD    $(BUILD-TARGET)"
	$(q)g++ -o $@ $(ldflags) $(obj)

%.o: %.cpp %.d
	@echo "  C++   $(BUILD-TARGET)"
	$(q)g++ -c -o $@ $(cxxflags) $<

%.d: %.cpp
	$(q)g++ -M -MT $(@:.d=.o) -o $@ $(cxxflags) $<

-include $(dep)

.PHONY: .FORCE
