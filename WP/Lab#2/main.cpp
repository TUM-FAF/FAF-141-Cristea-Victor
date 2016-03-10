#include "resources.h"
#include "header.h"
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>


using namespace std;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK    InfoDlgProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam);


HINSTANCE hInst;
HMENU hMenu;
HWND hwndList;
char buffer[25];
WNDPROC oldList,oldScroll;
char szClassName[ ] = "My app";
int items, focused = 0,backgroundImg = 0;
char *tempLink=NULL;
static char **words;


int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */
    hInst = hThisInstance;
    hMenu = LoadMenu(hInst,MAKEINTRESOURCE(IDB_MENU));
    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON));
    wincl.hIconSm = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));
    wincl.hCursor = LoadCursor (GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_CURSOR));
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH)TRANSPARENT;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx(
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "Lab#2",             /* Title Text */
           WS_SYSMENU|WS_SIZEBOX, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           600,                 /* The programs width */
           423,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           hMenu,                /*Menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);
    UpdateWindow(hwnd);
    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }



    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hwndButtonAdd,hwndButtonDel,hwndTxtList,hwndTxtInput,hwndScrollH,hwndScrollW,hwndScrollC;
    static HFONT textFont,buttonFont,hFontOld;
    RECT rect;
    HDC hdc;
    LRESULT textSize;
    HBRUSH color;

    int width,randWidth,minWidth,maxWidth;
    int textsize;
    int height,randHeight,minHeight,maxHeight;
    static int cxChar, cyChar,posX,posY;
    static int counter = 210;
    int hours,minutes,seconds;
    static int score;

    char szBuffer[200];
    char stBuffer[20];
    static char* wordGuess = NULL;
    char * placeholder = new char[26];
    char * messag = new char[100];
    static char *cpscore;
    placeholder = "Type here the new word...";




    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
        {
            width = GetSystemMetrics(SM_CXSCREEN);
            height = GetSystemMetrics(SM_CYSCREEN);
            wordGuess = GetWord();
            printf("\n1%s\n",wordGuess);
            GetWindowRect(hwnd,&rect);
            SetWindowPos(hwnd,0,(width-rect.right)/2,(height-rect.bottom)/20, 0, 0, SWP_NOZORDER|SWP_NOSIZE);
            hwndButtonAdd = CreateWindowEx((DWORD)NULL,//style
                TEXT("Button"),//name
                TEXT("Add word"),//text on button
                WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,//type
                5,210,//starting poin
                160,50,//width and height
                hwnd,//parent
                (HMENU)IDC_ADD_BUTTON,//menu
                hInst,//
                NULL);//pointer to new form

           hwndButtonDel = CreateWindowEx(
                (DWORD)NULL,
                TEXT("button"),
                TEXT("Quit"), // the caption of the button
                WS_CHILD | WS_VISIBLE| BS_PUSHBUTTON, // the styles
                200, 210, // the left and top co-ordinates
                157, 50, // width and height
                hwnd, // parent window handle
                (HMENU)IDC_RESTART_BUTTON, // the ID of your button
                hInst, // the instance of your application
                NULL);



            hwndTxtList = CreateWindowEx(
                (DWORD)NULL,
                TEXT("listbox"), // The class name required is edit
                TEXT(""), // Default text.
                WS_VISIBLE|WS_CHILD|WS_VSCROLL|LBS_NOINTEGRALHEIGHT|WS_BORDER|LBS_NOTIFY|ES_READONLY,
                5, 20, // the left and top co-ordinates
                350, 130, // width and height
                hwnd, // parent window handle
                (HMENU)IDC_TEXT_LIST, // the ID of your editbox
                hInst, // the instance of your application
                NULL); // extra bits you dont really need

            hwndTxtInput = CreateWindowEx(
                (DWORD)NULL,
                TEXT("edit"), // The class name required is edit
                TEXT(placeholder), // Default text.
                WS_VISIBLE | WS_CHILD | WS_BORDER, // Textbox styles
                5, 185, // the left and top co-ordinates
                350, 20, // width and height
                hwnd, // parent window handle
                (HMENU)IDC_TEXT_INPUT, // the ID of your editbox
                hInst, // the instance of your application
                NULL);

            hwndScrollC = CreateWindowEx(
                (DWORD)NULL,
                TEXT("scrollbar"),
                TEXT(""),
                WS_VISIBLE|WS_CHILD|SBS_HORZ,
                0,325,
                150,20,
                hwnd,
                (HMENU)ID_SCROLL_HPOS,
                hInst,
                NULL);




            hwndScrollH = CreateWindowEx(
                (DWORD)NULL,
                TEXT("scrollbar"),
                TEXT(""),
                WS_VISIBLE|WS_CHILD|SBS_HORZ,
                352,325,
                150,20,
                hwnd,
                (HMENU)ID_SCROLL_HPOS,
                hInst,
                NULL);


            hwndScrollW = CreateWindowEx(
                (DWORD)NULL,
                TEXT("scrollbar"),
                TEXT(""),
                WS_VISIBLE|WS_CHILD|SBS_VERT,
                482,175,
                20,150,
                hwnd,
                (HMENU)ID_SCROLL_HPOS,
                hInst,
                NULL);

                SetScrollRange(hwndScrollC,SB_CTL,0,255,FALSE);
                SetScrollPos(hwndScrollC,SB_CTL,0,FALSE);

                SetScrollRange(hwndScrollW,SB_CTL,0,200,FALSE);
                SetScrollPos(hwndScrollW,SB_CTL,200,FALSE);

                SetScrollRange(hwndScrollH,SB_CTL,0,200,FALSE);
                SetScrollPos(hwndScrollH,SB_CTL,0,FALSE);


                hwndList = hwndTxtList;
                tempLink = wordGuess;
                //SetTimer(hwnd,TIMER_GAME,3*60*1000,)
                SetTimer(hwnd,TIMER_TIME,1000,NULL);
                GetDictionary();
        }
        break;

        case WM_VSCROLL:
        {
            if((HWND)lParam==hwndScrollW)
            {
                switch(LOWORD(wParam))
                {
                case SB_PAGEDOWN:
                    posY-=Y_PAGE_MOVE;
                case SB_LINEDOWN:
                    posY=max(0,posY-Y_LINE_MOVE);
                    break;
                case SB_PAGEUP:
                    posY+=Y_PAGE_MOVE;
                case SB_LINEUP:
                    posY=min(200,posY+Y_LINE_MOVE);
                    break;
                case SB_TOP:
                    posY=200;
                    break;
                case SB_BOTTOM:
                    posY=0;
                    break;
                case SB_THUMBPOSITION:
                    posY=HIWORD(wParam);
                    break;
                default: break;
                }

                SetScrollPos(hwndScrollW,SB_CTL,200-posY,TRUE);
                SetWindowPos(hwnd,HWND_TOP,posX,posY,0,0,SWP_SHOWWINDOW|SWP_NOSIZE);
            }
        }
        break;

        case WM_HSCROLL:
        {
            switch(LOWORD(wParam))
                {
                case SB_PAGELEFT:
                    posX-=X_PAGE_MOVE;
                case SB_LINELEFT:
                    posX=max(0,posX-X_LINE_MOVE);
                    break;
                case SB_PAGERIGHT:
                    posX+=X_PAGE_MOVE;
                case SB_LINERIGHT:
                    posX=min(200,posX+X_LINE_MOVE);
                    break;
                case SB_RIGHT:
                    posX=200;
                    break;
                case SB_LEFT:
                    posX=0;
                    break;
                case SB_THUMBPOSITION:
                    posX=HIWORD(wParam);
                    break;
                default: break;
                }
                SetScrollPos(hwndScrollH,SB_CTL,posX,TRUE);
                SetWindowPos(hwnd,HWND_TOP,posX,posY,0,0,SWP_SHOWWINDOW|SWP_NOSIZE);
        }
        break;

        case WM_COMMAND:
        {
            if(LOWORD(wParam)==IDC_TEXT_LIST && HIWORD(wParam)==LBN_DBLCLK)
            {
                int i=SendMessage(hwndList,LB_GETCURSEL,0,0);
                sprintf(buffer,"Prefix -> %s \nWord -> %s",wordGuess,words[i]);
                MessageBox(hwnd,buffer,TEXT("Word"),MB_ICONASTERISK|MB_OK);
                SetFocus(hwndList);

            }
             switch (LOWORD(wParam))
            {
                case IDC_ADD_BUTTON:
                if(HIWORD(wParam) == BN_CLICKED)
                {
                    textSize = SendMessage(hwndTxtInput, WM_GETTEXT, 100, (LPARAM)messag);
                    messag[textSize] = _T('\0');

                    if(strlen(messag) && strcmp(messag, placeholder) && StartsWith(tempLink,messag) && InDictionary(messag,words))
                    {
                        char *item = new char[200];
                        if(items)
                            strcpy(item, "\r\n - ");
                        else
                            strcpy(item, " - "); // Managing the new string
                        strcat(item, messag);
                        int pos = (int)SendMessage(hwndTxtList, LB_ADDSTRING, 0, (LPARAM)item); // Appending a new item in the list
                        SendMessage(hwndList, LB_SETITEMDATA, pos, (LPARAM) items);
                        SendMessage(hwndList, WM_SETTEXT, TRUE,(LPARAM)"");// Clearing the text input
                        delete [] item; // Managing the memory
                        items += 1; // Incrementing the number of items
                        SendMessage(
                            hwndTxtInput,
                            WM_SETTEXT,
                            TRUE,
                            (LPARAM)placeholder); // Recovering the placeholder

                        focused = 0;
                        score+=strlen(messag) - strlen(tempLink);

                    }
                    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
                }
                break;
                case IDC_TEXT_INPUT:
                {
                    if(HIWORD(wParam) == EN_SETFOCUS)
                    {
                        textSize = SendMessage(hwndTxtInput, WM_GETTEXT, 100, (LPARAM)messag);
                        messag[textSize] = _T('\0');

                        if(!strcmp(messag, placeholder))
                        {
                            SendMessage(hwndTxtInput, WM_SETTEXT, TRUE,(LPARAM)"");// Clearing the text input
                            focused = 1;
                            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
                        }
                    }
                     else if(HIWORD(wParam) == EN_KILLFOCUS)
                    {
                        textSize = SendMessage(hwndTxtInput, WM_GETTEXT, 100, (LPARAM)messag);
                        messag[textSize] = _T('\0');

                        if(!strcmp(messag, ""))
                        {
                            SendMessage(
                                hwndTxtInput,
                                WM_SETTEXT,
                                TRUE,
                                (LPARAM)placeholder); // Recovering the placeholder
                            focused = 0;
                            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
                        }
                    }
                }
                break;
                case IDC_RESTART_BUTTON:
                {
                      if(HIWORD(wParam) == BN_CLICKED)
                      {
                        SendMessage(hwnd,WM_DESTROY,0,0);
                      }
                }
                break;
                case IDB_INFO:
                {
                    DialogBox(hInst,MAKEINTRESOURCE(IDB_DIALOG),hwnd,InfoDlgProc);
                }
                break;
                case IDB_EXIT:
                {
                    SendMessage(hwnd,WM_DESTROY,0,0);
                }
                break;
                case IDB_RESTART:
                {

                }
                break;
                case IDB_BACKGROUND_1:
                {
                    printf("First background");
                    if(backgroundImg == 0)
                        break;
                    backgroundImg = 0;
                    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);

                }
                break;
                case IDB_BACKGROUND_2:
                {
                    printf("First background");
                    if(backgroundImg == 1)
                        break;
                    backgroundImg = 1;
                    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);

                }
                break;
                case IDB_RECORDS:
                {
                    DialogBox(hInst,MAKEINTRESOURCE(IDB_DIALOG),hwnd,InfoDlgProc);
                }
                break;
            }
        }
        break;


            case WM_KEYDOWN:
            {
                switch(wParam)
                {
                    case VK_SPACE:
                        if(GetAsyncKeyState(VK_LCONTROL))
                        {
                            if(backgroundImg == 0)backgroundImg = 1;
                            else if(backgroundImg == 1) backgroundImg = 0;
                            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
                        }
                    break;

                    case KEY_Q:
                        if(GetAsyncKeyState(VK_LCONTROL))
                        {
                            SendMessage(hwnd,WM_DESTROY,0,0);
                        }
                    break;

                }
            }
            break;

            case WM_GETMINMAXINFO:
            {
                LPMINMAXINFO lpInfo;
                lpInfo = (LPMINMAXINFO)lParam;

                RECT rect;

                //min size
                rect.left = 0;
                rect.top = 0;
                rect.bottom = 300;
                rect.right = 400;

                AdjustWindowRectEx(&rect,WS_OVERLAPPEDWINDOW,FALSE,WS_EX_OVERLAPPEDWINDOW);

                POINT minSize;
                minSize.x = rect.right - rect.left;
                minSize.y = rect.bottom - rect.top;

                lpInfo->ptMinTrackSize = minSize;

                //max size
                rect.left = 0;
                rect.top = 0;
                rect.bottom = 400;
                rect.right = 500;

                AdjustWindowRectEx(&rect,WS_OVERLAPPEDWINDOW,FALSE,WS_EX_OVERLAPPEDWINDOW);

                POINT maxSize;
                maxSize.x = rect.right - rect.left;
                maxSize.y = rect.bottom - rect.top;

                lpInfo->ptMaxTrackSize = maxSize;

            }
            break;

            case WM_PAINT:
            {
                PAINTSTRUCT ps;
                hdc = BeginPaint(hwnd,&ps);
                GetClientRect(hwnd,&rect);
                HBITMAP backgrBMP = NULL;
                if(backgroundImg == 0)
                {
                    backgrBMP = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BACKGROUND_1));
                }
                else if(backgroundImg == 1)
                {
                    backgrBMP = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BACKGROUND_2));
                }
                if(!backgrBMP){MessageBox(NULL,"Whyyyyyyyy Background? :D ","Message",MB_OK);}
                HBRUSH backgrBrush = CreatePatternBrush(backgrBMP);

                HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, backgrBrush);
                Rectangle(hdc, 0, 0, rect.right - rect.left, rect.bottom-rect.top);

                SelectObject(hdc, oldBrush);
                DeleteObject(backgrBrush);
                DeleteObject(backgrBMP);



                buttonFont = CreateFont(20,0,0,0,0,0,0,0,0,0,0,0,0,TEXT("Courier New"));
                SendMessage(hwndButtonAdd,WM_SETFONT,(WPARAM)buttonFont,1);
                if(counter > 0)
                {
                    minutes = (counter / 60) % 60;
                    seconds = counter % 60;
                    wsprintf (szBuffer, " Minutes: %d Seconds: %d left", minutes, seconds);
                    DrawText (hdc, szBuffer, -1, &rect, DT_RIGHT|DT_TOP);
                }
                else
                {
                    //SendMessage (hwnd, WM_CLOSE, 0, 0L);
                    EnableWindow( GetDlgItem(hwnd, 100),  false);
                    EnableWindow( GetDlgItem(hwnd, 101),  true);
                    KillTimer(hwnd,TIMER_TIME);
                }
                SetTextColor(hdc, RGB(160, 0, 2));
                SetBkColor(hdc,TRANSPARENT);
                DrawText(hdc,"Done with Pride and Prejudice by Victor Cristea",-1,&rect,DT_CENTER|DT_BOTTOM|DT_SINGLELINE);
                TextOut(hdc,5,165,"Words that starts with",strlen("Words that starts with"));
                SetBkColor(hdc,RGB(220,220,220));
                SetTextColor(hdc,RGB(30,30,30));
                TextOut(hdc,165,165,tempLink,strlen(tempLink));
                TextOut(hdc,400,100,"Score:",strlen("Score:"));
                sprintf(stBuffer, "%i", score);
                TextOut(hdc,460,100,stBuffer,strlen(stBuffer));
                EndPaint(hwnd,&ps);
            }
            break;

            case WM_TIMER:
            {
                switch(wParam)
                {
                    case TIMER_TIME:
                        counter--;
                        InvalidateRect (hwnd, NULL, TRUE);
                    break;
                }
            }
            break;

            case WM_CLOSE:
        {
                RECT rect;
                GetWindowRect(hwnd,&rect);
                width = rect.right - rect.left;
                height = rect.bottom - rect.top;

                maxWidth = GetSystemMetrics(SM_CXSCREEN) - width;
                maxHeight = GetSystemMetrics(SM_CYSCREEN) - height;
                randWidth = rand()%(maxWidth);
                randHeight = rand()%(maxHeight);

                MoveWindow(hwnd,randWidth,randHeight,width,height,TRUE);
            }
            break;

            case WM_DESTROY:
            {
                KillTimer(hwnd, TIMER_GAME);
                MessageBox(NULL,"Don't do this :( ","Message",MB_OK);
                PostQuitMessage (0);
            }    /* send a WM_QUIT to the message queue */
            break;

            default:                      /* for messages that we don't deal with */
                return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

BOOL CALLBACK    InfoDlgProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
    switch(message)
    {
    case WM_INITDIALOG:
        return TRUE;
    case WM_COMMAND:
        switch(LOWORD(wParam))
        {
        case IDOK:
            EndDialog(hwnd,0);
            return TRUE;

        }
    break;
    }
    return FALSE;
}

