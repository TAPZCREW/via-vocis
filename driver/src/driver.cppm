module;

#include <ntddk.h>

#include <wdf.h>

export module device;

import log;

export namespace via {
    auto add_device() -> void;
}

module :private;

namespace via {
    auto add_device() -> void {
        debug_logln("Add device");
    }
} // namespace via
