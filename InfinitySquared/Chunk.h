class Chunk {
public:
    Chunk();
    void Render();
private:
    Block Blocks[0x100][0x100];
    Vector2u64 Pos;
    Chunk* N[4];//The four neighboring chunks: x++, x--, y++, y--
    GLuint VBO;
};