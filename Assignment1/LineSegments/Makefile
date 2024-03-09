INPUTS := inputs/
OUTPUTS := outputs/
MYOUTPUT := myoutput/

CXX := g++
CXX_FLAGS := -Wall -Wextra --std=c++20

INPUT_FILES := $(wildcard $(INPUTS)*.txt)
OUTPUT_FILES := $(wildcard $(OUTPUTS)*.txt)
MAIN_FILE := skyline.cpp
EXEC := $(MAIN_FILE:.cpp=)
MYOUTPUT_FILES := $(patsubst $(INPUTS)%, $(MYOUTPUT)%, $(INPUT_FILES:.txt=_out.txt))

all: $(EXEC)

$(EXEC): $(MAIN_FILE) $(INPUT_FILES)
	$(CXX) $(CXX_FLAGS) $< -o $@
	./$@
	rm -r $(EXEC)

clean:
	rm -f $(MYOUTPUT)*.txt
	rm -r $(EXEC)

.PHONY: all clean $(EXEC)