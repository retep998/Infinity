class Buffer {
public:
    enum Type : GLenum {
        Stream = 0x88E0,
        Static = 0x88E4,
        Dynamic = 0x88E8,
        Draw = 0x0,
        Read = 0x1,
        Copy = 0x2,
        Points = 0x0,
        Lines = 0x1,
        LineLoop = 0x2
    };
    void Create(uint32_t, Type, void*);
private:
    GLuint b;
};