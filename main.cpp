#define SPDL_INCLUDE_COLORS //Remove if you dont want the SPDL_Color struct
#define SPDL_INCLUDE_DEFINES //Remove if you want to use the entire wWinMain function, and not SPDL_Main.
#include "SPDL.hpp"

SPDL_App app; //needed for using SPDL.

//SPDL_Main makes it so you don't have to see the ugly and long wWinMain stuff. 
//if you dont like it, then just remove "SPDL_INCLUDE_DEFINES"
int SPDL_Main {
    SPDL_InitWindow(app, hInstance, nCmdShow);

    while (app.msg.message != WM_QUIT) {
        //Handles window events.
        if (SPDL_PendingMsg(app)) {
            TranslateMessage(&app.msg);
            DispatchMessage(&app.msg);
        }
        else {
            //add your code here.

            SPDL_PresentScreen(app); //Puts the pixels on screen. essiential for actually seeing what you drew.
        }
    }

    return 0;
}