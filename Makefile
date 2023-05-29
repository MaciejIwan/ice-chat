CXX = g++

CPPFLAGS += -I.
LDFLAGS += -lIce

SLICE_FILES = Chat.ice
SLICE_CPP_FILES = $(SLICE_FILES:.ice=.cpp)

.PHONY: clean slice

slice: $(SLICE_CPP_FILES)

$(SLICE_CPP_FILES): $(SLICE_FILES)
	slice2cpp $(SLICE_FILES)

clean:
	rm -f *.o
