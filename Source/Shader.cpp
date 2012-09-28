#include "Global.h"
#include "Common.h"
map<string, GLuint> Shaders;
static char buf[0x1000];
Shader::Shader() {
    s = 0;
}
Shader::Shader(string name, Type type) {
    Load(name, type);
}
void Shader::Load(string name, Type type) {
    s = Shaders[name];
    if (s) return;
    t = type;
    Shaders[name] = s = glCreateShader(t);
    ifstream file("Shaders/" + name + ".glsl");
    file.read(buf, 0x1000);
    const GLchar* t = buf;
    glShaderSource(s, 1, &t, nullptr);
    glCompileShader(s);
	glGetShaderInfoLog(s, 0x1000, 0, buf);
	Log << buf << flush;
    GLint compiled;
    glGetShaderiv(s, GL_COMPILE_STATUS, &compiled);
	if (!compiled) abort();
}