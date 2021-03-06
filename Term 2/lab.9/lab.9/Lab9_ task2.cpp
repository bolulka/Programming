// Lab9_ task2.cpp : Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "WinApiModule.h"
#include "Colors.h"
#include <string>

class Application
{
	static bool mouseClicked;
	static bool rectangleDragged;
	static const int rowsCount = 2;
	static const int columnsCount = 2;
	static const int fieldCount = 2;
	static const int paddingX = 150;
	static const int paddingY = 150;
	static const int border = 25;
	static const int textFieldHeight = 25;
	static const int squareSize = 50;
	static const int fieldHeight = columnsCount * (squareSize + border) + border;
	static const int fieldWidth = rowsCount * (squareSize + border) + border;
	static const int fieldSpacing = 175;
	static bool rectangles[fieldCount][rowsCount * columnsCount];
public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_LBUTTONDOWN:
		{
			auto mouseX = LOWORD(lParam);
			auto mouseY = HIWORD(lParam);
			mouseClicked = true;
			InvalidateRect(hWnd, nullptr, true);

			for (int i = 0; i < fieldCount; i++)
			{
				for (int j = 0; j < rowsCount; j++)
				{
					for (int k = 0; k < columnsCount; k++)
					{
						if (rectangles[i][j * rowsCount + k])
						{
							if (mouseX >= paddingX + i * (fieldWidth + fieldSpacing) + border + k * (border + squareSize)
								&& mouseY >= paddingY + textFieldHeight + j * (border + squareSize)
								&& mouseX <= paddingX + i * (fieldWidth + fieldSpacing) + border + squareSize + k * (border + squareSize)
								&& mouseY <= paddingY + textFieldHeight + j * (border + squareSize) + squareSize)
							{
								rectangles[i][j * rowsCount + k] = false;
								rectangleDragged = true;
							}
						}
					}
				}
			}
			if (rectangleDragged)
			{
				RECT rect;
				GetClientRect(hWnd, &rect);
				POINT positionLeftTop = { rect.left, rect.top };
				ClientToScreen(hWnd, &positionLeftTop);
				POINT positionRightBottom = { rect.right, rect.bottom };
				ClientToScreen(hWnd, &positionRightBottom);
				RECT rectCapture;
				SetRect(&rectCapture, positionLeftTop.x, positionLeftTop.y, positionRightBottom.x - squareSize, positionRightBottom.y - squareSize);
				ClipCursor(&rectCapture);
			}
			break;
		}

		case WM_LBUTTONUP:
		{
			auto mouseX = LOWORD(lParam);
			auto mouseY = HIWORD(lParam);
			mouseClicked = false;
			InvalidateRect(hWnd, nullptr, true);
			ClipCursor(nullptr);
			if (rectangleDragged)
			{
				rectangleDragged = false;
				int fieldIndex = 0;
				if (mouseX >= paddingX + 250 && mouseX <= paddingX+125 + 250 && mouseY >= paddingY && mouseY <= paddingY+125)
				{
					fieldIndex = 1;
				}
				for (int i = 0; i < rowsCount * columnsCount; i++)
				{
					if (!rectangles[fieldIndex][i])
					{
						rectangles[fieldIndex][i] = true;
						break;
					}
				}
			}
			break;
		}
		case WM_CREATE:
		{
			OnCreate(hWnd);
			return true;
		}

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			auto hdc = BeginPaint(hWnd, &ps);
			OnPaint(hWnd, hdc);
			EndPaint(hWnd, &ps);
			break;
		}

		case WM_MOUSEMOVE:
			OnMouseMove(hWnd);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

		return 0;
	}

private:
	static void OnCreate(HWND hWnd)
	{
		rectangles[0][0] = true;
		rectangles[0][1] = true;
		rectangles[0][2] = true;
		rectangles[0][3] = true;

		rectangles[1][0] = false;
		rectangles[1][1] = false;
		rectangles[1][2] = false;
		rectangles[1][3] = false;
	}

	static void SetRectFields(RECT* rect, int x, int y, int width, int height)
	{
		SetRect(rect, x, y, x + width, y + height);
	}

	static void OnMouseMove(HWND hWnd)
	{
		POINT mousePosition;
		GetCursorPos(&mousePosition);
		ScreenToClient(hWnd, &mousePosition);

		InvalidateRect(hWnd, nullptr, true);
	}

	static void OnPaint(HWND hWnd, HDC hdc)
	{
		auto fieldRectBrush = CreateSolidBrush(Color::Aquamarine);
		auto objectRectBrush = CreateSolidBrush(Color::Orchid);
		auto highlitedObjectRectBrush = CreateSolidBrush(Color::LiteSeaGreen);

		for (int i = 0; i < 2; i++)
		{
			RECT rect = { paddingX+85 + i * 250, paddingY-50, paddingX+150 + i * 250, paddingY-25 };
			int quantity = 0;
			for (int j = 0; j < 4; j++)
			{
				if (rectangles[i][j]) quantity++;
			}
			auto text = std::to_wstring(quantity);
			DrawTextW(hdc, text.c_str(), text.size(), &rect, NULL);
		}

		SelectObject(hdc, fieldRectBrush);
		for (int i = 0; i < fieldCount; i++)
		{
			RECT Field = { paddingX + i * 250, paddingY, paddingX +175 + i * 250, paddingY+175 };
			DrawRectangle(hdc, Field);
		}

		for (int i = 0; i < fieldCount; i++)
		{
			for (int j = 0; j < rowsCount; j++)
			{
				for (int k = 0; k < columnsCount; k++)
				{
					if (rectangles[i][j * rowsCount + k])
					{
						SelectObject(hdc, objectRectBrush);
						RECT rect = { paddingX + i * 250 + border + k * 75, paddingY+border + j * 75 , paddingX + i * 250 + border + 50 + k * 75, paddingY + border+squareSize + j * 75  };
						DrawRectangle(hdc, rect);
					}
				}
			}
		}

		if (rectangleDragged)
		{
			bool inField = false;
			POINT mousePosition;
			GetCursorPos(&mousePosition);
			ScreenToClient(hWnd, &mousePosition);
			for (int i = 0; i < 2; i++)
			{
				if (mousePosition.x >= paddingX + i * 250 && mousePosition.x <= paddingX+125 + i * 250 && mousePosition.y >= paddingY && mousePosition.y <= paddingY+125)
				{
					inField = true;
				}
			}
			SelectObject(hdc, !inField ? highlitedObjectRectBrush : objectRectBrush);
			RECT rect = { mousePosition.x, mousePosition.y, 50 + mousePosition.x, 50 + mousePosition.y };
			DrawRectangle(hdc, rect);
		}

		DeleteObject(fieldRectBrush);
		DeleteObject(objectRectBrush);
		DeleteObject(highlitedObjectRectBrush);
	}


	static void DrawRectangle(const HDC& hdc, const RECT& rect)
	{
		Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
	}
};

bool Application::rectangles[Application::fieldCount][Application::columnsCount * Application::rowsCount];
bool Application::mouseClicked = false;
bool Application::rectangleDragged = false;

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	auto winApiModule = WinApiModule(
		L"Lab9",
		L"Lab9",
		hInstance,
		Application::WndProc);

	return winApiModule.Run(nCmdShow);
}