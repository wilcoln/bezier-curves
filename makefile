# LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lGL -lGLU -lglut -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor
CFLAGS=$(HDR_PATHS) -Wno-deprecated
CC=g++
#CC=gcc

ok : OpenGL 

.cc.o:
	$(CC) -c -O3 $(CFLAGS) $<

OBJECTS_main = OpenGL.o  


OpenGL:  $(OBJECTS_main)
	$(CC) $(OBJECTS_main) -o OpenGL $(LINKER_FLAGS)


indenter :
	for i in *.h *.cpp do sed -i~ -f sed.sed  $i done
	indent  *.h *.cpp

clean :
	rm -fr *.o
	touch *.cc #*.h

delete :
	rm -f *.h~
	rm -f *.cc~
