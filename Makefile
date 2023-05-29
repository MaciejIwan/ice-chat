CXX = g++
CPPFLAGS += -I.
LDFLAGS += -lIce

SLICE_FILES = Chat.ice
SLICE_CPP_FILES = $(SLICE_FILES:.ice=.cpp)

OBJS = $(SLICE_CPP_FILES:.cpp=.o) main.o LobbyI.o RoomFactoryI.o RoomI.o UserI.o

.PHONY: all clean

all: chat

chat: $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

slice: $(SLICE_CPP_FILES)

$(SLICE_CPP_FILES): $(SLICE_FILES)
	slice2cpp $<

clean:
	rm -f chat $(OBJS) $(SLICE_CPP_FILES)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $<
