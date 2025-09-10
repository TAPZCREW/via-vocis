module;

#include <ntddk.h>

#include <wdf.h>

export module device;

import log;
import result;

export namespace via {
    auto add_device() -> Result<int, NTSTATUS>;
}

module :private;

namespace via {
    auto add_device() -> Result<int, NTSTATUS> {
        return Unexpected { NTSTATUS { 2 } };
    }
} // namespace via
