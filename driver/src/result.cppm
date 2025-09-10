module;

#include <string.h>

#ifdef __has_builtin
// #define HAS_HAS_BUILTIN
#endif

export module result;

export extern "C++" void* operator new(size_t, void* ptr) {
    return ptr;
}

namespace via::meta::details {
    template<bool B, typename T, typename F>
    struct Conditional {
        using Type = T;
    };

    template<typename T, typename F>
    struct Conditional<false, T, F> {
        using Type = F;
    };

    template<typename T>
    struct RemoveReference {
        using Type = T;
    };

    template<typename T>
    struct RemoveReference<T&> {
        using Type = T;
    };

    template<typename T>
    struct RemoveReference<T&&> {
        using Type = T;
    };

#ifdef __clang__
    template<typename T>
    static constexpr auto IsConst = __is_const(T);
#else
    template<typename T>
    static constexpr auto IsConst = false;

    template<typename T>
    static constexpr auto IsConst<const T> = true;
#endif

#ifdef __clang__
    template<typename T>
    static constexpr auto IsRValueReference = __is_rvalue_reference(T);
#else
    template<typename T>
    static constexpr auto IsRValueReference = false;

    template<typename T>
    static constexpr auto IsRValueReference<T&&> = true;
#endif

#ifdef __clang__
    template<typename T>
    static constexpr auto IsLValueReference = __is_lvalue_reference(T);
#else
    template<typename T>
    static constexpr auto IsLValueReference = false;

    template<typename T>
    static constexpr auto IsLValueReference<T&> = true;
#endif

#ifdef __clang__
    template<typename T>
    static constexpr auto IsReference = __is_reference(T);
#else
    template<typename T>
    static constexpr auto IsReference = IsLValueReference<T> or IsRValueReference<T>;
#endif

#ifdef __clang__
    template<typename T, typename U>
    static constexpr auto Is = __is_same(T, U);
#else
    template<typename T, typename U>
    static constexpr auto Is = false;

    template<typename T>
    static constexpr auto Is<T, T> = true;
#endif

#ifdef __clang__
    template<typename T>
    static constexpr auto Is<T, void> = __is_void(T);
#endif
} // namespace via::meta::details

export namespace via {
    namespace meta {
        template<bool B, typename T, typename F>
        using ConditionalType = typename details::Conditional<B, T, F>::Type;

        template<typename T>
        using RemoveReferenceType = typename details::RemoveReference<T>::Type;

        template<typename T>
        concept IsCopyable = __is_constructible(T, const T&) or __is_assignable(T, const T&);

        template<typename T>
        concept IsMovable = __is_constructible(T, T&&) or __is_assignable(T, T&&);

        template<typename T>
        concept IsConst = details::IsConst<T>;

        template<typename T>
        concept IsReference = details::IsReference<T>;

        template<typename T>
        concept IsRValueReference = details::IsRValueReference<T>;

        template<typename T>
        concept IsLValueReference = details::IsLValueReference<T>;

        template<typename T, typename U>
        concept Is = details::Is<T, U>;

        template<typename T, typename... Us>
        concept IsOneOf = (Is<T, Us> and ...);
    } // namespace meta

    template<typename T>
    constexpr auto as_const(T& value) -> const T& {
        return value;
    }

    template<typename T>
    constexpr auto move(T&& value) -> T&& {
        return static_cast<T&&>(value);
    }

    template<typename T>
    constexpr auto forward(meta::RemoveReferenceType<T>& value) -> T&& {
        return static_cast<T&&>(value);
    }

    template<typename T>
    constexpr auto forward(meta::RemoveReferenceType<T>&& value) -> T&& {
        return static_cast<T&&>(value);
    }

    template<typename T, typename U>
    constexpr auto forward_like(U&& value) -> auto&& {
        constexpr auto is_adding_const = meta::IsConst<meta::RemoveReferenceType<T>>;
        if constexpr (meta::IsLValueReference<T&&>) {
            if constexpr (is_adding_const) return as_const(value);
            else
                static_cast<U&>(value);
        } else {
            if constexpr (is_adding_const) return move(as_const(value));
            else
                return move(value);
        }
    }

    template<typename T>
        requires(meta::IsCopyable<T> or meta::IsMovable<T>)
    constexpr auto exchange(T& value, T&& with) -> T {
        if constexpr (meta::IsMovable<T>) {
            auto temp = move(value);
            value     = move(with);
            return temp;
        }
    }

    template<class To, class From>
        requires(sizeof(To) == sizeof(From))
    constexpr auto bit_cast(const From& src) noexcept -> To {
        auto dst = To {};
        memcpy(&dst, &src, sizeof(To));
        return dst;
    }

    template<typename E>
    struct Unexpected {
        E error;
    };

    template<typename T, typename E>
    class Result {
        static constexpr auto BYTE_COUNT = [] static {
            if constexpr (sizeof(T) > sizeof(E)) return sizeof(T);
            else
                return sizeof(E);
        }();
        using AlignedType = meta::ConditionalType<(sizeof(T) > sizeof(E)), T, E>;

      public:
        constexpr Result() = default;

        constexpr ~Result() { destroy(); }

