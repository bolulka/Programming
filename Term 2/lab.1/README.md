# Sem2_lab.1

1. Индекс базы.
Создать вектор студентов (каждый студент имеет свой ID:uint, Фамилию:(w)string, Имя:(w)string). 
Переорганизвать коллекцию так, чтобы обеспечить быстрый поиск по точному ID студента.
Запросить в консоли ID студента. Если такой присутствует, вывести его фамилию и имя. Если нет, вывести соответствующее сообщение.
2. Полиглот.
Дано следующее мульти-отображение:
{
	{ 1, L"адзін" },
	{ 1, L"один" },
	{ 1, L"one" },
	{ 2, L"два" },
	{ 2, L"two" },
	{ 3, L"тры" },
	{ 3, L"три" },
	{ 3, L"three" },
	{ 4, L"чатыры" },
	{ 4, L"четыре" },
	{ 4, L"four" },
}
При помощи методов lower_bound и upper_bound выведите все доступные варианты написания числа N. Если нету ни одного варианта, выведите соответствующее сообщение.
