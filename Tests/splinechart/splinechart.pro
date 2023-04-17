QT += charts

SOURCES += \
    main.cpp \
    my_thread.cpp

target.path = $$[QT_INSTALL_EXAMPLES]/charts/splinechart
INSTALLS += target

HEADERS += \
    my_thread.h
