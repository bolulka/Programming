#include <iostream>
#include <list>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

void Task1()
	{
	   
		std::cout << "Task 1" << std::endl;;
		std::list<int> arr = { 3, 5, -3, 7, 11, 9, -1 };

		//show
		std::cout << "Data: ";
		std::for_each(arr.begin(), arr.end(), [](int n) { std::cout << n << ' '; });

		//sort
		std::cout << std::endl << "Sorted: ";
		arr.sort([](int l, int r) { return abs(l) < abs(r); });
		std::for_each(arr.begin(), arr.end(), [](int n) { std::cout << n << ' '; });
		std::cout << std::endl;

		//first odd element
		auto first_odd = std::find_if(arr.begin(), arr.end(), [](int n) { return (n % 2 == 0); });
		if (first_odd == arr.end()) { std::cout << "No odd numbers \n"; }
		else { std::cout << "First odd number: " << *first_odd << '\n'; }

		//number of odd elements
		int count = 0;
		std::for_each(arr.begin(), arr.end(), [&count](int n) { count += (n % 2 == 0); });
		std::cout << "Odd number quantity: " << count << '\n';

		// replace negative to 0
		std::for_each(arr.begin(), arr.end(), [](int& n) { if (n < 0) { n = 0; } });
		std::cout << "Replacing negatives to zero: ";
		std::for_each(arr.begin(), arr.end(), [](int n) { std::cout << n << ' '; });

}
	

    template <typename T>
	T FSums(T first)
	{
		return first;
	}

	template <typename T, typename ... Args>
	T FSums(T first, Args ... args)
	{
		auto lambda = [](Args ... args) { return FSums(args...); };
		return first + lambda(args...);
	}

	void Task2()
	{
		std::cout << "\n\nTask 2 \n";
		short m = 13;
		int n1 = 17, n2 = 23;
		double x = 12.8;
		auto xSum = FSums(n1, 4.7, m, 1.5, 10, n2, x, 'b');
		std::cout << "xSum = " << xSum << std::endl;
	}

	template <typename T>
	std::string ToString(std::string separator, T first)
	{
		return std::to_string(first) + separator;
	}

	template <typename T, typename ... Args>
	std::string ToString(std::string separator, T first, Args ... args)
	{
		auto lambda = [](std::string separator, Args ... args) {return ToString(separator, args...); };
		return ToString(separator, first) + lambda(separator, args...);
	}

	void Task3()
	{
		std::cout << "\nTask 3 \n";
		int n = 17;
		double x = 6.75;
		std::cout << ToString(", ", 25, 3.7, n, x);
	}


int main()
{
	Task1();
	Task2();
	Task3();

	std::cout << std ::endl;
	system("pause");
	return 0;
}