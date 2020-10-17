CC=~/applications/djgpp/bin/i586-pc-msdosdjgpp-gcc
SOURCES=$(wildcard src/*.c)
EXEC=cdmap/main.exe
CFLAGS=-Wall -Wextra

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(SOURCES:.c=.o)
	$(CC) $(SOURCES:.c=.o) -o $(EXEC)

cdrom:
	xorriso -outdev disk.iso -blank as_needed -map ./cdmap
