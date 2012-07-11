class Chunk {
public:
    Chunk();
    void Render();
    static void Init();
private:
    Block Blocks[0x10000];
    Vector2u64 Pos;
    Chunk* N[4];//The four neighboring chunks: x++, x--, y++, y--
    GLuint Tex;
};