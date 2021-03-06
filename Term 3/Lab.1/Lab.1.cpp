// Lab.1.cpp : Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "Lab.1.h"
#include "Deque.h"

#include <sstream>

#include <CommCtrl.h>
#include "WinApiModule.h"
#include <CommCtrl.h>
#include <cstdlib>
#include <string>
#include <cstring>

#define DLGTITLE  L"Lab.1"
#define DLGFONT   L"Deque"

namespace Control
{
	int const IDC_TestTextBox1 = 1001;
	int const IDC_PushFront = 1002;
	int const IDC_TestLabel = 1003;
	int const IDC_PushBack = 1004;
	int const IDC_PopFront = 1005;
	int const IDC_PopBack = 1006;
	int const IDC_Swap = 1007;
	int const IDC_IndexForSwap1 = 1008;
	int const IDC_IndexForSwap2 = 1009;
	int const IDC_Front = 1010;
	int const IDC_Back = 1011;
}

// Эта структура — эмуляция пустого ресурса диалога.
// См. файл .rc в проекте WinAPI по умолчанию.
// По сути, что-то аналогичное заданию класса окна.
#pragma pack(push, 4)                 
static struct
{
	DWORD  style;
	DWORD  dwExtendedStyle;
	WORD   ccontrols; // Количество контролов. Контролы можно объявлять прямо тут, в этой структуре после всех полей, но зачем?
	short  x;
	short  y;
	short  cx;
	short  cy;
	WORD   menu;
	WORD   windowClass;
	WCHAR  wszTitle[ARRAYSIZE(DLGTITLE)];
	short  pointsize; // Масштабирование координат. См. FromUnit для преобразования координат.
	WCHAR  wszFont[ARRAYSIZE(DLGFONT)];
}
EmptyDialogTemplate =
{
   DS_SHELLFONT | DS_SETFONT | DS_MODALFRAME | DS_FIXEDSYS | WS_POPUP | WS_CAPTION | WS_SYSMENU, // Модальное!
   0x0,
   0,
   0, 0, 360, 180,
   0,                       // menu: none
   0,                       // window class: none
   DLGTITLE,                // Window caption
   8,                       // font pointsize
   DLGFONT,
};
#pragma pack(pop)

Deque dec;

class Application
{
	static HWND _hDialog;

public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_LBUTTONDOWN:
		{
			OnClick(hWnd);
			return true;
		}

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			auto hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;
		}

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

		return 0;
	}

