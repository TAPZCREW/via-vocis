module;

#include <stdint.h>
#include <string.h>

#include <ntddk.h>

#include <wdf.h>

export module string_view;

export namespace via {
    class StringView {
      public:
        constexpr StringView(const char* str);

        constexpr auto size() const -> size_t;
        constexpr auto data() const -> const char*;

        constexpr auto operator[](size_t i) const -> size_t;

      private:
        const char* m_data;
        size_t      m_size;
    };
} // namespace via

namespace via {
    constexpr StringView::StringView(const char* str) : m_data { str }, m_size { 0 } {
        if consteval {
            auto c = str;
            while (*c != '\0') {
                m_size += 1;
                ++c;
            }
        } else {
            m_size = strlen(m_data);
        }
    }

    constexpr auto StringView::size() const -> size_t {
        return m_size;
    }

    constexpr auto StringView::data() const -> const char* {
        return m_data;
    }

    constexpr auto StringView::operator[](size_t i) const -> size_t {
        if not consteval {
            if (i >= m_size) {
                DbgPrint("OOB access to str ");
                DbgPrint(m_data);
                DbgPrint(" with i = "); // TODO implement int to str
            }
        }
        return m_data[i];
    }
} // namespace via
