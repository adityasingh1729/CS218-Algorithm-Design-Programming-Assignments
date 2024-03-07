INPUTS := inputs/
OUTPUTS := outputs/
MYOUTPUT := myoutput/

CXX := g++
CXX_FLAGS := -Wall -Wextra --std=c++20

INPUT_FILES = $(wildcard $(INPUTS)*.txt)
OUTPUT_FILES = $(wildcard $(OUTPUTS)*.txt)
MAIN_FILE := helper.cpp
MYOUTPUT_FILES := $(patsubst $(INPUTS)%, $(MYOUTPUT)%, $(INPUT_FILES:.txt=_out.txt))

all: helper

helper: $(MAIN_FILE) $(INPUT_FILES)
	$(CXX) $(CXX_FLAGS) $< -o $@
	./$@

clean:
	rm -f $(MYOUTPUT)*.txt

.PHONY: all clean helper