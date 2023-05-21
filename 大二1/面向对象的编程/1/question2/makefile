FILE:=main.o

ifeq ($(FILE), $(wildcard $(FILE)))
all:clean main
else
all:main
endif


include control.mak

ifeq (TRUE, $(F1))
zhl+= -D__F1__
endif
ifeq (TRUE, $(F2))
zhl+= -D__F2__
endif
ifeq (TRUE, $(F3))
zhl+= -D__F3__
endif
ifeq (TRUE, $(F4))
zhl+= -D__F4__
endif

f1.o:f1.cpp
	g++ -c f1.cpp
f2.o:f2.cpp
	g++ -c f2.cpp
f3.o:f3.cpp
	g++ -c f3.cpp
f4.o:f4.cpp
	g++ -c f4.cpp
main.o:main.cpp
	g++ -c $(zhl) main.cpp
main:f1.o f2.o f3.o f4.o main.o
	g++ -o main $^
clean:
	rm *.o main
