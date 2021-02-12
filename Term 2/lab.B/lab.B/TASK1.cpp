#include <iostream>
#include <cmath>

using namespace std;


int Ñomputing(int argName1, int argName2, int argName3)
{
    int result;
	__asm
	{
	
		mov eax, argName1
		mov ebx, argName3
		; cdq
	 mov ecx,4
	 imul ecx
	 imul ebx

	 mov ebx, eax
	 mov ecx, edx
	 mov eax, argName2
	 imul eax

	 cmp edx, ecx
	 jg DiscPos
	 jl DiscNeg

	 cmp eax, ebx
	 jg DiscPos
	 jl DiscNeg
	 jz DiscZero

	 DiscNeg:
	    mov result, 0
			jmp mark

	 DiscPos :
	    mov result, 2
			jmp mark

	DiscZero:
		mov result, 1
			jmp mark

	mark:
		
	}
	return result;
}



int main()
{
	int res;
	double a;
	double b;
	double c;
	wcout << L"A = ";
	wcin >> a;
	wcout << L"B = ";
	wcin >> b;
	wcout << L"C = ";
	wcin >> c;
	res=Ñomputing(a, b, c);
	wcout <<L"Number of solutions: "<< res << endl;
	system("pause");
	return 0;
}