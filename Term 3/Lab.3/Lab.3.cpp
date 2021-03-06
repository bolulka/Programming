// Lab.3.cpp : Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "Lab.3.h"

#include "Windows.h"
#include "resource.h"
#include "stdio.h"
#include "Model.h"
#include <iostream>
#include <string>
using namespace std;
//enum operation { TO_INSERT, TO_DELETE };

class DequeView {
private:
	HWND hDial;
	Model* model;
	int idcDeque;
	
public:
	DequeView(HWND h, Model* _model, int IDC) : hDial(h), model(_model), idcDeque(IDC) {}


	void update()
	{
			wstring m = model->to_wstring();
			SendMessageW(GetControl(IDC_TextOut), WM_SETTEXT, m.size() + 1, (LPARAM)m.c_str());
		
	}

	void update(wstring str)
	{
		SendMessageW(GetControl(IDC_TextOut), WM_SETTEXT, str.size() + 1, (LPARAM)str.c_str());
	}

	HWND GetControl(int id)
	{
		return GetDlgItem(hDial, id);
	}

};



INT_PTR CALLBACK Controller(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static Model model;
	static DequeView view(hDlg, &model, IDC_TextOut);
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:

		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;

		}
		case IDC_PushFront:
		{
			int a = GetDlgItemInt(hDlg, IDC_TextIn, NULL, true);
			model.PushFront(a);
			view.update(); 
		}
		break;
		case IDC_PushBack:
		{
			int b = GetDlgItemInt(hDlg, IDC_TextIn, NULL, true);
			model.PushBack(b);
			view.update();
		}
		break;
		case IDC_PopBack:
		{
			if (model.Size() == 0) break;
			model.PopBack();
			view.update();
		}
		break;
		case IDC_PopFront:
		{
			if (model.Size() == 0) break;
			model.PopFront();
			view.update();
		}
		break;

		case IDC_Front:
		{
			if (model.Size() == 0) break;
			wstring str = to_wstring(model.Front());
			view.update(str);
		}
		break;

		case IDC_Back:
		{
			if (model.Size() == 0) break;
			wstring str = to_wstring(model.Back());
			view.update(str);
		}
		break;
		
		case IDC_Size:
		{
			wstring str = to_wstring(model.Size());
			view.update(str);
		}
		}

		break;
	}
	return (INT_PTR)FALSE;

}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	DialogBox(hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), NULL, Controller);
	return 0;
}
