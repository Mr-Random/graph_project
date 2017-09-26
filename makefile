#Makefile project GRAF v.1.0.0

#Variables
CC = gcc -g
CFLAGS = -O4 -W -Wall
CPPFLAGS = -I.
LDLIBS = -lm

MAIN=$(BINDIR)/main

SRCDIR = ./src
OBJDIR = ./obj
BINDIR = ./bin

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(MAIN)

#principale rule
$(MAIN): $(OBJ) $(BINDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $(OBJ) $(LDLIBS) 

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(SRCDIR)/%.h $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(OBJDIR)/$*.o 

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(OBJDIR)/$*.o 

clean:
	rm -f $(OBJ)/*.o

veryclean: clean
		rm $(MAIN)
