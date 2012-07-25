template <int N, typename T>
class Vector {
public:
    T& operator[](int n) {
        return Value[n];
    }
protected:
    union {
        T Value[N];
    };
};
template <typename T>
class Vector2 {
public:
    T& operator[](int n) {
        return Value[n];
    }
    union {
        T Value[2];
        struct {
            T X, Y;
        };
    };
};
typedef Vector2<uint64_t> Vector2u64;
typedef Vector2<uint32_t> Vector2u32;
typedef Vector2<uint16_t> Vector2u16;
typedef Vector2<uint8_t> Vector2u8;
typedef Vector2<int64_t> Vector2i64;
typedef Vector2<int32_t> Vector2i32;
typedef Vector2<int16_t> Vector2i16;
typedef Vector2<int8_t> Vector2i8;
typedef Vector2<float> Vector2f32;
typedef Vector2<double> Vector2f64;

