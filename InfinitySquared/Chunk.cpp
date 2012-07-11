#include "Global.h"
const int dim = 0x100;
const int num = dim*dim;
GLshort buf[0x200000];
Program prog;
GLuint vbo;
Chunk::Chunk() {
    Pos[0] = 0, Pos[1] = 0;
    N[0] = nullptr, N[1] = nullptr, N[2] = nullptr, N[3] = nullptr;
    for (int y = 0, i = 0; y < 0x100; ++y) {
        for (int x = 0; x < 0x100; ++x, ++i) {
            Blocks[i].id = rand();
        }
    }
    glGenTextures(1, &Tex);
    glBindTexture(GL_TEXTURE_2D, Tex);
    glTexImage2D(GL_TEXTURE_2D, 0, 1, 0x100, 0x100, 0, GL_RED, GL_UNSIGNED_SHORT, Blocks);
    glBindTexture(GL_TEXTURE_2D, 0);
}
void Chunk::Render() {
    glLoadIdentity();
    glScaled(32/800., 32/600., 1);
    prog.Use();
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexPointer(2, GL_SHORT, 8, 0);
    glDrawArrays(GL_QUADS, 0, 0x40000);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Chunk::Init() {
    for (int y = 0, i = 0; y < 0x100; ++y) {
        for (int x = 0; x < 0x100; ++x, i += 0x10) {
            buf[i+0x0] = x, buf[i+0x1] = y, buf[i+0x2] = 0, buf[i+0x3] = 0;
            buf[i+0x4] = x, buf[i+0x5] = y, buf[i+0x6] = 1, buf[i+0x7] = 0;
            buf[i+0x8] = x, buf[i+0x9] = y, buf[i+0xA] = 1, buf[i+0xB] = 1;
            buf[i+0xC] = x, buf[i+0xD] = y, buf[i+0xE] = 0, buf[i+0xF] = 1;
        }
    }
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 0x200000, buf, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    prog.Create();
    prog.Attach(Shader("ChunkFrag", Shader::Fragment));
    prog.Attach(Shader("ChunkVert", Shader::Vertex));
    prog.Link();
}