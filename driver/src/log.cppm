module;

#include <ntddk.h>

#include <wdf.h>

export module log;

import string_view;

export namespace via {
    auto debug_log(StringView str) -> void;
    auto debug_logln(StringView str) -> void;
} // namespace via

module :private;

namespace via {
    auto debug_log(StringView str) -> void {
        DbgPrint("Via vocis: ");
        DbgPrint(str.data());
    }

    auto debug_logln(StringView str) -> void {
        debug_log(str);
        DbgPrint("\n");
    }
} // namespace via
