#include "Global.h"
namespace Graphics {
    void Init() {
        glClearColor(0, 0, 1, 1);
        glEnable(GL_VERTEX_ARRAY);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    void Clear() {
        glClear(GL_COLOR_BUFFER_BIT);
    }
}