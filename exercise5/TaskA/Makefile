# program executable name
TARGET = taskA
# compiler flags
CFLAGS = -g -Wall -std=gnu11
# linker flags
LDFLAGS =  -g -lpthread -lcomedi -lm
# list of sources
SOURCES = $(shell find -name "*.c")
# default rule, to compile everything
all: $(TARGET)
# define object files
OBJECTS = $(SOURCES:.c=.o)
# link programs
$(TARGET): $(OBJECTS)
	 gcc -o $@ $^ $(LDFLAGS)
# compile
%.o : %.c
	clang $(CFLAGS) -c -o $@ $<
# cleaning
clean:
	rm -f $(TARGET) $(OBJECTS)
