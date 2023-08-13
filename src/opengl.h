#ifndef _WIN32
	#include <GLES3/gl3.h>
#else
	#include <glad/glad.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

	void HandleGLErrors();

#ifdef __cplusplus
}
#endif
