cmake_minimum_required(VERSION 3.16)

project(lean_02 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)
# set(QML_IMPORT_PATH "D:/download/qt6/6.8.2/msvc2022_64/qml")

find_package(Qt6 REQUIRED COMPONENTS Quick Core5Compat Core)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(applean_02
    main.cpp
    day05/keybackquit.h day05/keybackquit.cpp
)



qt_add_qml_module(applean_02
    URI lean_02
    VERSION 1.0
    QML_FILES
        Main.qml
        QML_FILES day01/ChooseImageDisplay.qml
        QML_FILES day01/MySignal.qml
        QML_FILES day01/ChangeColorRect.qml
        QML_FILES day01/KeyMoveText.qml
        QML_FILES day01/StartTimer.qml
        QML_FILES day02/PinchPhone.qml
        QML_FILES day02/ComponentFile.qml
        QML_FILES day02/ColorPicker.qml
        QML_FILES day02/LoaderTest.qml
        QML_FILES day02/LoaderTestFileInput.qml
        QML_FILES day02/LoaderTestFileInput2.qml
        QML_FILES day02/CreateControls.qml
        QML_FILES day02/CreateControls2.qml
        QML_FILES day03/PreferredMobileOs.qml
        QML_FILES day03/PreferredRadioButton.qml
        QML_FILES day03/PreferredMovies.qml
        QML_FILES day03/PreferredMobiesCheckBox.qml
        QML_FILES day03/ComboboxDemo.qml
        QML_FILES day03/MyCombobox.qml
        QML_FILES day03/ProgressBarDemo.qml
        QML_FILES day03/MyProgressBar.qml
        QML_FILES day04/TabViewSimple.qml
        QML_FILES day04/MyTabView.qml
        QML_FILES day04/MyStackView.qml
        QML_FILES day04/SliderDemo.qml
        QML_FILES day04/FlickableDemo.qml
        QML_FILES day05/CanvasTransform.qml
        QML_FILES day05/AuthCodeItem.qml
        QML_FILES day05/CanvasClipDemo.qml
        QML_FILES day05/CanvasFilesDemo.qml
        QML_FILES day05/CanvasFilesDemoButton.qml
        QML_FILES day06/ColorMakerDemo.qml
        QML_FILES day06/CallQmlDemo.qml
        QML_FILES day06/ImageProcessorDemo.qml
        QML_FILES day06/ImageProcessorButton.qml
        RESOURCES source.qrc
        SOURCES day06/colormaker.h day06/colormaker.cpp
        SOURCES day06/changeqmlcolor.h day06/changeqmlcolor.cpp
        SOURCES day06/imageprocessor.h day06/imageprocessor.cpp
        QML_FILES day07/PropertAnimationStandalone.qml
        QML_FILES day07/PropertyAnimationSwap.qml
        QML_FILES day07/NumberAnimationSquareToCircle.qml
        QML_FILES day07/ColorAnimationRedToGreen.qml
        QML_FILES day07/RotationAnimationDemo.qml
        QML_FILES day07/PathAnimationDemo.qml
        QML_FILES day07/SmoothedAnimationDemo.qml
        QML_FILES day07/SpringAnimationDemo.qml
        QML_FILES day07/SequentialAnimationDemo.qml
        QML_FILES day07/StateDemo.qml
        QML_FILES day07/ParentChangeDemo.qml
        QML_FILES day07/TransitionRectDemo.qml
        QML_FILES day07/Bubbleshot.qml
        QML_FILES day08/PhoneListViewDemo.qml
        QML_FILES day08/PhoneListItemText.qml
        QML_FILES day08/PhoneListDeletage.qml
        QML_FILES day08/VideoListXml.qml
        QML_FILES day08/VideoListViewText.qml
        SOURCES day08/videolistmodel.h day08/videolistmodel.cpp
        SOURCES day08/tablemodel.h day08/tablemodel.cpp
        QML_FILES day08/PhoneTableSimple.qml
        QML_FILES day08/FindImageDemo.qml
        QML_FILES day08/FlatButton.qml
        QML_FILES day08/ImageDigger.qml
        QML_FILES day08/LocalViewer.qml
        QML_FILES day09/SimpleMusic.qml
        QML_FILES day09/SimpleCameraDemo.qml
        QML_FILES day09/FileReaderDemo.qml

)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(applean_02 PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.applean_02
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(applean_02
    PRIVATE Qt6::Quick Qt6::Core5Compat Qt6::Core
)

include(GNUInstallDirs)
install(TARGETS applean_02
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
