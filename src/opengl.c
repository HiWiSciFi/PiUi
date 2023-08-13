#include "opengl.h"
#include <stdio.h>

void HandleGLErrors() {
	GLenum error;
	while ((error = glGetError()) != GL_NO_ERROR) {
		fprintf(stderr, "GL Error: ");
		switch (error) {
		case GL_NO_ERROR:                      fprintf(stderr, "GL_NO_ERROR\n");                      break;
		case GL_INVALID_ENUM:                  fprintf(stderr, "GL_INVALID_ENUM\n");                  break;
		case GL_INVALID_VALUE:                 fprintf(stderr, "GL_INVALID_VALUE\n");                 break;
		case GL_INVALID_OPERATION:             fprintf(stderr, "GL_INVALID_OPERATION\n");             break;
		case GL_OUT_OF_MEMORY:                 fprintf(stderr, "GL_OUT_OF_MEMORY\n");                 break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: fprintf(stderr, "GL_INVALID_FRAMEBUFFER_OPERATION\n"); break;
		default: fprintf(stderr, "unknown error\n");
		}
	}
	fflush(stderr);
}
