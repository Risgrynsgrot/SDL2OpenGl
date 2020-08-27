namespace Math
{
    template <class T>
    inline T clamp(T value, T min, T max)
    {
        const T t = value < min ? min : value;
        return t > max ? max : t;
    }
} // namespace Math
