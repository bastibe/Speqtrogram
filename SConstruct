env = Environment(tools=["default", "qt4"])

env.EnableQt4Modules(["QtGui", "QtCore"])

env.Append(
    CCFLAGS = "-O2 -march=native -Wall -Wextra",
    LIBS    = "portaudio",
)

sources = Glob("*.cpp")
ui      = env.Uic4("mainwindow.ui")
uim     = env.Moc4(ui)

env.Program("Speqtrogram", [sources, uim])