LRESULT CALLBACK ListProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    /*aici*/if(message == WM_KEYDOWN && wParam == KEY_R)
    {
         SetFocus(hwndList);
    }
    if(message==WM_KEYDOWN && wParam==KEY_R)
    {
        int iIndex=SendMessage(hwndList,LB_GETCURSEL,0,0);
        sprintf(buffer,"Prefix -> %s \nWord -> %s","asdl",words[iIndex]);
        MessageBox(hwnd,buffer,TEXT("Word"),MB_ICONASTERISK|MB_OK);
        SetFocus(hwndList);
    }/*si aici*/
    return CallWindowProc(oldList,hwnd,message,wParam,lParam);
}



void CreateChilds()
{

}


bool StartsWith(char *pre, char *str)
{
    return strncmp(pre, str, strlen(pre)) == 0;
}

void GetDictionary()
{
    words = new char*[55000];
    char *tempString;

    for(int i=0;i<55000;i++)
    {
        words[i] = new char[20];
    }

    FILE *in_file = fopen("words.txt", "r");
    if (words == NULL)
    {
        printf("Error alocating!");
        exit(-1);
    }
    if (in_file == NULL)
    {
        printf("Error file missing\n");
        exit(-1);
    }
    int i=0;
    while(i<55000)
    {
        fscanf(in_file,"%s",words[i]);
        i++;
    }

    return;
}

bool InDictionary(char * value, char **dict)
{
    int my_size = 55000;
    for (int i = 0; i < my_size; i++)
    {
        if (strcmp(value,dict[i])==0)
        {
            return true;
        }
    }

    return false;
}
char* GetWord()
{
    char * word = new char[10];
    char *strings[] = {"dis","un","for","cant","alos","man","star"};
    srand(time(NULL));
    int i = rand() % 7;
    strcpy(word,strings[i]);

    return word;
}


