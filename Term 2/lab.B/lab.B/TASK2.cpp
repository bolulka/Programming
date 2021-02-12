#include <iostream> 
#include <iso646.h> 

using namespace std;


int __fastcall CalculateDegree(unsigned int a, unsigned int b)
{

	unsigned int result;
	__asm
	{
		mov eax, a
		mov ecx, b

		cmp ecx, 1
		jg _begin1
		je _end

		_zero :
		mov eax, 1
			jmp _end

			_begin1 :
		sub ecx, 1
			_begin :
			imul a
			loop _begin
			_end :

		mov edx, b
			mov result, eax
	}

	return result;
}

int FindSum(unsigned int n, unsigned int m)
{
	int result;
	__asm
	{
		mov ecx, n
		mov edx, m
		mov ebx, 0
		mov edi, n
		cmp ecx, 0
		jg _begin
		mov ebx, 0
		jmp _end

		_begin :
		call CalculateDegree
			mov ecx, edi
			sub edi, 1
			add ebx, eax
			loop _begin
			_end :

		mov result, ebx

	}

	return result;

}




int main()
{

	unsigned int n;
	unsigned int m;
	wcout<< L"Input number of terms : ";
	wcin >> n;
	wcout << L"Input degree : ";
	wcin >> m;

	wcout << L"Result: " << FindSum(n,m);

	std::wcin.get();
	std::wcin.get();

}
