#include "Global.h"
void Program::Create() {
    p = glCreateProgram();
}
void Program::Attach(Shader s) {
    glAttachShader(p, s.s);
}
void Program::Link() {
    glLinkProgram(p);
    GLint len;
	glGetProgramiv(p, GL_INFO_LOG_LENGTH , &len);
    unique_ptr<GLchar> log(new GLchar[len]);
	glGetProgramInfoLog(p, len, 0, log.get());
	cout << log.get() << flush;
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