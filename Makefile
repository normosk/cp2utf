CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=cp2utf.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=cp2utf.exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
