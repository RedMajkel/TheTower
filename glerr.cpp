#include "glerr.h"

const char *debug_glerror(GLenum error)
{
	switch (error) {
#define GLERROR_TO_STR(u) case u: return #u
		GLERROR_TO_STR(GL_NO_ERROR);
		GLERROR_TO_STR(GL_INVALID_ENUM);
		GLERROR_TO_STR(GL_INVALID_VALUE);
		GLERROR_TO_STR(GL_INVALID_OPERATION);
		GLERROR_TO_STR(GL_STACK_OVERFLOW);
		GLERROR_TO_STR(GL_STACK_UNDERFLOW);
		GLERROR_TO_STR(GL_OUT_OF_MEMORY);
#undef GLERROR_TO_STR
	default:
		return "unrecognized";
	}
}
GLint checkGLcall(char* tekst, int line, char* file)
{
	GLint err2 = GL_NO_ERROR;
	GLint err = glGetError();
	if (err == GL_NO_ERROR) {
		return err2;
	}
	else do {
		cerr << file << " " << line << ": " << tekst << ": " << debug_glerror(err) << endl;
		err2 = err;
		err = glGetError();
	} while (err != GL_NO_ERROR);
	return err2;
}