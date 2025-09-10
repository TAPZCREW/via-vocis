#include <ntddk.h>

#include <wdf.h>

import device;
import log;

namespace via {
    auto driver_main() -> NTSTATUS {
        debug_logln("Driver loaded");

        return *add_device()
                  .map([](auto) static {
                      debug_logln("Device added!");
                      return STATUS_SUCCESS;
                  })
                  .map_error([](NTSTATUS error) static {
                      debug_logln("Failed to add device!");
                      return error;
                  });
    }

    auto driver_exit(DRIVER_OBJECT* driver_object) {
        debug_logln("Driver stopped");
    }
} // namespace via

extern "C" auto DriverEntry(DRIVER_OBJECT* driver_object, UNICODE_STRING* registry_path)
  -> NTSTATUS {
    driver_object->DriverUnload = via::driver_exit;
    return via::driver_main();
}
