GL_INCLUDE = /usr/X11R6/include
GL_LIB = /usr/X11R6/lib

main: main.o Util.o Sphere.o Plane.o Vector3.o Colour.o Material.o Primitive.o
	g++ -o main $^ -L$(GL_LIB) -lm -lGL -lglut -lGLEW

.cpp.o:
	g++ -std=gnu++0x -c -o $@ $< -I$(GL_INCLUDE)

clean:
	rm -f main *.o
