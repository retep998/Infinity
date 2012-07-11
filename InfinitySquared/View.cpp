#include "Global.h"
namespace View {
    uint32_t Width, Height;
    void Resize(uint32_t width, uint32_t height) {
        glViewport(0, 0, width, height);
        Width = width;
        Height = height;
    }
}