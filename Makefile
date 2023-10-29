CPP = g++
CPPFLAGS = -std=c++11 -Wall -Wno-sign-compare
SRCDIR = src
TESTDIR = tests
INCDIR = includes
OBJDIR = obj

SRCS = $(wildcard $(SRCDIR)/*.cpp)
TESTSRCS = $(wildcard $(TESTDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
TESTOBJS = $(patsubst $(TESTDIR)/%.cpp, $(OBJDIR)/%.o, $(TESTSRCS))

TARGET = run

all: $(TARGET)

$(TARGET): $(OBJS) $(TESTOBJS)
	$(CPP) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@if [ ! -d $(OBJDIR) ]; then mkdir -p $(OBJDIR); fi
	$(CPP) $(CPPFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp
	@if [ ! -d $(OBJDIR) ]; then mkdir -p $(OBJDIR); fi
	$(CPP) $(CPPFLAGS) -I$(INCDIR) -c $< -o $@

clean_obj:
	rm -rf $(OBJDIR)

clean: clean_obj
	rm -f $(TARGET)

re: clean all
	./$(TARGET)

debug: CPPFLAGS += -DDEBUG_ENABLED
debug: all
