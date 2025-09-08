#include <ntddk.h>

#include <wdf.h>

auto driver_unload_event(WDFDRIVER) -> void {
    DbgPrint("Driver unloaded\n");
}

auto driver_main() -> NTSTATUS {
    DbgPrint("Driver loaded\n");

    return STATUS_SUCCESS;
}

extern "C" auto DriverEntry(PDRIVER_OBJECT driver_object, PUNICODE_STRING registry_path)
  -> NTSTATUS {
    return driver_main();
}
