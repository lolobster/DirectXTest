#include <Windows.h>
#include <windowsx.h>

// WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd,
							UINT message,
							WPARAM wParam,
							LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, // "handle to an instance"
	HINSTANCE hPrevInstance,			// "handle to previous instance", only exists for backwards compatibility
	LPSTR lpCmdLine,					// long pointer to a string that contains the command line calling existence to the application
	int nCmdShow)						// indicates how the windows is to appear when created
{
	// handle for the window
	HWND hWnd;

	// struct for holding information for the window class
	WNDCLASSEX wc;

	// clear out the window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// fill in the struct with the needed information
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "WindowClass1";

	// register window class
	RegisterClassEx(&wc);

	// create window and use the result as the handle
	hWnd = CreateWindowEx(NULL,
		"WindowClass1",    // name of the window class
		"DirectX Test Window",   // title of the window
		WS_OVERLAPPEDWINDOW,    // window style
		300,    // x-position of the window
		300,    // y-position of the window
		500,    // width of the window
		400,    // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		hInstance,    // application handle
		NULL);    // used with multiple windows, NULL)

	// display the window on the screen
	ShowWindow(hWnd, nCmdShow);

	// enter the main loop:

	// this struct holds Windows event messages
	MSG msg;

	// Wait for the next message in the queue, store the result in 'msg'
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// translate keystroke messages into the right format
		TranslateMessage(&msg);

		// send the message to the WindowProc function
		DispatchMessage(&msg);
	}
	// return this part of the WM_QUIT message to Windows
	return msg.wParam;
}

// main message handler
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// sort through and find what code to run for the message given
	switch (message)
	{
		// the message is read when the windos is closed
	case WM_DESTROY:
	{
		// close program
		PostQuitMessage(0);
		return 0;
	}break;
	}
	// Handle any messages the switch statement didn't
	return DefWindowProc(hWnd, message, wParam, lParam);
}

// http://www.directxtutorial.com/Lesson.aspx?lessonid=9-1-3