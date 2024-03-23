CC = cc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -lmlx -lX11 -lm -I/fractal_test/src/minilibx-linux
SRCS = main.c
OBJS = $(SRCS:.c=.o)
EXEC = my_program

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
