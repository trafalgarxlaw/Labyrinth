CC = gcc
OBJS = $(patsubst %.c,%.o,$(wildcard *.c))
CFLAGS = `sdl2-config --cflags` `xml2-config --cflags`
LDFLAGS = -lSDL2_image `sdl2-config --libs` -ltmx `xml2-config --libs` -lz
EXEC = maze

$(EXEC): $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $(EXEC)

%.o: %.c
	$(CC) $< $(CFLAGS) -c -o $@

.PHONY: clean

clean:
	rm -f $(OBJS) $(EXEC)
