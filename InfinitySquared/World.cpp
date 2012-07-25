#include "Global.h"
namespace World {
    //Constants
    const uint32_t BlockSize = 0x10;//Pixels per block
    const uint32_t ChunkSize = 0x20;//Blocks per chunk
    const uint32_t ViewChunkWidth = 800/BlockSize/ChunkSize+2;
    const uint32_t ViewChunkHeight = 600/BlockSize/ChunkSize+2;
    const uint32_t ViewBlockWidth = ViewChunkWidth*ChunkSize;
    const uint32_t ViewBlockHeight = ViewChunkHeight*ChunkSize;
    //OpenGL objects
    GLuint VBO;//A VBO rendered for each chunk
    Program Prog;//The shader for rendering the world
    GLuint TexID;//Texture containing blocks ids
    //Structures
    struct Block {
        uint16_t id;
    };
    struct Chunk {
        Block Blocks[ChunkSize*ChunkSize];
    };
    void Init() {
        {//Initialize the VBO
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            unique_ptr<GLubyte> bufp(new GLubyte[ChunkSize*ChunkSize*0x10]);
            GLubyte* buf = bufp.get();
            for (int y = 0, i = 0; y < ChunkSize; ++y) {
                for (int x = 0; x < ChunkSize; ++x, i += 0x10) {
                    buf[i+0x0] = x, buf[i+0x1] = y, buf[i+0x2] = 0, buf[i+0x3] = 0;
                    buf[i+0x4] = x, buf[i+0x5] = y, buf[i+0x6] = 1, buf[i+0x7] = 0;
                    buf[i+0x8] = x, buf[i+0x9] = y, buf[i+0xA] = 1, buf[i+0xB] = 1;
                    buf[i+0xC] = x, buf[i+0xD] = y, buf[i+0xE] = 0, buf[i+0xF] = 1;
                }
            }
            glBufferData(GL_ARRAY_BUFFER, ChunkSize*ChunkSize*0x10, buf, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
        {//Initialize the ID texture with some random data
            glGenTextures(1, &TexID);
            glBindTexture(GL_TEXTURE_2D, TexID);
            mt19937 engine;
            uniform_int_distribution<GLushort> dist;
            unique_ptr<GLushort> bufp(new GLushort[ViewBlockWidth*ViewBlockHeight]);
            GLushort* buf = bufp.get();
            for (int i = 0; i < ViewBlockWidth*ViewBlockHeight; ++i) {
                buf[i] = dist(engine);
            }
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, ViewBlockWidth, ViewBlockHeight, 0, GL_RED, GL_UNSIGNED_SHORT, buf);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        {
            Prog.Create();
            Prog.Attach(Shader("ChunkFrag", Shader::Fragment));
            Prog.Attach(Shader("ChunkVert", Shader::Vertex));
            Prog.Link();
            Prog.BindAttrib(0, "pos");
            Prog.BindAttrib(1, "tpos");
        }
    }
}
void Chunk::Init() {

    
    
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
    glUniform2f(prog.UniformLoc("vpos"), -View::Pos.X()-View::Posf.X(), -View::Pos.Y()-View::Posf.Y());
    glDrawArrays(GL_QUADS, 0, 0x40000);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
}