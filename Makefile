  
CFLAGS += -Wall -pedantic -O3 -std=c99

.PHONY: wsort

wsort:
	$(CC) $(CFLAGS) -o wsort wsort.c

run: wsort
	./wsort
