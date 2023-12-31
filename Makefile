CC = gcc
CFLAGS = -Ofast
TARGET = mathquiz
SRCS = main.c color.c

# Gets max system's thread count
NUM_THREADS := $(shell nproc)

# Set make thread count to max number given by system
MAKEFLAGS += -j$(NUM_THREADS)

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET).out

.PHONY: clean

clean:
	rm -f $(TARGET)

.PHONY: max_threads
