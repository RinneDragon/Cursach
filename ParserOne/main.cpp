#include "class.h"
#include <iostream> 
#include <cctype>
#include <conio.h>
#include <cstring>

#define ENTER_KEY 13
#define EXIT_KEY 27

using namespace std;

bool isValidCh(char el)
{ 
	return strchr("+-*/().", el);
}

int main() {
	do
	{
		//ввод строки
		MyString str(10);
		cout << "Enter your mathematical expression (valid characters: ( ) + - * / . )." << endl;
		cout <<	"To complete the input, press ENTER. Enter negative numbers in brackets." << endl;
	    auto temp = _getch();		
		size_t brack = 0;
		bool isCorStr = true;
		if ((isValidCh(temp)) && (temp != '(')) isCorStr = false;
		while (temp != ENTER_KEY)
		{
			if ((isdigit(temp)) || (isValidCh(temp))||(isalpha(temp)))
			{
				str.push_back((char)temp);
				cout << str.getEnd();
			}
			if (temp == '(') brack++;
			if (temp == ')') brack--;

			temp = _getch();

			if ((isValidCh(str.getEnd())) && (isValidCh(temp)) && (temp != '(') && (temp != ')') && (str.getEnd() != '(') && (str.getEnd()!= ')')) isCorStr = false;
		}

		cout << endl;
		if ((brack != 0) || (!isCorStr))
		{
			cout << "Your mathematical expression is incorrect. Press any key to continue." << endl << endl;
			continue;
		}
		str.push_back('\0');
		

		using operand = Either<MyString, double>;
		using op = char;
		using token = Either<op, operand>;
		//парсинг строки
		//DynArr<Either<char, double>> mas(str.getCount() + 1);
		DynArr<token> mas(str.getCount() + 1);

		char *beg = str.getData(), *next = nullptr;
		while ((*beg) != '\0')
		{
			if ((isdigit(*beg)) || (((*(beg - 1) == '(') && (*(beg) == '-'))))
			{
				double num = strtod(beg, &next);
				mas.push_back(token::Right(operand::Right(num)));
				beg = next;
			}
			else
			{
				if ((isalpha(*beg)) || (((*(beg - 1) == '(') && (*(beg) == '-'))))
				{
					MyString str_token(1);
					size_t size = 1;
					while (isalpha(*beg))
					{
						str_token.push_back(*beg);
						str_token.resize(size + 1);
						beg++;
					}
					operand tempOperand = operand::Left(str_token); // Крашится тута
					token tempToken = token::Right(tempOperand);
					mas.push_back(tempToken);
					beg = next;
				}
				else 
				{
					mas.push_back(token::Left(*beg));
					beg++;
				}
			}
			
		}

		for (size_t i = 0; i < mas.getCount() + 1; i++)
		{
			auto temp = mas.getAt(i);
			if (temp.isLeft()) cout << temp.getLeft() << ' ';
			if (temp.isRight())
			{
				auto tempR = temp.getRight();
				if (tempR.isRight()) cout << tempR.getRight() << ' ';
				if (tempR.isLeft())  cout << tempR.getLeft().getData() << ' ';
			}
		}
		cout << endl;

		//сортировочная станция
		//DynArr<Either<char, double>> output(mas.getCount() + 1);
		//Stack<char> stek;

		//for (size_t i = 0; i < (mas.getCount() + 1); i++)
		//{
		//	if (mas.getAt(i).isRight()) output.push_back(Either<char, double>::Right(mas.getAt(i).getRight()));

		//	if (mas.getAt(i).isLeft())
		//	{
		//		if (getPrior(mas.getAt(i).getLeft()) == Priority::First)
		//		{
		//			if (stek.isEmpty()) stek.push(mas.getAt(i).getLeft());
		//			else
		//			{
		//				if (getPrior(stek.getTop()) == Priority::First)
		//				{
		//					output.push_back(Either<char, double>::Left(stek.pop()));
		//					stek.push(mas.getAt(i).getLeft());
		//				}
		//				else stek.push(mas.getAt(i).getLeft());
		//			}
		//		}
		//		if (getPrior(mas.getAt(i).getLeft()) == Priority::Second)
		//		{
		//			if (stek.isEmpty()) stek.push(mas.getAt(i).getLeft());
		//			else
		//			{
		//				if (stek.getTop() != '(')
		//				{
		//					output.push_back(Either<char, double>::Left(stek.pop()));
		//					stek.push(mas.getAt(i).getLeft());
		//				}
		//				else stek.push(mas.getAt(i).getLeft());
		//			}
		//		}

		//		if ((mas.getAt(i).getLeft()) == '(') stek.push(mas.getAt(i).getLeft());

		//		if ((mas.getAt(i).getLeft()) == ')')
		//		{
		//			while (stek.getTop() != '(')
		//			{
		//				output.push_back(Either<char, double>::Left(stek.pop()));
		//			}
		//			stek.pop();
		//		}
		//	}
		//}
		//while (!stek.isEmpty())
		//{
		//	output.push_back(Either<char, double>::Left(stek.pop()));
		//}
		////вывод выражения в обратной польской нотации
		//cout << "Your mathematical expression in Reverse Polish notation: ";
		//for (size_t i = 0; i < output.getCount() + 1; i++)
		//{
		//	auto temp = output.getAt(i);
		//	if (temp.isLeft()) cout << temp.getLeft() << ' ';
		//	if (temp.isRight()) cout << temp.getRight() << ' ';
		//}
		//cout << endl;

		////вычисление значения математического выражения
		//Stack<double> res;

		//double tem = 0, buf = 0;
		//for (size_t i = 0; i < (output.getCount() + 1); i++)
		//{
		//	if (output.getAt(i).isRight())
		//	{
		//		res.push(output.getAt(i).getRight());
		//	}

		//	if (output.getAt(i).isLeft())
		//	{
		//		switch (output.getAt(i).getLeft())
		//		{
		//		case '+':
		//		{
		//			buf = res.pop();
		//			tem = res.pop() + buf;
		//			res.push(tem);
		//			break;
		//		}
		//		case '-':
		//		{
		//			buf = res.pop();
		//			tem = res.pop() - buf;
		//			res.push(tem);
		//			break;
		//		}
		//		case '*':
		//		{
		//			buf = res.pop();
		//			tem = res.pop() * buf;
		//			res.push(tem);
		//			break;
		//		}
		//		case '/':
		//		{
		//			buf = res.pop();
		//			tem = res.pop() / buf;
		//			res.push(tem);
		//			break;
		//		}
		//		}
		//	}

		//}
		////результат
		//cout << "Your result: " << tem << endl;
		//cout << "Press any key to continue. To complete the program, press ESC." << endl << endl;
	} while (_getch() != EXIT_KEY);
	return EXIT_SUCCESS;
}