        constexpr Result(Result&& other)
            requires(meta::IsCopyable<T> and meta::IsCopyable<E>
                     or meta::IsMovable<T> and meta::IsMovable<E>)
        {
            memcpy(m_data, other.m_data, BYTE_COUNT);
            m_status = exchange(other.m_status, Status::EMPTY);
        }

        constexpr Result(const Result& other)
            requires(meta::IsCopyable<T> and meta::IsCopyable<E>)
        {
            memcpy(m_data, other.m_data, BYTE_COUNT);
            m_status = other.m_status;
        }

        constexpr auto operator=(Result&& other) -> Result&
            requires(meta::IsCopyable<T> and meta::IsCopyable<E>
                     or meta::IsMovable<T> and meta::IsMovable<E>)
        {
            if (&other == this) return *this;

            destroy();
            memcpy(m_data, other.m_data, BYTE_COUNT);
            m_status = exchange(other.m_status, Status::EMPTY);
            return *this;
        }

        constexpr auto operator=(const Result& other) -> Result&
            requires(meta::IsCopyable<T> and meta::IsCopyable<E>
                     or meta::IsMovable<T> and meta::IsMovable<E>)
        {
            if (&other == this) return *this;

            destroy();
            memcpy(m_data, other.m_data, BYTE_COUNT);
            m_status = exchange(other.m_status, Status::EMPTY);
            return *this;
        }

        constexpr Result(const T& value) : m_status { Status::VALUE } { new (m_data) T { value }; }

        constexpr Result(T&& value) : m_status { Status::VALUE } { new (m_data) T { move(value) }; }

        constexpr Result(const Unexpected<E>& value) : m_status { Status::ERROR } {
            new (m_data) E { value.error };
        }

        constexpr Result(Unexpected<E>&& value) : m_status { Status::ERROR } {
            new (m_data) E { move(value.error) };
        }

        constexpr auto operator=(const T& value) -> Result& {
            destroy();
            new (m_data) T { value };
            return *this;
        }

        constexpr auto operator=(T&& value) -> Result& {
            destroy();
            new (m_data) T { move(value) };
            return *this;
        }

        constexpr auto operator=(const Unexpected<E>& value) -> Result& {
            destroy();
            new (m_data) T { value };
            return *this;
        }

        constexpr auto operator=(Unexpected<E>&& value) -> Result& {
            destroy();
            new (m_data) T { move(value) };
            return *this;
        }

        template<typename Self>
        constexpr auto error(this Self&& self) -> decltype(forward_like<Self>(*self.error_ptr())) {
            return forward_like<Self>(*self.error_ptr());
        }

        template<typename Self>
        constexpr auto value(this Self&& self) -> decltype(forward_like<Self>(*self.value_ptr())) {
            return forward_like<Self>(*self.value_ptr());
        }

        template<typename Self>
        constexpr auto operator*(this Self&& self)
          -> decltype(forward_like<Self>(*self.value_ptr())) {
            return forward_like<Self>(*self.value_ptr());
        }

        template<typename Self, typename Func>
        constexpr auto and_then(this Self&& self, Func&& then)
          -> decltype(then(forward_like<Self>(*self.value_ptr()))) {
            if (self.m_status != Status::VALUE) return forward<Self>(self);

            return then(forward<Self>(self));
        }

        template<typename Self, typename Func>
        constexpr auto map(this Self&& self, Func&& then)
          -> Result<decltype(then(forward_like<Self>(*self.value_ptr()))), E> {
            using To = Result<decltype(then(forward_like<Self>(*self.value_ptr()))), E>;
            if (self.m_status != Status::VALUE) return To { forward<Self>(self).error() };

            auto& value = *self.value_ptr();
            if constexpr (meta::IsOneOf<Self, Result&&, const Result&&>) {
                self.m_status = Status::EMPTY;
                return then(move(value));
            } else {
                return then(value);
            }
        }

        template<typename Self, typename Func>
        constexpr auto or_else(this Self&& self, Func&& then)
          -> decltype(then(forward_like<Self>(*self.error_ptr()))) {
            if (self.m_status == Status::VALUE) return forward<Self>(self);

            return then(forward<Self>(self));
        }

        template<typename Self, typename Func>
        constexpr auto map_error(this Self&& self, Func&& then)
          -> Result<T, decltype(then(forward_like<Self>(*self.error_ptr())))> {
            if (self.m_status == Status::VALUE) return forward<Self>(self);

            auto& value = *self.error_ptr();
            if constexpr (meta::IsOneOf<Self, Result&&, const Result&&>) {
                self.m_status = Status::EMPTY;
                return then(move(value));
            } else {
                return then(value);
            }
        }

      private:
        enum class Status : char {
            EMPTY,
            VALUE,
            ERROR,
        };

        constexpr auto value_ptr() -> T* { return bit_cast<T*>(&m_data[0]); }

        constexpr auto error_ptr() -> E* { return bit_cast<E*>(&m_data[0]); }

        constexpr auto destroy() -> void {
            if (m_status == Status::VALUE) value_ptr()->~T();
            else if (m_status == Status::ERROR)
                error_ptr()->~E();

            m_status = Status::EMPTY;
        }

        Status m_status = Status::EMPTY;
        alignas(AlignedType) char m_data[BYTE_COUNT];
    };
} // namespace via
