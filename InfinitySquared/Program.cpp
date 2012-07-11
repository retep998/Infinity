#include "Global.h"
Program::Program() {
    p = glCreateProgram();
}
void Program::Attach(Shader s) {
    glAttachShader(p, s.s);
}
void Program::Link() {
    glLinkProgram(p);
    GLint len;
	glGetProgramiv(p, GL_INFO_LOG_LENGTH , &len);
    GLchar* log = new GLchar[len];
	glGetProgramInfoLog(p, len, 0, log);
	cout << log << flush;
    delete log;
    GLint linked;
    glGetProgramiv(p, GL_LINK_STATUS, &linked);
	if (!linked) abort();
}