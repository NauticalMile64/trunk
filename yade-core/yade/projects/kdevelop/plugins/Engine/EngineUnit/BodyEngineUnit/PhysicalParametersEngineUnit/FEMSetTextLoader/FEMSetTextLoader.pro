# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./plugins/Engine/EngineUnit/BodyEngineUnit/PhysicalParametersEngineUnit/FEMSetTextLoader
# Target is a library:  

LIBS += -lPhysicalParametersMetaEngine \
        -lParticleParameters \
        -lRigidBodyParameters \
        -lFEMSetParameters \
        -lFEMNodeData \
        -lFEMTetrahedronData \
        -lSphere \
        -lTetrahedron \
        -rdynamic 
INCLUDEPATH += $(YADEINCLUDEPATH) 
MOC_DIR = $(YADECOMPILATIONPATH) 
UI_DIR = $(YADECOMPILATIONPATH) 
OBJECTS_DIR = $(YADECOMPILATIONPATH) 
QMAKE_LIBDIR = ../../../../../../plugins/Engine/MetaEngine/BodyMetaEngine/PhysicalParameterMetaEngine/PhysicalParametersMetaEngine/$(YADEDYNLIBPATH) \
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
HEADERS += FEMSetTextLoader.hpp 
SOURCES += FEMSetTextLoader.cpp 
