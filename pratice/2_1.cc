#include "sb6.h"

class my_application : public sb6::application{
public:
	void render(double currentTime)
	{
		static const GLfloat red[] = {1.0f,0.0f,0.0f,1.0f};
		glClearBufferfv(GL_COLOR, 0, red);
	}
};

DECLARE_MAIN(my_application);