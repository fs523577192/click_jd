#include <cstdio>
#include "Window.cpp"
#include "MouseCursor.cpp"
#include "click.cpp"

extern "C" {
    
// constant definition
TCHAR szAppName[] = TEXT("MyWindow");
TCHAR outputBuffer[] = TEXT("(0000, 0000)        ");

// global variable definition
int sequenceIndex = 0, sequenceCount = 0;
LONG sequences[100][3];
Window *pEmulatorWindow;
ClickHelper *pClickHelper;

// function definition
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CALLBACK TimerProc(HWND, UINT, UINT_PTR, DWORD);
void initSequences();
void enterTwoStores();
void favorStores();
void favorGoods();
void wander();

// entry point
int CALLBACK _tWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR lpCmdLine,
    int nCmdShow
) {
    try {
        Window mainWindow(hInstance, TEXT("mainWindow"), TEXT("My Window"), WndProc,
                Window::DEFAULT, Window::DEFAULT, 300, 300);
        mainWindow.show(nCmdShow);
        mainWindow.update();
        mainWindow.messageLoop();
    } catch (LPCTSTR message) {
        MessageBox( NULL, message, TEXT("Error"), MB_OK | MB_ICONERROR );
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;                //设备环境句柄
    PAINTSTRUCT ps;         //绘制结构
    RECT rect;              //矩形结构
    
    HWND emulatorWindow;
    MouseCursor *pCursor;
    
    switch (message)        //处理得到的消息
    {
    case WM_CREATE:
        emulatorWindow = FindWindow(NULL, TEXT("雷电模拟器"));
        if (emulatorWindow) {
            _stprintf(outputBuffer, TEXT("%X"), emulatorWindow);
            
            pEmulatorWindow = new Window(emulatorWindow);
            pClickHelper = new ClickHelper();
            initSequences();
            
            SetTimer(hwnd, 1, 3000, (TIMERPROC) TimerProc);
        }
        
        // clickAt(940, 305);
        
        // clickAt(1170, 345);
        return 0;
        
    case WM_PAINT:           //处理窗口区域无效时发来的消息
        hdc = BeginPaint(hwnd, &ps);
        GetClientRect(hwnd, &rect);
        DrawText(hdc, outputBuffer, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        EndPaint(hwnd, &ps);
        return 0;

    case WM_MOUSEMOVE:
        pCursor = new MouseCursor();
        _stprintf(outputBuffer, TEXT("(%4d, %4d)"), pCursor->getX(), pCursor->getY());
        delete pCursor;
        
        rect.left = 0;
        rect.top = 0;
        rect.right = 299;
        rect.bottom = 299;
        InvalidateRect(hwnd, &rect, TRUE);
        return 0;

    case WM_DESTROY:         //处理窗口关闭时的消息
        // MessageBox( hwnd, TEXT("关闭程序!"), TEXT("结束"), MB_OK | MB_ICONINFORMATION );
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);        //DefWindowProc处理我们自定义的消息处理函数没有处理到的消息
}

void CALLBACK TimerProc(HWND hwnd, UINT arg2, UINT_PTR timerId, DWORD arg4)
{
    RECT rect;
    LONG *sequence;
    
    pEmulatorWindow->showOnTop();
    
    sequence = sequences[sequenceIndex++];
    pClickHelper->clickAt(sequence[0], sequence[1]);
    
    KillTimer(hwnd, timerId);
    
    if (sequenceIndex < sequenceCount) {
        SetTimer(hwnd, timerId, sequence[2], (TIMERPROC) TimerProc);
    }
}

void initSequences()
{
    sequenceIndex = 0;
    /* Go to desktop first
    sequences[sequenceIndex][0] = 1290; sequences[sequenceIndex][1] = 980; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // Open JD
    sequences[sequenceIndex][0] = 1100; sequences[sequenceIndex][1] = 245; sequences[sequenceIndex][2] = 10 * 1000;
    
    sequenceIndex += 1;
    // 领京豆
    sequences[sequenceIndex][0] = 990; sequences[sequenceIndex][1] = 205; sequences[sequenceIndex][2] = 10 * 1000;
    
    sequenceIndex += 1;
    */
    enterTwoStores();
    
    sequenceIndex += 1;
    // 种豆得豆
    sequences[sequenceIndex][0] = 1235; sequences[sequenceIndex][1] = 215; sequences[sequenceIndex][2] = 20 * 1000;
    
    sequenceIndex += 1;
    // 种豆得豆
    sequences[sequenceIndex][0] = 845; sequences[sequenceIndex][1] = 580; sequences[sequenceIndex][2] = 5 * 1000;
    
    wander();
    favorStores();
    favorGoods();
    
    sequenceIndex += 1;
    // 返回上一级
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // 种豆得豆
    sequences[sequenceIndex][0] = 985; sequences[sequenceIndex][1] = 820; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceCount = sequenceIndex;
    sequenceIndex = 0;
}

void enterTwoStores()
{
    // 进店领豆
    sequences[sequenceIndex][0] = 970; sequences[sequenceIndex][1] = 345; sequences[sequenceIndex][2] = 10 * 1000;
    
    sequenceIndex += 1;
    // 进店1
    sequences[sequenceIndex][0] = 1180; sequences[sequenceIndex][1] = 375; sequences[sequenceIndex][2] = 10 * 1000;
    
    sequenceIndex += 1;
    // 返回上一级
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // 返回上一级
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // 进店领豆
    sequences[sequenceIndex][0] = 970; sequences[sequenceIndex][1] = 345; sequences[sequenceIndex][2] = 10 * 1000;
    
    sequenceIndex += 1;
    // 进店2
    sequences[sequenceIndex][0] = 1180; sequences[sequenceIndex][1] = 375; sequences[sequenceIndex][2] = 10 * 1000;
    
    sequenceIndex += 1;
    // 返回上一级
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // 返回上一级
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
}

void favorStores()
{
    sequenceIndex += 1;
    // 关注任务
    sequences[sequenceIndex][0] = 930; sequences[sequenceIndex][1] = 925; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // 进店关注
    sequences[sequenceIndex][0] = 875; sequences[sequenceIndex][1] = 775; sequences[sequenceIndex][2] = 20 * 1000;
    
    sequenceIndex += 1;
    // 进店1
    sequences[sequenceIndex][0] = 820; sequences[sequenceIndex][1] = 465; sequences[sequenceIndex][2] = 20 * 1000;
    
    sequenceIndex += 1;
    // 取消关注
    sequences[sequenceIndex][0] = 1225; sequences[sequenceIndex][1] = 190; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // 返回上一级
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // 进店2
    sequences[sequenceIndex][0] = 820; sequences[sequenceIndex][1] = 655; sequences[sequenceIndex][2] = 20 * 1000;
    
    sequenceIndex += 1;
    // 取消关注
    sequences[sequenceIndex][0] = 1225; sequences[sequenceIndex][1] = 190; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // 返回上一级
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // 进店3
    sequences[sequenceIndex][0] = 990; sequences[sequenceIndex][1] = 465; sequences[sequenceIndex][2] = 20 * 1000;
    
    sequenceIndex += 1;
    // 取消关注
    sequences[sequenceIndex][0] = 1225; sequences[sequenceIndex][1] = 190; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // 返回上一级
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // 进店4
    sequences[sequenceIndex][0] = 990; sequences[sequenceIndex][1] = 655; sequences[sequenceIndex][2] = 20 * 1000;
    
    sequenceIndex += 1;
    // 取消关注
    sequences[sequenceIndex][0] = 1225; sequences[sequenceIndex][1] = 190; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // 返回上一级
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // 进店5
    sequences[sequenceIndex][0] = 1155; sequences[sequenceIndex][1] = 465; sequences[sequenceIndex][2] = 20 * 1000;
    
    sequenceIndex += 1;
    // 取消关注
    sequences[sequenceIndex][0] = 1225; sequences[sequenceIndex][1] = 190; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // 返回上一级
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // 进店6
    sequences[sequenceIndex][0] = 1155; sequences[sequenceIndex][1] = 655; sequences[sequenceIndex][2] = 20 * 1000;
    
    sequenceIndex += 1;
    // 取消关注
    sequences[sequenceIndex][0] = 1225; sequences[sequenceIndex][1] = 190; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // 返回上一级
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
}

void favorGoods()
{
    sequenceIndex += 1;
    // 关注任务
    sequences[sequenceIndex][0] = 930; sequences[sequenceIndex][1] = 925; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // 挑选商品
    sequences[sequenceIndex][0] = 990; sequences[sequenceIndex][1] = 775; sequences[sequenceIndex][2] = 20 * 1000;
    
    sequenceIndex += 1;
    // 挑选商品1
    sequences[sequenceIndex][0] = 1130; sequences[sequenceIndex][1] = 855; sequences[sequenceIndex][2] = 20 * 1000;
    
    sequenceIndex += 1;
    // 取消关注
    sequences[sequenceIndex][0] = 1230; sequences[sequenceIndex][1] = 740; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // 返回上一级
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
    
    /*
    sequenceIndex += 1;
    // 挑选商品2
    sequences[sequenceIndex][0] = 1130; sequences[sequenceIndex][1] = 855; sequences[sequenceIndex][2] = 20 * 1000;
    
    sequenceIndex += 1;
    // 取消关注
    sequences[sequenceIndex][0] = 1230; sequences[sequenceIndex][1] = 740; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // 返回上一级
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
    */
}

void wander()
{
    sequenceIndex += 1;
    // 逛逛会场
    sequences[sequenceIndex][0] = 1170; sequences[sequenceIndex][1] = 925; sequences[sequenceIndex][2] = 20 * 1000;
    
    sequenceIndex += 1;
    // 返回上一级
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // 逛逛会场（进入两次，防止有一次出现确认框）
    sequences[sequenceIndex][0] = 1170; sequences[sequenceIndex][1] = 925; sequences[sequenceIndex][2] = 20 * 1000;
    
    sequenceIndex += 1;
    // 返回上一级
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
}

} // extern "C"