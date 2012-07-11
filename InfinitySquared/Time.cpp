#include "Global.h"
namespace Time {
    double FPS, Delta;
    high_resolution_clock Clock;
    high_resolution_clock::time_point Start;
    high_resolution_clock::time_point Last;
    void Init() {
        Start = Clock.now();
        Last = Start;
        FPS = 0;
        Delta = 0;
    }
    void Update() {
        high_resolution_clock::time_point now = Clock.now();
        high_resolution_clock::duration dif = now-Last;
        Last = now;
        Delta = duration_cast<duration<double, ratio<1>>>(dif).count();
        if (Delta < 0.0001) Delta = 0.0001;
        if (Delta > 1) Delta = 1;
        FPS = FPS*(1-Delta) + 1;
    }
}