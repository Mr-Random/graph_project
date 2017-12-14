#Makefile project GRAF v.1.0.0

#Variables
CC = gcc -g
CFLAGS = -O4 -Wall
CPPFLAGS = -I.
LDLIBS = -lm

MAIN=$(BINDIR)/main

SRCDIR = ./src
OBJDIR = ./obj
BINDIR = ./bin
LIBDIR = ./lib

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)


all: directories $(MAIN)

#principale rule
$(MAIN): $(OBJ) $(BINDIR) #$(LIBDIR)/libLinkedList.a $(LIBDIR)/libGraph.a
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $(OBJ) $(LDLIBS) 

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(SRCDIR)/%.h $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(OBJDIR)/$*.o 

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(OBJDIR)/$*.o 

.PHONY: directories
directories: $(OBJDIR) $(BINDIR)

$(OBJDIR): 
	mkdir -p $(OBJDIR)

$(BINDIR): 
	mkdir -p $(BINDIR)

$(LIBDIR)/libLinkedList.a : $(OBJDIR)/ManipulatingLinkedLists.o 
	ar rcs $@ $^

$(LIBDIR)/libGraph.a : $(OBJDIR)/ManipulatingLinkedLists.o
	ar rcs $@ $^

clean: 
	rm -rf $(OBJDIR)

veryclean: clean
	rm -rf $(BINDIR)