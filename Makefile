CC = gcc

CFLAGS = -Wall -g


# Define source files
SRCS = main.c calculator.c

OBJS =$(SRCS:.c=.o)

# Define the executable file
MAIN = Calculator

.PHONY: depend clean

all: $(MAIN)
	@echo "build..."

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS)

#add this two params and correct their values in case of libraries to be added: $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend nedds it
