CPP = g++
CPPFLAGS = -std=c++11 -Wall -Wno-sign-compare
SRCDIR = src
INCDIR = includes
OBJDIR = obj
INCDIR = utils

# Liste de tous les fichiers sources dans le répertoire src
SRCS = $(wildcard $(SRCDIR)/*.cpp) 

# Génération de la liste des fichiers objets
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Nom de l'exécutable
TARGET = run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CPP) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@if [ ! -d $(OBJDIR) ]; then mkdir -p $(OBJDIR); fi
	$(CPP) $(CPPFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(TARGET)

re: fclean all
