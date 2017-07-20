# DIRECTORY STRUCTURE
SRCDIR := src
BLDDIR := build
OBJDIR := $(BLDDIR)/obj
DEPDIR := $(BLDDIR)/dep
SRCS   := $(shell find $(SRCDIR) -name "*.cpp")
OBJS   := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DEPS   := $(SRCS:$(SRCDIR)/%.cpp=$(DEPDIR)/%.d)
TREE   := $(sort $(patsubst %/,%,$(dir -d $(OBJS))))


# COMPILER OPTIONS
CXX           = g++ 
CXXFLAGS      = -std=c++11 -O3
INCPATH       = -I.
LINK          = g++ 
LFLAGS        = -m64 -Wl,-O3
LIBS          = $(SUBLIBS) -larmadillo -llapack -lblas
CPPFLAGS      = -MMD -MP -MF $(@:$(OBJDIR)/%.o=$(DEPDIR)/%.d)

# OUTPUT FILE NAME
TARGET  = shellProject

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LFLAGS) -o $(BLDDIR)/$(TARGET) $(OBJS) $(OBJCOMP) $(LIBS)

.SECONDEXPANSION:
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $$(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

$(TREE): %:
	mkdir -p $@
	mkdir -p $(@:$(OBJDIR)%=$(DEPDIR)%)

clean:
	rm -r $(OBJDIR) $(DEPDIR)
