# Simple Pixel Drawing Library (SPDL)

I made this to more easily draw pixels without having to use SDL or OpenGL or anything else.

This is a **header-only** library.


---

## How to Use

```cpp
#define SPDL_INCLUDE_COLORS    // allows access to the SPDL_Color struct
#define SPDL_INCLUDE_DEFINES   // includes defines that can help with stuff
#include "SPDL.hpp"
```

```cpp
SPDL_App app; // Required SPDL app struct
```

If `SPDL_INCLUDE_DEFINES` is defined you can use:

```cpp
int SPDL_Main {
    SPDL_InitWindow(app, hInstance, nCmdShow);

    while (app.msg.message != WM_QUIT) {
        if (SPDL_PendingMsg(app)) {
            TranslateMessage(&app.msg);
            DispatchMessage(&app.msg);
        } else {
            // Your rendering code here
            SPDL_PresentScreen(app); // Show the framebuffer on screen
        }
    }

    return 0;
}
```

If you’d rather use `wWinMain` directly, just don't define `SPDL_INCLUDE_DEFINES`

---

## What SPDL Implements

### `struct SPDL_App`

```cpp
struct SPDL_App {
    int width               = 800;
    int height              = 600;
    LPCWSTR window_title    = L"SPDL Window";
    LPCWSTR class_name      = L"spdl_window";
    MSG msg {};
    HWND hwnd               = nullptr;
    HDC hdc                 = nullptr;
    HBITMAP bitmap          = nullptr;
    uint32_t* framebuffer   = nullptr;
};
```

### Core Functions

```cpp
void SPDL_InitWindow(SPDL_App& app, HINSTANCE hInstance, int nCmdShow);
BOOL SPDL_PendingMsg(SPDL_App& app);
void SPDL_PresentScreen(SPDL_App& app);
```

### Drawing Functions

```cpp
void SPDL_DrawPixel(SPDL_App& app, int32_t x, int32_t y, uint32_t color);
void SPDL_DrawLine(SPDL_App& app, int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color);
void SPDL_ClearScreen(SPDL_App& app, uint32_t color);
```

---

## Misc

If `SPDL_INCLUDE_COLORS` is defined, you get access to:

```cpp
SPDL_Color::black
SPDL_Color::blue
SPDL_Color::green
SPDL_Color::cyan
SPDL_Color::red
SPDL_Color::magenta
SPDL_Color::brown
SPDL_Color::light_gray
SPDL_Color::dark_gray
SPDL_Color::light_blue
SPDL_Color::light_green
SPDL_Color::light_cyan
SPDL_Color::light_red
SPDL_Color::light_magenta
SPDL_Color::yellow
SPDL_Color::white
```
