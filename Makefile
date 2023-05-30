CXX = g++
CPPFLAGS += -I.
LDFLAGS += -lIce

SLICE_FILES = Chat.ice
SLICE_CPP_FILES = $(SLICE_FILES:.ice=.cpp)

OBJS = $(SLICE_CPP_FILES:.cpp=.o) LobbyI.o RoomFactoryI.o RoomI.o UserI.o

.PHONY: all clean

all: clean server client

client: $(OBJS) client.o
	$(CXX) -o $@ client.o $(OBJS) $(LDFLAGS)

server: $(OBJS) server.o 
	$(CXX) -o $@ server.o $(OBJS) $(LDFLAGS)

slice: $(SLICE_CPP_FILES)

$(SLICE_CPP_FILES): $(SLICE_FILES)
	slice2cpp $<

clean:
	rm -f client client.o server server.o $(OBJS) $(SLICE_CPP_FILES) $(SLICE_CPP_FILES:.cpp=.h)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $<
