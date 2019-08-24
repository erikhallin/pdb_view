#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include "master.h"

using namespace std;

// maximum mumber of lines the output console should have
static const WORD MAX_CONSOLE_LINES = 500;
int g_wind_w=800;
int g_wind_h=600;
int g_screen_w;
int g_screen_h;
float g_fov=60.0;

master m_master;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);
void RedirectIOToConsole();


int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    bool show_console=true;

    //get screen size
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    g_screen_w = desktop.right;
    g_screen_h = desktop.bottom;

    WNDCLASSEX wcex;
    HWND hwnd;
    HWND hwnd_console;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;

    //register window class
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "PDBview";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    //create main window
    hwnd = CreateWindowEx(0,
                          "PDBview",
                          "PDBview",
                          WS_OVERLAPPEDWINDOW,
                          0,//CW_USEDEFAULT,
                          0,//CW_USEDEFAULT,
                          g_wind_w,
                          g_wind_h,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    //enable OpenGL for the window
    EnableOpenGL(hwnd, &hDC, &hRC);

    //start console
    if(show_console)
    {
        RedirectIOToConsole();
        cout<<"Debug mode enabled"<<endl;

        //move window
        hwnd_console=GetConsoleWindow();
        MoveWindow(hwnd_console,0,g_wind_h,g_wind_w,g_screen_h-g_wind_h-100,true);
    }

    //register dnd
    DragAcceptFiles(hwnd,true);

    //init master
    m_master.init();

    //program main loop
    while (!bQuit)
    {
        //check for messages
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            //handle or dispatch messages
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            //OpenGL animation code goes here

            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //glRotatef(1.0,0,0,1);
            m_master.draw();

            /*glPushMatrix();
            glRotatef(theta, 0.0f, 0.0f, 1.0f);

            glBegin(GL_TRIANGLES);

                glColor3f(1.0f, 0.0f, 0.0f);   glVertex2f(0.0f,   1.0f);
                glColor3f(0.0f, 1.0f, 0.0f);   glVertex2f(0.87f,  -0.5f);
                glColor3f(0.0f, 0.0f, 1.0f);   glVertex2f(-0.87f, -0.5f);

            glEnd();

            glPopMatrix();*/

            SwapBuffers(hDC);

            //theta += 1.0f;
            //Sleep (1);
        }
    }

    //shutdown OpenGL
    DisableOpenGL(hwnd, hDC, hRC);

    //destroy the window explicitly
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
        break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        case WM_DROPFILES:
        {
            cout<<"file dropped\n";

            TCHAR lpszFile[MAX_PATH] = {0};
            UINT uFile = 0;
            HDROP hDrop = (HDROP)wParam;

            uFile = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, NULL);
            if (uFile != 1)
            {
                MessageBox (NULL, "Dropping multiple files is not supported.", NULL, MB_ICONERROR);
                DragFinish(hDrop);
                break;
            }
            lpszFile[0] = '\0';
            if (DragQueryFile(hDrop, 0, lpszFile, MAX_PATH))
            {
                //MessageBox (NULL, lpszFile, NULL, MB_ICONINFORMATION);
                m_master.load_protein(lpszFile);
                cout<<"file path: "<<lpszFile<<endl;
            }

            DragFinish(hDrop);
        }break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    //get the device context (DC)
    *hDC = GetDC(hwnd);

    //set the pixel format for the DC
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    //create and enable the render context (RC)
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);

    //3d
    gluPerspective(g_fov, (float)g_wind_w/(float)g_wind_h , 0.001f, 100.0f);
    //glOrtho(-10,10,-10,10 , 0.001f, 100.0f);

    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    //TEMP
    //FOG
    GLfloat fogColor[4]= {0.01f, 0.01f, 0.01f, 1.0f};   // Fog Color
    glFogi(GL_FOG_MODE, GL_LINEAR);                     // Fog Mode GL_LINEAR
    glFogfv(GL_FOG_COLOR, fogColor);                    // Set Fog Color
    glFogf(GL_FOG_DENSITY, 0);                          // How Dense Will The Fog Be
    glFogf(GL_FOG_START, 10.0f);                        // Fog Start Depth
    glFogf(GL_FOG_END, 100.0f);                         // Fog End Depth
    glEnable(GL_FOG);                                   // Enables GL_FOG
    //Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    //Lighting
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    GLfloat LightAmbient[]=		{ 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat LightDiffuse[]=		{ 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat LightSpecular[]=    { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat LightPosition[]=	{ 0.0f, 0.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT0, GL_SPECULAR,LightSpecular);	// Setup The Diffuse Light
	glLightfv(GL_LIGHT0, GL_POSITION,LightPosition);	// Position The Light
	glEnable(GL_LIGHT0);								// Enable Light One
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

void RedirectIOToConsole()
{
    int hConHandle;
    long lStdHandle;
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    FILE *fp;

    // allocate a console for this app
    AllocConsole();

    // set the screen buffer to be big enough to let us scroll text
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&coninfo);
    coninfo.dwSize.Y = MAX_CONSOLE_LINES;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),coninfo.dwSize);

    // redirect unbuffered STDOUT to the console
    lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

    fp = _fdopen( hConHandle, "w" );

    *stdout = *fp;

    setvbuf( stdout, NULL, _IONBF, 0 );

    // redirect unbuffered STDIN to the console

    lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

    fp = _fdopen( hConHandle, "r" );
    *stdin = *fp;
    setvbuf( stdin, NULL, _IONBF, 0 );

    // redirect unbuffered STDERR to the console
    lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

    fp = _fdopen( hConHandle, "w" );

    *stderr = *fp;

    setvbuf( stderr, NULL, _IONBF, 0 );

    // make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
    // point to console as well
    ios::sync_with_stdio();
}