private:
	static void OnClick(HWND hWnd)
	{
		// Восстанавливаем hInst по hWnd.
		auto hInst = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);
		// Запускаем диалог.
		DialogBoxIndirectParamW(hInst, (LPCDLGTEMPLATEW)&EmptyDialogTemplate, hWnd, DlgProc, NULL);
	}

	static INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
	{
		UNREFERENCED_PARAMETER(lParam);
		switch (message)
		{
		case WM_INITDIALOG:
		{
			_hDialog = hDlg;
			OnInitDialog();
			return (INT_PTR)TRUE;
		}

		case WM_COMMAND:
			return (INT_PTR)OnCommand(wParam);

		case WM_CLOSE:
			EndDialog(hDlg, IDCANCEL);
			break;
		}

		return (INT_PTR)FALSE;
	}

	static void OnInitDialog()
	{
		// Создаём все контролы.

		CreateDialogControl(L"EDIT", L"Data", ES_AUTOHSCROLL, 27, 18, 82, 14, Control::IDC_TestTextBox1);
		CreateDialogControl(L"BUTTON", L"PushFront", NULL, 28, 45, 40, 14, Control::IDC_PushFront);
		CreateDialogControl(L"BUTTON", L"PushBack", NULL, 70, 45, 40, 14, Control::IDC_PushBack);
		CreateDialogControl(L"BUTTON", L"PopFront", NULL, 28, 65, 40, 14, Control::IDC_PopFront);
		CreateDialogControl(L"BUTTON", L"PopBack", NULL, 70, 65, 40, 14, Control::IDC_PopBack);
		CreateDialogControl(L"STATIC", L"Deque", NULL, 160, 20, 82, 28, Control::IDC_TestLabel);
		CreateDialogControl(L"EDIT", L"Data", ES_AUTOHSCROLL, 48, 100, 20, 20, Control::IDC_IndexForSwap1);
		CreateDialogControl(L"EDIT", L"Data", ES_AUTOHSCROLL, 72, 100, 20, 20, Control::IDC_IndexForSwap2);
		CreateDialogControl(L"BUTTON", L"Swap", NULL, 50, 125, 40, 14, Control::IDC_Swap);
		CreateDialogControl(L"BUTTON", L"First element", NULL, 150, 80, 50, 14, Control::IDC_Front);
		CreateDialogControl(L"BUTTON", L"Last element", NULL, 210, 80, 50, 14, Control::IDC_Back);


	}

	static HWND CreateDialogControl(const wchar_t* className, const wchar_t* text, DWORD style, int X, int Y, int width, int height, int id)
	{
		return CreateWindowEx(
			NULL,
			className,
			text,
			WS_VISIBLE | WS_CHILD | WS_TABSTOP | style,
			FromUnit(X), FromUnit(Y),
			FromUnit(width), FromUnit(height),
			_hDialog,
			(HMENU)id,
			nullptr, nullptr);
	}

	static int FromUnit(int value)
	{
		return MulDiv(value, LOWORD(GetDialogBaseUnits()), 4);
	}

	static BOOL OnCommand(WPARAM wParam)
	{
		auto controlID = LOWORD(wParam);
		auto notification = HIWORD(wParam);

		switch (controlID)
		{
		case Control::IDC_PushFront:
		{
			AddDataFront();
			Print();
			break;
		}

		case Control::IDC_PushBack:
		{	
			AddDataBack();
			Print();
			break;
		}
			
		case Control::IDC_PopFront:
		{
			dec.PopFront();
			Print();
			break;
		}

		case Control::IDC_PopBack:
		{
			dec.PopBack(); 
			Print();
			break;
		}
			
		case Control::IDC_Swap:
		{
			AddDataForSwap();
			Print();
			break;
		}

		case Control::IDC_Front:
		{
			if (dec.IsEmpty()) return SetLabelText(L" ");
			else
			{
				int temp1 = dec.Front();
				std::wstring temp2 = std::to_wstring(temp1);
				temp2.push_back('\n');
				return SetLabelText(&temp2[0]);
				break;
			}
		}
			
		case Control::IDC_Back:
		{
			if (dec.IsEmpty()) return SetLabelText(L" ");
			else
			{
				int temp1 = dec.Back();
				std::wstring temp2 = std::to_wstring(temp1);
				temp2.push_back('\n');
				return SetLabelText(&temp2[0]);
				break;
			}
		}
		}

		/*case Control::IDC_TestTextBox1:
			return ProcessTestTextBox(notification);

		case Control::IDC_IndexForSwap1:
			return ProcessTestTextBox(notification);

		case Control::IDC_IndexForSwap2:
			return ProcessTestTextBox(notification);*/

		return FALSE;
	}

	static BOOL ProcessTestTextBox(WORD notification)
	{
		switch (notification)
		{
		case EN_CHANGE:
		{
			auto testTextBox = GetControl(Control::IDC_TestTextBox1);
			auto textLength = GetWindowTextLengthW(testTextBox);
			int temp;
			auto buffer = new char[textLength + 1];
			SendMessage(testTextBox, WM_GETTEXT, textLength, (LPARAM)buffer);
			temp=atoi(buffer);
			//SetLabelText(buffer);
			delete[] buffer;
			return temp;
		}

		default:
			return FALSE;
		}
	}

	static BOOL Print()
	{
		//std::stringstream ss;
		//ss << dec;
		//std::string str = ss.str();
		//std::wstring wstr(str.begin(), str.end());
		//wstr.push_back('\n');
		//auto Label = GetControl(Control::IDC_TestLabel );
		////SendDlgItemMessage(Label, NULL, LB_DELETESTRING, NULL, NULL);
		//SendMessageW(Label, WM_SETTEXT, wstr.size() +1, (LPARAM)wstr.c_str());
		//return TRUE;
		std::wstring str;
		str = dec.to_String();
		/*char buf[256];
		strcpy_s(buf, str.c_str());*/

		
		auto Label = GetControl(Control::IDC_TestLabel);
		SendMessageW(Label, WM_SETTEXT, str.size() + 1, (LPARAM)str.c_str());
		return TRUE;
	}

	static BOOL AddDataFront()
	{
		auto TextBox = GetControl(Control::IDC_TestTextBox1);
		auto textLength = GetWindowTextLengthW(TextBox);
		auto buffer = new wchar_t[textLength + 1];
		SendMessage(TextBox, WM_GETTEXT, textLength + 1, (LPARAM)buffer);
		int temp = std::stoi(std::wstring(buffer));
		dec.PushFront(temp);
		return TRUE;
	}

	static BOOL AddDataForSwap()
	{
		auto TextBox1 = GetControl( Control::IDC_IndexForSwap1 );
		auto TextBox2 = GetControl( Control::IDC_IndexForSwap2 );
		auto textLength1 = GetWindowTextLengthW(TextBox1);
		auto textLength2 = GetWindowTextLengthW(TextBox2);
		auto buffer1 = new wchar_t[textLength1 + 1];
		auto buffer2 = new wchar_t[textLength2 + 1];
		SendMessage(TextBox1, WM_GETTEXT, textLength1+1, (LPARAM)buffer1);
		SendMessage(TextBox2, WM_GETTEXT, textLength2+1, (LPARAM)buffer2);
		int index1 = std::stoi(std::wstring(buffer1));
		int index2 = std::stoi(std::wstring(buffer2));
		dec.Swap(index1, index2);
		return TRUE;
	}

	static BOOL AddDataBack()
	{
		auto TextBox = GetControl( Control::IDC_TestTextBox1 );
		auto textLength = GetWindowTextLengthW(TextBox);
		auto buffer = new wchar_t[textLength + 1];
		SendMessage(TextBox, WM_GETTEXT, textLength + 1, (LPARAM)buffer);
		int temp = std::stoi(std::wstring(buffer));
		dec.PushBack(temp);
		return TRUE;
	}

	

	static HWND GetControl(int id)
	{
		return GetDlgItem(_hDialog, id);
	}

	static BOOL SetLabelText(const wchar_t* text)
	{
		auto testLabel = GetControl(Control::IDC_TestLabel);
		SendMessageW(testLabel, WM_SETTEXT, 0, (LPARAM)text);
		return TRUE;
	}

	
};

HWND Application::_hDialog;

int APIENTRY WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	auto winApiModule = WinApiModule(
		L"1. Deque and pattern Iterator",
		L"1. Deque and pattern Iterator",
		hInstance,
		Application::WndProc);

	return winApiModule.Run(nCmdShow);
}