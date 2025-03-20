QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    algorithm/inference_settings.cpp \
    algorithm/rheed_image_handle.cpp \
    main.cpp \
    mainwindow.cpp \
    ui/card_layout_panel.cpp \
    ui/detect_info_canvas.cpp \
    ui/rheed_image_handle_thread.cpp \
    ui/rheed_image_handle_ui.cpp \
    ui/rheed_video_handle_thread.cpp \
    ui/rheed_video_handle_ui.cpp

HEADERS += \
    algorithm/inference_settings.h \
    algorithm/rheed_image_handle.h \
    mainwindow.h \
    ui/card_layout_panel.h \
    ui/detect_info_canvas.h \
    ui/rheed_image_handle_thread.h \
    ui/rheed_image_handle_ui.h \
    ui/rheed_video_handle_thread.h \
    ui/rheed_video_handle_ui.h

FORMS += \
    mainwindow.ui

# pro文件中，解决中文乱码
msvc {
      QMAKE_CFLAGS += /utf-8
      QMAKE_CXXFLAGS += /utf-8
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../CodeEnvironment/opencv/build/x64/vc16/lib/ -lopencv_world480
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../CodeEnvironment/opencv/build/x64/vc16/lib/ -lopencv_world480d
else:unix: LIBS += -L$$PWD/../../../CodeEnvironment/opencv/build/x64/vc16/lib/ -lopencv_world480

INCLUDEPATH += $$PWD/../../../CodeEnvironment/opencv/build/include
DEPENDPATH += $$PWD/../../../CodeEnvironment/opencv/build/include

RESOURCES += \
    resources.qrc
