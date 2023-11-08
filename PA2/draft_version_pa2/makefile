CC = g++
CFLAGS = -c

OPTFLAGS = -O2

bin/mps : main_opt.o
		$(CC) $(OPTFLAGS) main_opt.o -o bin/mps

main_opt.o : src/main.cpp
		$(CC) $(CFLAGS) $< -o $@


clean:
		rm -rf *.o bin/*