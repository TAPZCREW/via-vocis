add_requires("qt6core", "qt6gui", "qt6qml", "qt6quick", "qt6base")

target("via-vocis-qt", function()
  set_languages("c++26")

  add_rules("qt.quickapp")
  add_rules("platform.windows.subsystem")

  add_files("src/*.cpp", "src/**.qrc")

  set_policy("build.c++.modules", true)

  add_frameworks("QtQuickControls2")

  set_values("windows.subsystem", "console")
end)
