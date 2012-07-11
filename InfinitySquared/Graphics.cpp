#include "Global.h"
namespace Graphics {
    void Init() {
        glClearColor(0, 0, 1, 1);
        glEnable(GL_VERTEX_ARRAY);
    }
    void Clear() {
        glClear(GL_COLOR_BUFFER_BIT);
    }
}