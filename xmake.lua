set_policy("build.c++.modules.two_phases", false)
set_policy("build.c++.modules.non_cascading_changes", true)

includes("driver/xmake.lua")
includes("qt-frontend/xmake.lua")
includes("cli-frontend/xmake.lua")
