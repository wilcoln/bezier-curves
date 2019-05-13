# LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lGL -lGLU -lglut -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor
CFLAGS=$(HDR_PATHS) -Wno-deprecated -std=c++11 -std=gnu++11
CC=g++
#CC=gcc

ok : main

.cc.o:
	$(CC) -c -O3 $(CFLAGS) $<

OBJECTS_main = main.o  utils.o Fonction.o callbacks.o


main:  $(OBJECTS_main)
	$(CC) $(OBJECTS_main) -o main $(LINKER_FLAGS)


indenter :
	for i in *.h *.cpp do sed -i~ -f sed.sed  $i done
	indent  *.h *.cpp

clean :
	rm -fr *.o
	touch *.cpp *.h

delete :
	rm -f *.h~
	rm -f *.cpp~
