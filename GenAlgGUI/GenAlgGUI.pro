QT += widgets
QT += charts

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
           InputMenu.cpp \
           ExperimentWindow.cpp \
           ../src/sources/DataManager.cpp \
           ../src/sources/GeneticAlgorithm.cpp \
           ../src/sources/Backpack.cpp \
           ../src/sources/Crossover.cpp \
           ../src/sources/Mutation.cpp

HEADERS += InputMenu.h \
            ExperimentWindow.h \
            ../src/headers/DataManager.hpp \
            ../src/headers/GeneticAlgorithm.hpp \
            ../src/headers/Backpack.hpp \
            ../src/headers/Crossover.hpp \
            ../src/headers/Mutation.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
