template <int N, typename T>
class Vector {
public:
    T& operator[](int n) {
        return Value[n];
    }
protected:
    T Value[N];
};
template <typename T>
class Vector2 : public Vector<2, T> {
public:
    T& X() {
        return this->Value[0];
    }
    T& Y() {
        return this->Value[1];
    }
};
typedef Vector2<uint64_t> Vector2u64;

