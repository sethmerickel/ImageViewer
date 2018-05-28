CC := clang++ # This is the main compiler
#CC := clang --analyze # and comment out the linker last line

# Folders
SRCDIR := src
BUILDDIR := build
TARGETDIR := bin
INCDIRS := -Iinclude

# Targets
EXECUTABLE := imageviewer
TARGET := $(TARGETDIR)/$(EXECUTABLE)

#Define sources and objects
SOURCES := $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.cpp=.o))

# Flags
#CFLAGS := -std=c++17 -stdlib=libc++ -O2
CFLAGS := -std=c++17 -w -O2 
LIBDIRS := 
LIBS := -lglfw -ldl

all: init $(TARGET)

init:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

$(TARGET): $(BUILDDIR)/main.o $(BUILDDIR)/glad.o
	@echo "Linking..."	
	$(CC) $(LIBS) $^ -o $@

$(BUILDDIR)/main.o: $(SRCDIR)/main.cpp
	@echo "Building main.o..."
	$(CC) $(CFLAGS) -c $^ -o $@ $(INCDIRS)

$(BUILDDIR)/glad.o: $(SRCDIR)/glad.c
	@echo "Building glad.o..."
	$(CC) $(CFLAGS) -c $^ -o $@ $(INCDIRS) $(LIBS)

clean:
	@echo "Cleaning $(TARGET)...";
	$(RM) -r $(BUILDDIR) $(TARGETDIR)


# Tests

.PHONY: clean
