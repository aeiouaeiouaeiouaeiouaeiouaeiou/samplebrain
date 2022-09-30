cmake_minimum_required(VERSION 3.16)
project(samplebrain VERSION 1.0 LANGUAGES C CXX)

include(Dependencies.cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set up AUTOMOC and some sensible defaults for runtime execution
# When using Qt 6.3, you can replace the code block below with
# qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
include(GNUInstallDirs)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Widgets)

qt_add_executable(samplebrain WIN32 MACOSX_BUNDLE
    app/MainWindow.cpp app/MainWindow.h
    app/SettingsDialog.cpp app/SettingsDialog.h
    app/audio_thread.cpp
    app/feedback.cpp
    app/process_thread.cpp
    app/qtmain.cpp
    app/sound_items.cpp
    brain/src/aquila/filter/MelFilter.cpp
    brain/src/aquila/filter/MelFilterBank.cpp
    brain/src/aquila/transform/Dct.cpp
    brain/src/block.cpp
    brain/src/block_stream.cpp
    brain/src/brain.cpp
    brain/src/fft.cpp
    brain/src/mfcc.cpp
    brain/src/renderer.cpp
    brain/src/search_params.cpp
    brain/src/spiralcore/OSC_server.cpp
    brain/src/spiralcore/allocator.cpp
    brain/src/spiralcore/audio.cpp
    brain/src/spiralcore/command_ring_buffer.cpp
    brain/src/spiralcore/portaudio_client.cpp
    brain/src/spiralcore/ring_buffer.cpp
    brain/src/spiralcore/sample.cpp
    brain/src/spiralcore/stream.cpp
    brain/src/status.cpp
    brain/src/window.cpp
    gui/samplebrain.ui
    gui/settings.ui
)
target_include_directories(samplebrain PRIVATE
    .
    /opt/homebrew/include
    /usr/local/include
    2
    brain/src
)

target_link_libraries(samplebrain PRIVATE
    # Remove: L..
    # Remove: L/opt/homebrew/lib
    # Remove: L/usr/local/lib
    Qt::Core
    Qt::Gui
    Qt::Widgets
    dl
    fftw3
    lo_shared
    m
    portaudio
    pthread
    sndfile
)

target_compile_options(samplebrain PUBLIC
    -O3
    -Wall
    -Wno-unused
    -std=c++11
)


# Resources:
set(samplebrain_resource_files
    "app/images/at.png"
    "app/images/pause.png"
    "app/images/play.png"
    "app/images/record.png"
    "app/images/settings.png"
    "app/images/stop.png"
)

qt_add_resources(samplebrain "samplebrain"
    PREFIX
        "/images"
    BASE
        "app"
    FILES
        ${samplebrain_resource_files}
)

install(TARGETS samplebrain
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Consider using qt_generate_deploy_app_script() for app deployment if
# the project can use Qt 6.3. In that case rerun qmake2cmake with
# --min-qt-version=6.3.
