CPP = g++
CPPFLAGS = -std=c++11 -Wall -Wno-sign-compare -DDEBUG_ENABLED
SRCDIR = src
INCDIR = includes
OBJDIR = obj

SRCS = $(wildcard $(SRCDIR)/*.cpp) 
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

TARGET = run

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CPP) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@if [ ! -d $(OBJDIR) ]; then mkdir -p $(OBJDIR); fi
	$(CPP) $(CPPFLAGS) -I$(INCDIR) -c $< -o $@

clean_obj:
	rm -rf $(OBJDIR)

clean: clean_obj
	rm -f $(TARGET)

re: fclean all