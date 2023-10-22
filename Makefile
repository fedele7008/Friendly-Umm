CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -MMD
OUTDIR = bin
SRCDIR = src
OBJDIR = obj

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

EXEC = FriendlyUmmCompiler
TARGET = $(OUTDIR)/${EXEC}

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(OUTDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJDIR) $(OUTDIR)

.PHONY: all clean