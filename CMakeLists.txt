project(pcro)

find_package(Qt4 4.6.0 REQUIRED)
find_package(KDE4 REQUIRED)

set(pcro_SRS    alsasoundcard.cpp
                main.cpp
                mainwindow.cpp
                qcustomplot.cpp
                           
                alsasoundcard.h
                mainwindow.h
                qcustomplot.h
                ui_mainwindow.h
                )

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${KDE4_ENABLE_EXCEPTIONS})
ADD_DEFINITIONS(${QT_DEFINITIONS})

KDE4_ADD_UI_FILES(pcro_SRS mainwindow.ui)

KDE4_ADD_EXECUTABLE(pcro ${pcro_SRS})

target_link_libraries(pcro    ${KDE4_KDECORE_LIBS}
                              ${KDE4_KDEUI_LIBS}
                              ${QT_QTCORE_LIBRARY}
                              ${QT_QTGUI_LIBRARY}
                              asound
                              )