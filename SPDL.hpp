#ifndef SPDL_HPP
#define SPDL_HPP 1

#include <Windows.h>
#include <cstdint>
#include <algorithm>

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

#ifdef SPDL_INCLUDE_COLORS //I'm sure not everyone would want this, so you can choose if you want it or not.
struct SPDL_Color {
    static constexpr uint32_t black = 0xFF000000;
    static constexpr uint32_t blue = 0xFF0000AA;
    static constexpr uint32_t green = 0xFF00AA00;
    static constexpr uint32_t cyan = 0xFF00AAAA;
    static constexpr uint32_t red = 0xFFAA0000;
    static constexpr uint32_t magenta = 0xFFAA00AA;
    static constexpr uint32_t brown = 0xFFAA5500;
    static constexpr uint32_t light_gray = 0xFFAAAAAA;
    static constexpr uint32_t dark_gray = 0xFF555555;
    static constexpr uint32_t light_blue = 0xFF5555FF;
    static constexpr uint32_t light_green = 0xFF55FF55;
    static constexpr uint32_t light_cyan = 0xFF55FFFF;
    static constexpr uint32_t light_red = 0xFFFF5555;
    static constexpr uint32_t light_magenta = 0xFFFF55FF;
    static constexpr uint32_t yellow = 0xFFFFFF55;
    static constexpr uint32_t white = 0xFFFFFFFF;
};
#endif

#ifdef SPDL_INCLUDE_DEFINES //Incase i add anymore defines.
#define SPDL_Main WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
#endif

static inline LRESULT CALLBACK SPDL_WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_CLOSE) {
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

static inline void SPDL_Init(SPDL_App& app) {
    HDC screenDC = GetDC(nullptr);
    app.hdc = CreateCompatibleDC(screenDC);

    BITMAPINFO bi = {};
    bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bi.bmiHeader.biWidth = app.width;
    bi.bmiHeader.biHeight = -app.height;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;

    app.bitmap = CreateDIBSection(app.hdc, &bi, DIB_RGB_COLORS, (void**)&app.framebuffer, nullptr, 0);
    if (!app.bitmap) {
        MessageBox(nullptr, L"Failed to create DIB Section!", L"SPDL Error", MB_ICONERROR | MB_OK);
        ReleaseDC(nullptr, screenDC);
        return;
    }

    SelectObject(app.hdc, app.bitmap);
    ReleaseDC(nullptr, screenDC);
}

inline BOOL SPDL_PendingMsg(SPDL_App& app) {
    return PeekMessage(&app.msg, nullptr, 0, 0, PM_REMOVE);
}

inline void SPDL_PresentScreen(SPDL_App& app) {
    HDC windowDC = GetDC(app.hwnd);
    BitBlt(windowDC, 0, 0, app.width, app.height, app.hdc, 0, 0, SRCCOPY);
    ReleaseDC(app.hwnd, windowDC);
}

inline void SPDL_InitWindow(SPDL_App& app, HINSTANCE hInstance, int nCmdShow) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = SPDL_WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = app.class_name;

    if (!RegisterClass(&wc)) {
        MessageBox(nullptr, L"Failed to register window class!", L"SPDL Error", MB_ICONERROR | MB_OK);
        return;
    }

    DWORD windowStyle = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX;

    app.hwnd = CreateWindow(
        app.class_name, app.window_title,
        windowStyle,
        CW_USEDEFAULT, CW_USEDEFAULT,
        app.width, app.height,
        nullptr, nullptr, hInstance, nullptr
    );

    if (!app.hwnd) {
        MessageBox(nullptr, L"Failed to create window!", L"SPDL Error", MB_ICONERROR | MB_OK);
        return;
    }

    ShowWindow(app.hwnd, nCmdShow);
    SPDL_Init(app);
}

inline void SPDL_DrawPixel(SPDL_App& app, int32_t x, int32_t y, uint32_t color) {
    if (x < 0 || y < 0 || x >= app.width || y >= app.height) return;
    app.framebuffer[y * app.width + x] = color;
}

inline void SPDL_DrawLine(SPDL_App& app, int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color) {
    int32_t dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int32_t dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int32_t err = dx + dy;

    while (true) {
        SPDL_DrawPixel(app, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        int32_t e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

inline void SPDL_ClearScreen(SPDL_App& app, uint32_t color) {
    std::fill(app.framebuffer, app.framebuffer + (app.width * app.height), color);
}

#endif
