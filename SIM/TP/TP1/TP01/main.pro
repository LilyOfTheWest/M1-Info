GLEW_PATH = C:/glew-1.13.0/
GLM_PATH  = C:/glm/

TEMPLATE  = app
TARGET    = tp01

#LIBS     += -Wl,-rpath $${GLEW_PATH}/lib/Release/Win32/ -L$${GLEW_PATH}/lib/Release/Win32/
#LIBS     += -lglew32 -lglut -lm
#INCLUDEPATH  += $${GLEW_PATH}/include/GL  $${GLM_PATH}

LIBS += -lglew32


SOURCES   = main.cpp viewer.cpp
HEADERS   = viewer.h

CONFIG   += qt opengl warn_on thread uic4 release
QT       += xml opengl core gui

INCLUDEPATH += C:/glew-1.13.0/include/GL
LIBS += -Lc:C:/glew-1.13.0/lib/Release/Win32/

#INCLUDEPATH += C:/glm/
