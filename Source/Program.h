class Program {
public:
    void Create();
    void Attach(Shader);
    void Link();
    void Use();
    void BindAttrib(GLuint, string);
    GLint UniformLoc(string);
private:
    GLuint p;
};