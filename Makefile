CC = gcc
CFLAGS = -Wall -Wextra -g -lws2_32

TARGET = application

SRCS = main.c src/router.c src/handlers.c src/server.c src/http.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ -lws2_32

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean