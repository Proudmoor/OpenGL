GCC_OPTIONS=-Wall -pedantic 
GL_OPTIONS=-framework OpenGL -lsfml-window -lsfml-system -lsfml-graphics
OPTIONS=$(GCC_OPTIONS) $(GL_OPTIONS)


.cpp: 
	g++ $@.cpp  $(OPTIONS) -o $@ 

