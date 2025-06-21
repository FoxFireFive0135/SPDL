Simple Pixel Drawing Library (SPDL)
————————————————————————————————
I made this to more easily draw pixels without having to use SDL or OpenGL or anything else.



How to use
————————————————————————————————
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



What SPDL Implements
————————————————————————————————
struct SPDL_App {
    int width = 800;
    int height = 600;
    LPCWSTR window_title = L"SPDL Window";
    LPCWSTR class_name = L"spdl_window";
    MSG msg{};
    HWND hwnd = nullptr;
    HDC hdc = nullptr;
    HBITMAP bitmap = nullptr;
    uint32_t* framebuffer = nullptr;
};

SPDL_InitWindow(SPDL_App& app, HINSTANCE hInstance, int nCmdShow)
BOOL SPDL_PendingMsg(SPDL_App& app)
SPDL_PresentScreen(SPDL_App& app)

SPDL_DrawPixel(SPDL_App& app, int32_t x, int32_t y, uint32_t color)
SPDL_DrawLine(SPDL_App& app, int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color)
SPDL_ClearScreen(SPDL_App& app, uint32_t color)