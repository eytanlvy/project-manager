CPP = g++
CPPFLAGS = -std=c++11 -Wall -Wno-sign-compare -DDEBUG_ENABLED
SRCDIR = src
INCDIR = includes
OBJDIR = obj
VPATH = $(SRCDIR):$(SRCDIR)/utils1:$(SRCDIR)/utils2
INCLUDES = -I$(INCDIR)

SRCS = $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/utils1/*.cpp) $(wildcard $(SRCDIR)/utils2/*.cpp)

OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

TARGET = run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CPP) -o $@ $^

$(OBJDIR)/%.o: %.cpp
	@if [ ! -d $(OBJDIR) ]; then mkdir -p $(OBJDIR); fi
	$(CPP) $(CPPFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(TARGET)

re: fclean all
