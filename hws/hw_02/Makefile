CXX = g++
CXXFLAGS = -O2 -g -ggdb -Wall -Werror -std=c++11 -Iinclude
LDFLAGS = -g -ggdb

EXE = hw_02
SRCDIR = src
OBJDIR = obj

EXE_TEST = hw_02_test
SRCDIR_TEST = test
OBJDIR_TEST = obj/test


OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))
OBJECTS_TEST = $(patsubst $(SRCDIR_TEST)/%.cpp,$(OBJDIR_TEST)/%.o,$(wildcard $(SRCDIR_TEST)/*.cpp))

all: $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE) $(LDFLAGS)

$(EXE_TEST): $(OBJECTS_TEST)
	$(CXX) $(OBJECTS_TEST) -o $(EXE_TEST) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

test: $(OBJECTS_TEST) obj/huffman_tree.o obj/huffman_archiver.o obj/huffman_unarchiver.o obj/util.o
	$(CXX) $(OBJECTS_TEST) obj/huffman_tree.o obj/huffman_archiver.o obj/huffman_unarchiver.o obj/util.o -o $(EXE_TEST) $(LDFLAGS)

$(OBJDIR_TEST)/%.o: $(SRCDIR_TEST)/%.cpp | $(OBJDIR_TEST)
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

include $(wildcard $(OBJDIR)/*.d)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR_TEST):
	mkdir -p $(OBJDIR)/test

clean:
	rm -rf $(OBJDIR) $(EXE) $(EXE_TEST)

.PHONY: clean all