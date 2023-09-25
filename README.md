# KallumOS

Welcome to my mock operating system. My vision for this program is to emulate using an operating system. 

This program is essentially just that, a program. However when using it, one should be able to feel as though they are using an operating system and not need to leave back to Windows to achieve what they want to achieve. It is of course a working progress, and for a long time, will not be usable in this manner. 

Features are being added in all the time, and the release logs can be found here.

#### OS usage

- Create account
    1. To start using KOS, click "Create Account" at the bottom of the login screen after opening the app. 
    2.  Enter your desired username, and password in the respective boxes
    3.  Click "Create"
        If all your credentials were correct, the background screen will go green, if there is a problem, the screen will go red 

        (Yes this will be updated in due time to use text based prompts. Bear with me :))
    
    4. Click "Back to Login"

- Logging in
    1. Enter your user name and password into the respective boxes (I hope you haven't forgotten them already!)
    2. Click "Login"
        Again, if there is a problem with your entries, the screen will go red

- Opening apps
    - Once you are logged in, you should be presented with the "App launcher" app. This app allows you to look through the different apps that are available to you. (Try not to be overwhelmed by the ridiculous catelogue of apps and games that you can try). 
    - If you do not see the app launcher, or you want to open another instance of the app launcher, press the "a" key without any KOS process focused in the task bar
    - Click on the up and down arrows at the top of the app launcher to scroll through the list
    - From the app launcher you can open any app you want by clicking within the app's red box
    - An app that is opened should show up in the task bar at the top of your screen

- Manipulating apps
    - Each app's process should have a bar that has the app's name displayed on the left side, and some buttons on the right side
    - To minimize an app, click the blue button to the right
    - To un minimuze an app, click on its "icon" in the task bar (yes, I know the icons currently do not have any pictures. Bear with me please :()
    - To close an app, click on the red button to the right
    - To move an app's box, click and hold anywhere that isn't a button on the app's bar, then move your mouse.
    - If you are a pro (you probably are if you're using KOS), you can also close apps by opening the "Task Manager". This is also usefull if you cannot find your app in the task bar

- File manager
    Some apps have file managers (such as the Text Editor). The file manager will allow you to either choose a file, or save to a new file.

    - Open file:
        When opening a file, you will be shown the different directories and files available in your KOS hard-drive. 
        1. You can enter into a directory by clicking on directories listed under the "Directories" section
        2. Select a file you want by clicking on a file that is listed under the "Files" section. Your selected file will turn blue
        3. Click the "Select" button

    - Save a file: 
        When saving a file you will be able to save the app's content to a new file of your choosing
        1. You can enter into a directory by clicking on directories listed under the "Directories" section
        2. Type your file name into the text box at the top next to the "Save" button

- Kode

#### Development

To make an app for KOS you must inheret from the `Process` class. This gives you access to a few different functions.
- **Tick(float elapsedTime)**
    This is where all the logic of your program should go. The tick function will let you see how much time has passed since the OS's last tick.
- **Draw(Point offset)**
    This is where you can draw the components of your app to the screen. 
    
    - Offset:
        You can use the offset that is passed into this function to store where you should draw things from. The offset that is passed into your Draw function by KOS will be (0,0) by default, but can change if your app is opened by another app. For example, you will probably want to set the offset to the coordinate of the process' "box", to do this, use the code

        ```c++
        offset.Set(new Point(offset.GetX() + position.GetX(), offset.GetY() + position.GetY() + barHeight));
        ```
        >This sets the offset to be at X position of the box, and the y position + the bar height (the bar is the part of the box where you can close and minimise the app)
    
    - Draw functions:
        You have several drawing functions available to you to draw to the screen. To use these type 
        `#include "kGraphics.h"` at the top of your app. From here you can any of the drawing functions from the kGraphics namespace.   

    You are allowed to draw anywhere within the KOS screen, however it is advised to draw within your programs "box". The confines of the box. You can do this by checking the size of the process' box properties `position`, and `size`

- Inputs

- Using buttons and text boxes

- Using the file manager