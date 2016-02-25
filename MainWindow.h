#include <windows.h>

class MainWindow
{
public:
    MainWindow(HINSTANCE hInstance);
    ~MainWindow();
    static LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    bool Run(int nCmdShow);

private:
    WNDCLASSEX m_wndClass;
    static HINSTANCE m_hInstance;
    HWND m_hwnd;
    static char m_szClassName[];
};
