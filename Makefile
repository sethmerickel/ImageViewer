CC := clang++ # This is the main compiler
#CC := clang --analyze # and comment out the linker last line

# Folders
SRCDIR := src
OBJDIR := obj
TARGETDIR := bin
INCDIRS := -Iinclude

# Targets
EXECUTABLE := imageviewer
TARGET := $(TARGETDIR)/$(EXECUTABLE)

#Define sources and objects
SRCS := $(wildcard src/*.cpp) 
OBJS := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRCS:.cpp=.o))

# Flags
#CFLAGS := -std=c++17 -stdlib=libc++ -O2
CFLAGS := -std=c++17 -w -O2 
LIBDIRS := 
LDFLAGS := -lglfw -ldl

all: init $(TARGET)

init:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(OBJDIR)

$(TARGET): $(OBJS)
	@echo "Linking..."
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "Compiling..."
	$(CC) $(CFLAGS) -c $^ -o $@ $(INCDIRS)

clean:
	@echo "Cleaning $(TARGET)...";
	$(RM) -r $(BUILDDIR) $(TARGETDIR) $(OBJDIR)

debug:
	@echo $(SRCS)
	@echo $(OBJS)

# Tests

.PHONY: clean
.PHONY: debug
