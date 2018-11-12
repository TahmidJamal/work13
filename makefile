all: work13.o
	gcc -o go work13.o

work13.o: work13.c
	gcc -c work13.c

run:
	./go

clean:
	rm *.o
	rm ./go

