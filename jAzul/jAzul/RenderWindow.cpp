#include "WindowsContainer.h"
#include "StringConverter.h"
#include "RenderWindow.h"

LRESULT CALLBACK HandleMsgRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

RenderWindow::RenderWindow() :
	handle(nullptr),
	hInstance(nullptr),
	window_title(),
	window_title_wide(),
	window_class(),
	window_class_wide(),
	width(0),
	height(0)

{
}

RenderWindow::~RenderWindow()
{
}

bool RenderWindow::Initialize(HINSTANCE _hInstance, WindowContainer* pWinContainer, std::string _window_title, std::string _window_class, int _width, int _height)
{
	this->hInstance = _hInstance;

	// Copy / Create my variables
	if(window_title.empty())
		this->window_title = _window_title;

	this->window_title_wide = StringConverter::StringToWide(this->window_title);
	this->window_class = _window_class;
	this->window_class_wide = StringConverter::StringToWide(this->window_class);
	this->width = _width;
	this->height = _height;	
	
	// Register my window with windows
	this->RegisterWindowClass();

	// create my handle
	this->handle = CreateWindowEx(0, //Extended Windows style - we are using the default. For other options
		this->window_class.c_str(), //Window class name
		this->window_title.c_str(), //Window Title
		WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_MAXIMIZEBOX, //Windows style
		0, //Window X Position
		0, //Window Y Position
		this->width, //Window Width
		this->height, //Window Height
		NULL, //Handle to parent of this window. Since this is the first window, it has no parent window.
		NULL, //Handle to menu or child window identifier. Can be set to NULL and use menu in WindowClassEx if a menu is desired to be used.
		this->hInstance, //Handle to the instance of module to be used with this window
		pWinContainer); //Param to create window


	if (this->handle == nullptr) {
		ErrorLogger::Log(GetLastError(), "CreateWindowEX Failed for window: " + this->window_title);
		return false;
	}

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(this->handle, SW_SHOW);
	SetForegroundWindow(this->handle);
	SetFocus(this->handle);

	return true;
}

bool RenderWindow::ProcessMessages()
{
	// Handle the windows messages.
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG)); // Initialize the message structure.

	while (PeekMessage(&msg,		// Where to store message (if one exists) 
		this->handle,				// Handle to window we are checking messages for
		0,							// Minimum Filter Msg Value - We are not filtering for specific messages, but the min/max could be used to filter only this->mo messages for example.
		0,							// Maximum Filter Msg Value
		PM_REMOVE))					// Remove message after capturing it via PeekMessage. For more argument options.
	{
		TranslateMessage(&msg);		//Translate message from virtual key messages into character messages so we can dispatch the message. 
		DispatchMessage(&msg);		//Dispatch message to our Window Proc for this window. 
	}

	// Check if the window was closed
	if (msg.message == WM_NULL) {
		if (!IsWindow(this->handle)) {
			this->handle = NULL; //Message processing loop takes care of destroying this window
			UnregisterClass(this->window_class.c_str(), this->hInstance);
			return false;
		}
	}

	return true;
}

void RenderWindow::SetWindowName(std::string _window_title)
{
	this->window_title = _window_title;
}

void RenderWindow::UpdateWindowText(std::string _window_title)
{
	std::string windowCap = this->window_title + _window_title;
	SetWindowText(this->handle, windowCap.c_str());
}

HWND RenderWindow::GetHandle() const
{
	return this->handle;
}

const int RenderWindow::GetWidth() const
{
	return this->width;
}

const int RenderWindow::GetHeight() const
{
	return this->height;
}

void RenderWindow::RegisterWindowClass()
{
	WNDCLASSEX wc;										// Our Window Class (This has to be filled before our window can be created) 
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		// Flags [Redraw on width/height change from resize/movement] 
	wc.lpfnWndProc = HandleMessageSetup;				// Pointer to Window Proc function for handling messages from this window
	wc.cbClsExtra = 0;									// # of extra bytes to allocate following the window-class structure. We are not currently using this.
	wc.cbWndExtra = 0;									// # of extra bytes to allocate following the window instance. We are not currently using this.
	wc.hInstance = this->hInstance;						// Handle to the instance that contains the Window Procedure
	wc.hIcon = NULL;									// Handle to the class icon. Must be a handle to an icon resource. We are not currently assigning an icon, so this is null.
	wc.hIconSm = NULL;									// Handle to small icon for this class. We are not currently assigning an icon, so this is null.
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Default Cursor - If we leave this null, we have to explicitly set the cursor's shape each time it enters the window.
	wc.hbrBackground = NULL;							// Handle to the class background brush for the window's background color, 
	wc.lpszMenuName = NULL;								// Pointer to a null terminated character string for the menu. We are not using a menu yet, so this will be NULL.
	wc.lpszClassName = this->window_class.c_str();		// Pointer to null terminated string of our class name for this window.
	wc.cbSize = sizeof(WNDCLASSEX);						// Need to fill in the size of our struct for cbSize
	
	RegisterClassEx(&wc);								// Register the class so that it is usable.
}

// ***************************************************

// ** MESSAGE PROCESSING METHODS

// ***************************************************

LRESULT CALLBACK HandleMsgRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_CLOSE) {
		DestroyWindow(hwnd);
	}
	else {
		// retrieve ptr to window class
		WindowContainer* const pWindow = reinterpret_cast<WindowContainer*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		// forward message to window class handler
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_NCCREATE:
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		WindowContainer* pWindow = reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams);
		if (pWindow == nullptr) //Sanity check
		{
			ErrorLogger::Log("Critical Error: Pointer to window container is null during WM_NCCREATE.");
			exit(-1);
		}
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgRedirect));
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}