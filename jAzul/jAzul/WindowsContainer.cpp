#include "WindowsContainer.h"
#include <memory>

WindowContainer::WindowContainer() :
	graphicsEngine(),
	kb(),
	windowRenderer(),
	mo()
{
	static bool raw_in_init = false;

	// Register Mouse Inpiut
	if (!raw_in_init) {
		RAWINPUTDEVICE rid;

		rid.usUsagePage = 0x01;
		rid.usUsage = 0x02;
		rid.dwFlags = 0;
		rid.hwndTarget = nullptr;

		if (RegisterRawInputDevices(&rid, 1, sizeof(rid)) == FALSE) {
			ErrorLogger::Log(GetLastError(), "Failed to Register RID");
			exit(-1);
		}
		raw_in_init = true;
	}
}

LRESULT WindowContainer::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	switch (uMsg) {
		// MOUSE MESSAGES
	case WM_KEYDOWN:
	{
		if (wParam == VK_ESCAPE) {
			DestroyWindow(hwnd);
			return 0;
		}

		const unsigned char key = (unsigned char)wParam;

		kb.OnKeyPressed(key);
	}
	break;

	case WM_KEYUP:
	{
		const unsigned char key = (unsigned char)wParam;
		kb.OnKeyReleased(key);
	}
	break;

	case WM_CHAR:
	{
		const unsigned char key = (unsigned char)wParam;
		
		kb.OnChar(key);
	}
	break;

	// MOUSE MESSAGES
	case WM_MOUSEMOVE:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		this->mo.OnMouseMove(x, y);
	}
	break;

	case WM_LBUTTONDOWN:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		this->mo.OnLeftPressed(x, y);
	}
	break;

	case WM_RBUTTONDOWN:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		this->mo.OnRightPressed(x, y);
	}
	break;

	case WM_MBUTTONDOWN:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		this->mo.OnMiddlePressed(x, y);
	}
	break;

	case WM_LBUTTONUP:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		this->mo.OnLeftReleased(x, y);
	}
	break;

	case WM_RBUTTONUP:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		this->mo.OnRightReleased(x, y);
	}
	break;

	case WM_MBUTTONUP:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		this->mo.OnMiddleReleased(x, y);
	}
	break;

	case WM_MOUSEWHEEL:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) {
			this->mo.OnWheelUp(x, y);
		}
		else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0) {
			this->mo.OnWheelDown(x, y);
		}
	}
	break;
	
	case WM_INPUT:
	{
		UINT dataSize;
		GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER)); //Need to populate data size first

		if (dataSize > 0) {
			std::unique_ptr<BYTE[]> raw_data = std::make_unique<BYTE[]>(dataSize);

			if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, raw_data.get(), &dataSize, sizeof(RAWINPUTHEADER)) == dataSize) {
				RAWINPUT* raw = (RAWINPUT*)(raw_data.get());

				if (raw->header.dwType == RIM_TYPEMOUSE) {
					this->mo.OnMouseMoveRaw(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
				}
			}
		}

		result = DefWindowProc(hwnd, uMsg, wParam, lParam); //Need to call DefWindowProc for WM_INPUT messages

	}
	break;

	default:
		result = DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	}

	return result;
}
