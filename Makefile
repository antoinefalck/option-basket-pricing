CC = g++
CFLAGS = -Wall

SRC = main.cpp MC.cpp Price.cpp Brownian.cpp
DEPS = Brownian.h
OBJ = $(SRC:.cpp=.o)

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -larmadillo

main.o: main.cpp Price.h Brownian.h
	$(CC) $(CFLAGS) -c $<

MC.o: MC.cpp MC.h Price.h
	$(CC) $(CFLAGS) -c $<

Price.o: Price.cpp Price.h Brownian.h
	$(CC) $(CFLAGS) -c $<

Brownian.o: Brownian.cpp Brownian.h
	$(CC) $(CFLAGS) -c $< 

clean:
	rm -rf *.o

mrproper: clean
	rm -rf main