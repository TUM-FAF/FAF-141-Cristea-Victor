#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>

using namespace std;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
bool startsWith(char *pre, char *str);
bool inDictionary(char * value, char **dict);
void getDictionary();
char* getWord();

#define IDC_ADD_BUTTON 100
#define IDC_RESTART_BUTTON 101
#define IDC_TEXT_LIST 102
#define IDC_TEXT_INPUT 103
#define TIMER_GAME 1
#define TIMER_TIME 2
#define POMEGRANTE RGB(20,20,20)
HINSTANCE hInst;
int items, focused = 0;
char *tempLink = NULL;
char **words;
/*  Make the class name into a global variable  */
char szClassName[ ] = "CodeBlocksWindowsApp";

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx(
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "Lab#1 Windows Programming",       /* Title Text */
           WS_SYSMENU|WS_SIZEBOX, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           600,                 /* The programs width */
           400,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
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
    static HWND hwndButtonAdd,hwndButtonDel,hwndTxtList,hwndTxtInput;
    static HFONT textFont,buttonFont,hFontOld;
    RECT rect;
    HDC hdc;
    LRESULT textSize;
    HBRUSH color;

    int width,randWidth,minWidth,maxWidth;
    int textsize;
    int height,randHeight,minHeight,maxHeight;
    static int cxChar, cyChar;
    static int counter = 210;
    int hours,minutes,seconds;
    static int score;

    char szBuffer[200];
    char stBuffer[20];
    char* wordGuess = NULL;
    char * placeholder = new char[26];
    char * messag = new char[100];
    static char *cpscore;
    placeholder = "Type something from words that i know ...";




    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
        {
            width = GetSystemMetrics(SM_CXSCREEN);
            height = GetSystemMetrics(SM_CYSCREEN);
            wordGuess = getWord();
            printf("\n1%s\n",wordGuess);
            GetWindowRect(hwnd,&rect);
            SetWindowPos(hwnd,0,(width-rect.right)/2,(height-rect.bottom)/20, 0, 0, SWP_NOZORDER|SWP_NOSIZE);
            hwndButtonAdd = CreateWindowEx((DWORD)NULL,//style
                TEXT("Button"),//name
                TEXT("Add"),//text on button
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
                TEXT("edit"), // The class name required is edit
                TEXT(""), // Default text.
                WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL |
                ES_AUTOVSCROLL | ES_MULTILINE | ES_READONLY, // Textbox styles
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
                5, 180, // the left and top co-ordinates
                350, 20, // width and height
                hwnd, // parent window handle
                (HMENU)IDC_TEXT_INPUT, // the ID of your editbox
                hInst, // the instance of your application
                NULL);
                tempLink = wordGuess;
                //SetTimer(hwnd,TIMER_GAME,3*60*1000,)
                SetTimer(hwnd,TIMER_TIME,1000,NULL);
                getDictionary();
        }
        break;

        case WM_COMMAND:
        {
             switch (LOWORD(wParam))
            {
                case IDC_ADD_BUTTON:
                if(HIWORD(wParam) == BN_CLICKED)
                {
                    textSize = SendMessage(hwndTxtInput, WM_GETTEXT, 100, (LPARAM)messag);
                    messag[textSize] = _T('\0');

                    if(strlen(messag) && strcmp(messag, placeholder) && startsWith(tempLink,messag) && inDictionary(messag,words))
                    {
                        char *item = new char[200];
                        if(items)
                            strcpy(item, "\r\n - ");
                        else
                            strcpy(item, " - "); // Managing the new string
                        strcat(item, messag);
                        SendMessage(hwndTxtList, EM_REPLACESEL,
                            TRUE, (LPARAM)item); // Appending a new item in the list
                        SendMessage(hwndTxtInput, WM_SETTEXT, TRUE,(LPARAM)"");// Clearing the text input
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
            }
        }
        break;

        case IDC_ADD_BUTTON:
        {


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
                MessageBox(NULL,"Don't do this ;( ","Message",MB_OK);
                PostQuitMessage (0);
        }    /* send a WM_QUIT to the message queue */
        break;
        //min and max window size
        case WM_GETMINMAXINFO:
        {
                LPMINMAXINFO lpInfo;
                lpInfo = (LPMINMAXINFO)lParam;

                RECT rect;

                //min size
                rect.left = 0;
                rect.top = 0;
                rect.bottom = 400;
                rect.right = 500;

                AdjustWindowRectEx(&rect,WS_OVERLAPPEDWINDOW,FALSE,WS_EX_OVERLAPPEDWINDOW);

                POINT minSize;
                minSize.x = rect.right - rect.left;
                minSize.y = rect.bottom - rect.top;

                lpInfo->ptMinTrackSize = minSize;

                //max size
                rect.left = 0;
                rect.top = 0;
                rect.bottom = 500;
                rect.right = 700;

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
                SetBkColor(hdc,TRANSPARENT);
                SetTextColor(hdc, RGB(16, 255, 160));
                DrawText(hdc,"Done with Pride and Prejudice by Cristea Victor",-1,&rect,DT_CENTER|DT_BOTTOM|DT_SINGLELINE);
                TextOut(hdc,5,165,"Words that starts with",strlen("Words that starts with"));
                SetBkColor(hdc,RGB(100,255,255));
                SetTextColor(hdc,RGB(1,1,1));
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

        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

bool startsWith(char *pre, char *str)
{
    return strncmp(pre, str, strlen(pre)) == 0;
}

void getDictionary()
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

bool inDictionary(char * value, char **dict)
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
char* getWord()
{
    char * word = new char[10];
    char *strings[] = {"dis","un","for","cant","alos","man","star"};
    srand(time(NULL));
    int i = rand() % 7;
    strcpy(word,strings[i]);

    return word;
}


