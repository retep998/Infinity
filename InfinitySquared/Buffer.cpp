#include "Global.h"
void Buffer::Create(uint32_t size, Type type, void* data) {
    glGenBuffers(1, &b);
    glBindBuffer(GL_ARRAY_BUFFER, b);
    glBufferData(GL_ARRAY_BUFFER, size, data, type);
}