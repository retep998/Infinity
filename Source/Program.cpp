#include "Global.h"
#include "Common.h"
static char buf[0x1000];
void Program::Create() {
    p = glCreateProgram();
}
void Program::Attach(Shader s) {
    glAttachShader(p, s.s);
}
void Program::Link() {
    glLinkProgram(p);
	glGetProgramInfoLog(p, 0x1000, 0, buf);
	Log << buf << flush;
    GLint linked;
    glGetProgramiv(p, GL_LINK_STATUS, &linked);
	if (!linked) abort();
}
void Program::Use() {
   glUseProgram(p);
}
void Program::BindAttrib(GLuint index, string name) {
    glBindAttribLocation(p, index, name.c_str());
    glEnableVertexAttribArray(index);
}
GLint Program::UniformLoc(string name) {
    return glGetUniformLocation(p, name.c_str());
}