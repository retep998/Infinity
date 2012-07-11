#include "Global.h"
GLshort buf[0x20000];
Chunk::Chunk() {
    Pos[0] = 0, Pos[1] = 0;
    N[0] = nullptr, N[1] = nullptr, N[2] = nullptr, N[3] = nullptr;
    for (int x = 0, i = 0; x < 0x100; ++x) {
        for (int y = 0; y < 0x100; ++y, i += 2) {
            buf[i+0] = x;
            buf[i+1] = y;
        }
    }
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 0x40000, buf, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Chunk::Render() {
    glLoadIdentity();
    glScaled(4/800., 4/600., 1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexPointer(2, GL_SHORT, 0, 0);
    glDrawArrays(GL_POINTS, 0, 0x10000);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}