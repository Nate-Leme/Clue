PROG = adventure
SRCS = adventure.c rooms.c items.c
OBJS = $(SRCS:%.c=%.o)

$(PROG): $(OBJS)
	$(CC) -g -o $(PROG) $(OBJS)

clean:
	rm -f $(PROG) $(OBJS)