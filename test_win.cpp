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
    HDC hdc;                //�豸�������
    PAINTSTRUCT ps;         //���ƽṹ
    RECT rect;              //���νṹ
    
    HWND emulatorWindow;
    MouseCursor *pCursor;
    
    switch (message)        //����õ�����Ϣ
    {
    case WM_CREATE:
        emulatorWindow = FindWindow(NULL, TEXT("�׵�ģ����"));
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
        
    case WM_PAINT:           //������������Чʱ��������Ϣ
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

    case WM_DESTROY:         //�����ڹر�ʱ����Ϣ
        // MessageBox( hwnd, TEXT("�رճ���!"), TEXT("����"), MB_OK | MB_ICONINFORMATION );
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);        //DefWindowProc���������Զ������Ϣ������û�д�������Ϣ
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
    // �쾩��
    sequences[sequenceIndex][0] = 990; sequences[sequenceIndex][1] = 205; sequences[sequenceIndex][2] = 10 * 1000;
    
    sequenceIndex += 1;
    */
    enterTwoStores();
    
    sequenceIndex += 1;
    // �ֶ��ö�
    sequences[sequenceIndex][0] = 1235; sequences[sequenceIndex][1] = 215; sequences[sequenceIndex][2] = 20 * 1000;
    
    sequenceIndex += 1;
    // �ֶ��ö�
    sequences[sequenceIndex][0] = 845; sequences[sequenceIndex][1] = 580; sequences[sequenceIndex][2] = 5 * 1000;
    
    wander();
    favorStores();
    favorGoods();
    
    sequenceIndex += 1;
    // ������һ��
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // �ֶ��ö�
    sequences[sequenceIndex][0] = 985; sequences[sequenceIndex][1] = 820; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceCount = sequenceIndex;
    sequenceIndex = 0;
}

void enterTwoStores()
{
    // �����춹
    sequences[sequenceIndex][0] = 970; sequences[sequenceIndex][1] = 345; sequences[sequenceIndex][2] = 10 * 1000;
    
    sequenceIndex += 1;
    // ����1
    sequences[sequenceIndex][0] = 1180; sequences[sequenceIndex][1] = 375; sequences[sequenceIndex][2] = 10 * 1000;
    
    sequenceIndex += 1;
    // ������һ��
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // ������һ��
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // �����춹
    sequences[sequenceIndex][0] = 970; sequences[sequenceIndex][1] = 345; sequences[sequenceIndex][2] = 10 * 1000;
    
    sequenceIndex += 1;
    // ����2
    sequences[sequenceIndex][0] = 1180; sequences[sequenceIndex][1] = 375; sequences[sequenceIndex][2] = 10 * 1000;
    
    sequenceIndex += 1;
    // ������һ��
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // ������һ��
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
}

void favorStores()
{
    sequenceIndex += 1;
    // ��ע����
    sequences[sequenceIndex][0] = 930; sequences[sequenceIndex][1] = 925; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // �����ע
    sequences[sequenceIndex][0] = 875; sequences[sequenceIndex][1] = 775; sequences[sequenceIndex][2] = 20 * 1000;
    
    sequenceIndex += 1;
    // ����1
    sequences[sequenceIndex][0] = 820; sequences[sequenceIndex][1] = 465; sequences[sequenceIndex][2] = 20 * 1000;
    
    sequenceIndex += 1;
    // ȡ����ע
    sequences[sequenceIndex][0] = 1225; sequences[sequenceIndex][1] = 190; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // ������һ��
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // ����2
    sequences[sequenceIndex][0] = 820; sequences[sequenceIndex][1] = 655; sequences[sequenceIndex][2] = 20 * 1000;
    
    sequenceIndex += 1;
    // ȡ����ע
    sequences[sequenceIndex][0] = 1225; sequences[sequenceIndex][1] = 190; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // ������һ��
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // ����3
    sequences[sequenceIndex][0] = 990; sequences[sequenceIndex][1] = 465; sequences[sequenceIndex][2] = 20 * 1000;
    
    sequenceIndex += 1;
    // ȡ����ע
    sequences[sequenceIndex][0] = 1225; sequences[sequenceIndex][1] = 190; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // ������һ��
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // ����4
    sequences[sequenceIndex][0] = 990; sequences[sequenceIndex][1] = 655; sequences[sequenceIndex][2] = 20 * 1000;
    
    sequenceIndex += 1;
    // ȡ����ע
    sequences[sequenceIndex][0] = 1225; sequences[sequenceIndex][1] = 190; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // ������һ��
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // ����5
    sequences[sequenceIndex][0] = 1155; sequences[sequenceIndex][1] = 465; sequences[sequenceIndex][2] = 20 * 1000;
    
    sequenceIndex += 1;
    // ȡ����ע
    sequences[sequenceIndex][0] = 1225; sequences[sequenceIndex][1] = 190; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // ������һ��
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // ����6
    sequences[sequenceIndex][0] = 1155; sequences[sequenceIndex][1] = 655; sequences[sequenceIndex][2] = 20 * 1000;
    
    sequenceIndex += 1;
    // ȡ����ע
    sequences[sequenceIndex][0] = 1225; sequences[sequenceIndex][1] = 190; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // ������һ��
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
}

void favorGoods()
{
    sequenceIndex += 1;
    // ��ע����
    sequences[sequenceIndex][0] = 930; sequences[sequenceIndex][1] = 925; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // ��ѡ��Ʒ
    sequences[sequenceIndex][0] = 990; sequences[sequenceIndex][1] = 775; sequences[sequenceIndex][2] = 20 * 1000;
    
    sequenceIndex += 1;
    // ��ѡ��Ʒ1
    sequences[sequenceIndex][0] = 1130; sequences[sequenceIndex][1] = 855; sequences[sequenceIndex][2] = 20 * 1000;
    
    sequenceIndex += 1;
    // ȡ����ע
    sequences[sequenceIndex][0] = 1230; sequences[sequenceIndex][1] = 740; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // ������һ��
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
    
    /*
    sequenceIndex += 1;
    // ��ѡ��Ʒ2
    sequences[sequenceIndex][0] = 1130; sequences[sequenceIndex][1] = 855; sequences[sequenceIndex][2] = 20 * 1000;
    
    sequenceIndex += 1;
    // ȡ����ע
    sequences[sequenceIndex][0] = 1230; sequences[sequenceIndex][1] = 740; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // ������һ��
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
    */
}

void wander()
{
    sequenceIndex += 1;
    // ���᳡
    sequences[sequenceIndex][0] = 1170; sequences[sequenceIndex][1] = 925; sequences[sequenceIndex][2] = 20 * 1000;
    
    sequenceIndex += 1;
    // ������һ��
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
    
    sequenceIndex += 1;
    // ���᳡���������Σ���ֹ��һ�γ���ȷ�Ͽ�
    sequences[sequenceIndex][0] = 1170; sequences[sequenceIndex][1] = 925; sequences[sequenceIndex][2] = 20 * 1000;
    
    sequenceIndex += 1;
    // ������һ��
    sequences[sequenceIndex][0] = 1285; sequences[sequenceIndex][1] = 940; sequences[sequenceIndex][2] = 5 * 1000;
}

} // extern "C"