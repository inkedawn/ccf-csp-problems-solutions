﻿// CCF201312-2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

/*

问题描述
　　每一本正式出版的图书都有一个ISBN号码与之对应，ISBN码包括9位数字、1位识别码和3位分隔符，其规定格式如“x-xxx-xxxxx-x”，其中符号“-”是分隔符（键盘上的减号），最后一位是识别码，例如0-670-82162-4就是一个标准的ISBN码。ISBN码的首位数字表示书籍的出版语言，例如0代表英语；第一个分隔符“-”之后的三位数字代表出版社，例如670代表维京出版社；第二个分隔之后的五位数字代表该书在出版社的编号；最后一位为识别码。
　　识别码的计算方法如下：
　　首位数字乘以1加上次位数字乘以2……以此类推，用所得的结果mod 11，所得的余数即为识别码，如果余数为10，则识别码为大写字母X。例如ISBN号码0-670-82162-4中的识别码4是这样得到的：对067082162这9个数字，从左至右，分别乘以1，2，…，9，再求和，即0×1+6×2+……+2×9=158，然后取158 mod 11的结果4作为识别码。
　　编写程序判断输入的ISBN号码中识别码是否正确，如果正确，则仅输出“Right”；如果错误，则输出是正确的ISBN号码。
输入格式
　　输入只有一行，是一个字符序列，表示一本书的ISBN号码（保证输入符合ISBN号码的格式要求）。
输出格式
　　输出一行，假如输入的ISBN号码的识别码正确，那么输出“Right”，否则，按照规定的格式，输出正确的ISBN号码（包括分隔符“-”）。
样例输入
0-670-82162-4
样例输出
Right
样例输入
0-670-82162-0
样例输出
0-670-82162-4

*/

#include "pch.h"
#include <iostream>
#include <string>
#include <cstdlib>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
char ISBNCheckCode(const string& isbn);
inline int c_atoi(const char& c);
inline char c_itoa(const int& i);

int main()
{
	string isbn; getline(cin, isbn);
	char checkcode = ISBNCheckCode(isbn);
	if (isbn.length() != 13) {
		return 1;
	}
	if (isbn.back() == checkcode) {
		cout << "Right" << endl;
	}
	else {
		isbn.back() = checkcode;
		cout << isbn << endl;
	}
	return 0;
}

// input should be "x-xxx-xxxxx-x"
char ISBNCheckCode(const string& isbn) {
	int code = (c_atoi(isbn[0]) * 1 +
		c_atoi(isbn[2]) * 2 +
		c_atoi(isbn[3]) * 3 +
		c_atoi(isbn[4]) * 4 +
		c_atoi(isbn[6]) * 5 +
		c_atoi(isbn[7]) * 6 +
		c_atoi(isbn[8]) * 7 +
		c_atoi(isbn[9]) * 8 +
		c_atoi(isbn[10]) * 9) % 11;
	return (code==10)?'X': c_itoa(code);
}

inline int c_atoi(const char& c) {
	return c - '0';
}

inline char c_itoa(const int& i) {
	return i + '0';
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
