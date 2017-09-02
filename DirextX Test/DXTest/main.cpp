#include <Windows.h>
#include <windowsx.h>
#include <d3d9.h> // Required for Direct3D

// Include the Direct3D lib file
#pragma comment (lib, "d3d9.lib")

// Global declarations
LPDIRECT3D9 d3d; // Pointer to Direct3D interface
LPDIRECT3DDEVICE9 d3ddev; // Pointer to the device class

// Function prototypes
void initD3D(HWND hWnd); // Setup & init Direct3D
void renderFrame(void); // Render a frame
void cleanD3D(void); // Close Direct3D and release memory

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
		"Direct3D test",   // title of the window
		WS_OVERLAPPEDWINDOW,    // window style
		300,    // x-position of the window
		300,    // y-position of the window
		800,    // width of the window
		600,    // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		hInstance,    // application handle
		NULL);    // used with multiple windows, NULL)

	// display the window on the screen
	ShowWindow(hWnd, nCmdShow);

	// Setup & init Direct3D
	initD3D(hWnd);

	// enter the main loop:

	// this struct holds Windows event messages
	MSG msg;

	while (true)
	{
		// Check if there are messages waiting in the queue
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// translate message and dispatch it to WindowProc
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If message is WM_QUIT, exit loop
		if (msg.message == WM_QUIT)
			break;

		renderFrame();
	}

	// Clean up DirectX and COM
	cleanD3D();

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

void initD3D(HWND hWnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION); // Create the Direct3D interface

	D3DPRESENT_PARAMETERS d3dpp; // Create a struct to hold various device information

	ZeroMemory(&d3dpp, sizeof(d3dpp)); // Clear out the struct
	d3dpp.Windowed = TRUE; // Start program windowed
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; // Discard old frames
	d3dpp.hDeviceWindow = hWnd; // Set the window to be used by Direct3D

	// Create a device class using this information and information from the d3dpp struct
	d3d->CreateDevice(D3DADAPTER_DEFAULT, // Adapter
					  D3DDEVTYPE_HAL, // Device type
					  hWnd, // Focus window
					  D3DCREATE_SOFTWARE_VERTEXPROCESSING, // Behavior flag
					  &d3dpp, // Presentation parameter
					  &d3ddev); // Returned device interface
}

void renderFrame()
{
	// Clear the window and fill with blue
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);

	d3ddev->BeginScene(); // Begins the 3D scene

	// Do 3D rendering on back buffer here


	d3ddev->EndScene(); // End the 3D scene

	d3ddev->Present(NULL, NULL, NULL, NULL); // Display the created frame
}

void cleanD3D()
{
	d3ddev->Release(); // Close and release the 3D device
	d3d->Release(); // Close and release Direct3D
}

/* http://www.directxtutorial.com/Lesson.aspx?lessonid=9-4-1 */