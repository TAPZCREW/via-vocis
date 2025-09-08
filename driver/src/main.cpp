#include <ntddk.h>

#include <wdf.h>

auto driver_main() -> NTSTATUS {
    DbgPrint("Via vocis: Driver loaded\n");
    return STATUS_SUCCESS;
}

auto driver_exit(DRIVER_OBJECT* driver_object) {
    DbgPrint("Via vocis: Driver stopped\n");
}

extern "C" auto DriverEntry(DRIVER_OBJECT* driver_object, UNICODE_STRING* registry_path)
  -> NTSTATUS {
    driver_object->DriverUnload = driver_exit;
    return driver_main();
}
