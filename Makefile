SLICE_FILES=Chat.ice
SLICE_CPP_FILES=$(SLICE_FILES:.ice=.cpp)

slice: $(SLICE_CPP_FILES)

$(SLICE_CPP_FILES): $(SLICE_FILES)
	slice2cpp $(SLICE_FILES)

clean:
	rm -f *.o Chat.cpp Chat.h