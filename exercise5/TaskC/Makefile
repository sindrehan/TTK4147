# program executable name
TARGET = taskC
# compiler flags
CFLAGS = -g -Wall -std=gnu11 -fsanitize=thread
# linker flags
LDFLAGS = -lpthread -lcomedi -lm -g -fsanitize=thread
# list of sources
SOURCES = $(shell find -name "*.c")
# default rule, to compile everything
all: $(TARGET)
# define object files
OBJECTS = $(SOURCES:.c=.o)
# link programs
$(TARGET): $(OBJECTS)
	 gcc  -o $@ $^ $(LDFLAGS)
# compile
%.o : %.c
	clang $(CFLAGS) -c -o $@ $<
# cleaning
clean:
	rm -f $(TARGET) $(OBJECTS)
