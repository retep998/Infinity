class Shader {
public:
    enum Type : GLenum {
        Vertex = GL_VERTEX_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
        Geometry = GL_GEOMETRY_SHADER
    };
    Shader();
    Shader(string, Type);
    void Load(string, Type);
private:
    GLuint s;
    Type t;
    friend class Program;
};