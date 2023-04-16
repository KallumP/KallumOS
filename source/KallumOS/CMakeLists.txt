cmake_minimum_required(VERSION 3.0)

project(MyProject)

set(SOURCES
    AppLauncher.cpp
    Button.cpp
    Control.cpp
    CreateAccount.cpp
    Desktop.cpp
    Input.cpp
    KallumOS.cpp
    Kode.cpp
    Login.cpp
    main.cpp
    Process.cpp
    State.cpp
    Taskbar.cpp
    TaskManager.cpp
    Tetris.cpp
    TextBox.cpp
    TextEditor.cpp
    TicTak.cpp
)

set(HEADERS
    AppLauncher.h
    Button.h
    Control.h
    CreateAccount.h
    Dektop.h
    Helper.h
    Input.h
    InputPress.h
    KallumOS.h
    Kode.h
    Login.h
    Point.h
    Process.h
    State.h
    TaskBar.h
    TaskManager.h
    Tetris.h
    TextEditor.h
    TicTak.h
)

add_executable(MyProject ${SOURCES} ${HEADERS})

target_include_directories(MyProject PUBLIC include)

target_compile_options(MyProject PRIVATE -Wall -Wextra -pedantic -Werror)