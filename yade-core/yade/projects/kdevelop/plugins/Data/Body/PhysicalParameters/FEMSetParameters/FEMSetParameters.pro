# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./plugins/Data/Body/PhysicalParameters/FEMSetParameters
# Target is a library:  

LIBS += -lAABB \
        -lPolyhedron \
        -lyade-lib-serialization \
        -lyade-lib-wm3-math \
        -lyade-lib-multimethods \
        -rdynamic 
INCLUDEPATH += $(YADEINCLUDEPATH) 
MOC_DIR = $(YADECOMPILATIONPATH) 
UI_DIR = $(YADECOMPILATIONPATH) 
OBJECTS_DIR = $(YADECOMPILATIONPATH) 
QMAKE_LIBDIR = ../../../../../plugins/Data/Body/BoundingVolume/AABB/$(YADEDYNLIBPATH) \
               ../../../../../plugins/Data/Body/GeometricalModel/Polyhedron/$(YADEDYNLIBPATH) \
               /usr/local/lib/yade/yade-libs/ \
               $(YADEDYNLIBPATH) 
QMAKE_CXXFLAGS_RELEASE += -lpthread \
                          -pthread 
QMAKE_CXXFLAGS_DEBUG += -lpthread \
                        -pthread 
DESTDIR = $(YADEDYNLIBPATH) 
CONFIG += debug \
          warn_on \
          dll 
TEMPLATE = lib 
HEADERS += FEMSetParameters.hpp 
SOURCES += FEMSetParameters.cpp 
