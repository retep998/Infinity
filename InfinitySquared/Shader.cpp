#include "Global.h"
map<string, GLuint> Shaders;
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
    s = glCreateShader(t);
    Shaders[name] = s;
    ifstream file(name+".glsl");
    string text;
    getline(file, text, '\0');
    const GLchar* t = text.c_str();
    glShaderSource(s, 1, &t, nullptr);
    glCompileShader(s);
    GLint len;
	glGetShaderiv(s, GL_INFO_LOG_LENGTH , &len);
    unique_ptr<GLchar> log(new GLchar[len]);
	glGetShaderInfoLog(s, len, 0, log.get());
	cout << log.get() << flush;
    GLint compiled;
    glGetShaderiv(s, GL_COMPILE_STATUS, &compiled);
	if (!compiled) abort();
}