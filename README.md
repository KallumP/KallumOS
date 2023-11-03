# KallumOS

Welcome to my mock operating system. My vision for this program is to emulate using an operating system.

This program is essentially just that, a program. However when using it, one should be able to feel as though they are using an operating system and not need to leave back to Windows to achieve what they want to achieve. It is of course a working progress, and for a long time, will not be usable in this manner.

Features are being added in all the time, and the release logs can be found [here](releaseNotes.md).

#### OS usage

-   Creating an account:

    1. To start using KOS, click "Create Account" at the bottom of the login screen after opening the app.
    2. Enter your desired username, and password in the respective boxes
    3. Click "Create"
       If all your credentials were correct, the background screen will go green, if there is a problem, the screen will go red.
       (Yes this will be updated in due time to use text based prompts. Bear with me :smirk:)
    4. Click "Back to Login"

-   Logging in:

    1. Enter your user name and password into the respective boxes (I hope you haven't forgotten them already!)
    2. Click "Login"

    Again, if there is a problem with your entries, the screen will go red

-   Opening apps

    -   Once you are logged in, you should be presented with the "App launcher" app. This app allows you to look through the different apps that are available to you. (Try not to be overwhelmed by the ridiculous catelogue of apps and games that you can try)
    -   If you do not see the app launcher, or you want to open another instance of the app launcher, press the "a" key without any KOS process focused in the task bar
    -   Click on the up and down arrows at the top of the app launcher to scroll through the list
    -   From the app launcher you can open any app you want by clicking within the app's red box
    -   An app that is opened should show up in the task bar at the top of your screen

-   Manipulating apps

    -   Each app's process should have a bar that has the app's name displayed on the left side, and some buttons on the right side
    -   To minimize an app, click the blue button to the right
    -   To un minimuze an app, click on its "icon" in the task bar (yes, I know the icons currently do not have any pictures. Bear with me please :unamused:)
    -   To close an app, click on the red button to the right
    -   To move an app's box, click and hold anywhere that isn't a button on the app's bar, then move your mouse
    -   If you are a pro (you probably are if you're using KOS), you can also close apps by opening the "Task Manager". This is also usefull if you cannot find your app in the task bar

-   File manager

    Some apps have file managers (such as the Text Editor). The file manager will allow you to either choose a file, or save to a new file.

    -   Open file:

        When opening a file, you will be shown the different directories and files available in your KOS hard-drive.

        1. You can enter into a directory by clicking on directories listed under the "Directories" section
        2. Select a file you want by clicking on a file that is listed under the "Files" section. Your selected file will turn blue
        3. Click the "Select" button

    -   Save a file:

        When saving a file you will be able to save the app's content to a new file of your choosing

        1. You can enter into a directory by clicking on directories listed under the "Directories" section

        2. Type your file name into the text box at the top next to the "Save" button

-   Kode

    You can program in KOS. From here can you make your own operating system? :grin:

    When opening the app, you will have two lines of kode already written. To start, press the "F5" key and you will see the output in the console at the bottom.

    As you can see, the `out` command allows one to write something to the console.

    If your output does not look like what you expected, press the "F3" button. This turns on debug mode, and you can see what each line of kode was actually doing.

    **Structure**

    -   Your kode consists of statements. A statement is ended by hitting the return key, which will start a new line.
    -   Each statement consists of chunks, which are separated by a space. The first chunk is usually an instruction
    -   To navigate which statement is being written to, you can use the up and down arrow keys. The currently focused statement will be in black, and all others will be in gray.

    **Instructions**

    -   `out`

        As mentioned earlier, out allows you to write to the console. It can either write a string to the console, or the contents of a variable eg: `out <variable name>` or the result of some operation eg: `out 5 + 3`

    -   `int`

        Allows the user to create an integer variable.

        -   To create an int, at least four chunks are required.

            1. The "int" instruction
            2. The name of the int
            3. An equals sign
            4. The value your int should hold. (this can be a single chunk with a static value, or an arithmetic operation)

                eg: `int x = 0`
                eg: `int y = 4 + 5`

        -   To manipulate the int you will need to provide at least three chunks.

            1. The int variable's identifier
            2. An equals sign
            3. The value to assign (this can be a single chunk with a static value, or an arithmetic operation)

    -   `bool`

        Allows the user to create a boolean variable. This variable can be manipulated using different comparators and boolean operations

        -   To create a bool, at least four chunks are needed

            1. The "bool" instruction
            2. The name of the bool
            3. An equals sign
            4. The value your bool should hold. (this can be a single chunk with a static value, or a boolean operation)

                eg: `bool a = true`
                eg: `bool b = 5 <= 4 + 3`
                eg: `bool c = true != false`

        -   To manipulate the bool you will need to provide at least three chunks.

            1. The bool variable's identifier
            2. An equals sign
            3. The value to assign (this can be a single chunk with a static value, or a boolean operation)

    -   Operations

        This is something that resolves to a value. Currently, this can be an arithmetic operation `4 * 5 - 1` or a boolean operation `true == true`.

        -   A valid arithmetic operation will have an odd number of chunks, and follows the following form:

            1. A value (this can be a static value or a variable)
            2. A supported symbol: +, -. /, \*, ^, \*\*)
            3. A value (this can be a static value, a variable, or another operation)

        -   A valid boolean operation is slightly more complicated.
            There are two main types of operation:

            -   Value comparison
                Here, a boolean comparator must be surrounded by two operations. The operations can either be arithmetic (in which case the boolean comparator will evaluate an integer comparison) or pure boolean algebra (in which case the comparator will evaluate a boolean comparison). The two surrounding operations must be of the same type. (You cannot have a boolean value on one side and an arithmetic value on the other)
                It takes the following structure

                1. lSide function
                2. A supported comparator: ==, !=, <, <=, >, >=
                3. rSide function (of the same type as the lSide)

                `eg: 7 + 3 <= 40 - 20`
                `eg: true || false == false`

            -   Pure boolean algebra
                This is where a set of boolean variables are evaluated using boolean operators, and no comparators are present.

                The structure is as follows

                1. Boolean value must be present (this can be a static boolean value or a boolean variable).
                   This value can be preceded by a not operator: !, \`. This operator is treated like a normal chunk, so will have a space between it and the chunk being not-ed
                2. (Optional) Boolean operator followed by another boolean value (this can be a static boolean value or a boolean variable).

        The ability to provide another operation means that this is recursive until the whole operation has been resolved.

        The current order of operations is the order you provide. It will ignore "bidmas" or expected order of boolean algebra from other languages (This may change in the future)

        Where an error is ran into (eg: Dividing by 0) it will output an error to the console, skip that operation and continue resolving the rest of the operation.

#### Development

To make an app for KOS you must inherit from the `Process` class. This gives you access to a few different functions.

-   **Tick(float elapsedTime)**

    This is where all the logic of your program should go. The tick function will let you see how much time has passed since the OS's last tick.

-   **Draw(Point offset)**

    This is where you can draw the components of your app to the screen.

    -   Offset:

        You can use the offset that is passed into this function to store where you should draw things from. The offset that is passed into your Draw function by KOS will be (0,0) by default, but can change if your app is opened by another app. For example, you will probably want to set the offset to the coordinate of the process' "box", to do this, use the code

        ```c++
        offset.Set(new Point(offset.GetX() + position.GetX(), offset.GetY() + position.GetY() + barHeight));
        ```

        > This sets the offset to be at X position of the box, and the y position + the bar height (the bar is the part of the box where you can close and minimise the app)

    -   Draw functions:

        You have several drawing functions available to you to draw to the screen. To use these type
        `#include "kGraphics.h"` at the top of your app. From here you can any of the drawing functions from the kGraphics namespace.

    You are allowed to draw anywhere within the KOS screen, however it is advised to draw within your programs "box". The confines of the box. You can do this by checking the size of the process' box properties `position`, and `size`

-   **Input events**

    To be written

-   **Using buttons and text boxes**

    To be written

-   **Using the file manager**

    To use the file managers, your app should have a FileSelector or FileSaver pointer, and your tick, hover and input event functions should pass through to these file manager pointers (be safe, check for nullptr first)

    Before opening your file managers, verify the file path using `helper.verify(path)`, which allows you to see if the path you are trying to pass to the manager is valid, if it is not then create it using `helper.create(path)`. If this returns false, it means that path could not be created, do not open the file viewer.

    **File selection**

    1. Assign a new FileSelector to your pointer
    2. In the input events, wait for the file selector to be ready using `fileSelector->GetReady()`, which will return true if the user has selected a file
    3. When it is ready, take the selected file path using `fileSelector->GetSelectedFilePath()`, which will return the path that the user selected
    4. Get the file path in relation to the program's hardrive using: fullPath = `"hardDrive/" + std::filesystem::relative(selectedPath, "hardDrive/").string();`
    5. Avoid a memory leak by deleting the FileSelector pointer and setting the pointer to nullptr

    **File saving**

    1. Assign a new FileSaver to your pointer
    2. In the input events, wait for the file selector to be ready using `fileSaver->GetReady()`, which will return true if the user has selected a file
    3. When it is ready, take the selected file path using `fileSaver->GetSelectedFilePath()`, which will return the path that the user entered
    4. Get the file path in relation to the program's hardrive using: fullPath = `"hardDrive/" + std::filesystem::relative(selectedPath, "hardDrive/").string();`
    5. Avoid a memory leak by deleting the FileSelector pointer and setting the pointer to nullptr
