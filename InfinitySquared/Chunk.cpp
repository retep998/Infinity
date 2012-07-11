#include "Global.h"
const int dim = 0x100;
const int num = dim*dim;
GLshort buf[0x200000];
Program prog;
GLuint vbo, ttex;
Chunk::Chunk() {
    Pos[0] = 0, Pos[1] = 0;
    N[0] = nullptr, N[1] = nullptr, N[2] = nullptr, N[3] = nullptr;

    glGenTextures(1, &Tex);
    glBindTexture(GL_TEXTURE_2D, Tex);
    mt19937 engine;
    uniform_int_distribution<GLushort> dist;
    for (int y = 0, i = 0; y < 0x100; ++y) {
        for (int x = 0; x < 0x100; ++x, ++i) {
            Blocks[i].id = dist(engine);
        }
    }
    glTexImage2D(GL_TEXTURE_2D, 0, 1, 0x100, 0x100, 0, GL_RED, GL_UNSIGNED_SHORT, Blocks);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
}
void Chunk::Init() {
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    for (int y = 0, i = 0; y < 0x100; ++y) {
        for (int x = 0; x < 0x100; ++x, i += 0x10) {
            buf[i+0x0] = x, buf[i+0x1] = y, buf[i+0x2] = 0, buf[i+0x3] = 0;
            buf[i+0x4] = x, buf[i+0x5] = y, buf[i+0x6] = 1, buf[i+0x7] = 0;
            buf[i+0x8] = x, buf[i+0x9] = y, buf[i+0xA] = 1, buf[i+0xB] = 1;
            buf[i+0xC] = x, buf[i+0xD] = y, buf[i+0xE] = 0, buf[i+0xF] = 1;
        }
    }
    glBufferData(GL_ARRAY_BUFFER, 0x200000, buf, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    prog.Create();
    prog.Attach(Shader("ChunkFrag", Shader::Fragment));
    prog.Attach(Shader("ChunkVert", Shader::Vertex));
    prog.Link();
    prog.BindAttrib(0, "pos");
    prog.BindAttrib(1, "tpos");
    
    glGenTextures(1, &ttex);
    glBindTexture(GL_TEXTURE_2D_ARRAY, ttex);
    mt19937 engine;
    uniform_int_distribution<GLuint> dist;
    sf::Image img;
    img.loadFromFile("tiles.png");
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, 16, 16, 6, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr());
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}
void Chunk::Render() {
    prog.Use();
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 2, GL_SHORT, GL_FALSE, 8, 0);
    glVertexAttribPointer(1, 2, GL_SHORT, GL_FALSE, 8, (GLvoid*)4);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Tex);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D_ARRAY, ttex);
    glUniform1i(prog.UniformLoc("tex"), 0);
    glUniform1i(prog.UniformLoc("ttex"), 1);
    glUniform2f(prog.UniformLoc("vsize"), View::Size.X(), View::Size.Y());
    glUniform2f(prog.UniformLoc("vpos"), Pos.X()-View::Pos.X()-View::Posf.X(), Pos.Y()-View::Pos.Y()-View::Posf.Y());
    glDrawArrays(GL_QUADS, 0, 0x40000);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}