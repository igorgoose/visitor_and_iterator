#include <iostream>
#include <string>
#include <ctime>
#include <Windows.h>
#include "stacc.h"

using namespace std;


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(0, "");
	int decision;
	srand(time(0));
	try {
		while (true) {
			cout << "1 - ������ �� ������ int" << endl;
			cout << "2 - ������ �� ������ string" << endl;
			cout << "3 - �����" << endl;
			cin >> decision;
			switch (decision) {
			case 1: {
				system("cls");
				int dec2;
				int *arr = new int[5];
				cout << "1 - ��������� ���� �������������" << endl;
				cout << "2 - ��������� ���� �������" << endl;
				cin >> dec2;
				bool init = false;
				while (!init) {
					switch (dec2) {
					case 1:
						for (int i = 0; i < 5; i++) {
							arr[i] = rand() % 100;
						}
						init = true;
						break;
					case 2:
						cout << "������� 5 ����� �����" << endl;
						for (int i = 0; i < 5; i++) {
							cin >> arr[i];
						}
						init = true;
						break;
					default:
						cerr << "�������� ����!";
						break;
					}
				}
				stacc<int> ist(arr, 5);
				visitorMax<int> max;
				visitorMin<int> min;
				visitorIMax<int> imax;
				visitorIMin<int> imin;
				cout << "����: " << ist << endl;
				cout << "VisitorMAX :" << ist.accept(max) << endl;
				cout << "VisitorIMAX :" << ist.accept(imax) << endl;
				cout << "VisitorMIN :" << ist.accept(min) << endl;
				cout << "VisitorIMIN :" << ist.accept(imin) << endl;
				system("pause");
				system("cls");
				break;
			}
			case 2: {
				system("cls");
				int dec2;
				string arr[5];
				cout << "1 - ��������� ���� �������������" << endl;
				cout << "2 - ��������� ���� �������" << endl;
				cin >> dec2;
				bool init = false;
				while (!init) {
					switch (dec2) {
					case 1: {
						for (int i = 0; i < 5; i++) {
							for (int j = 0; j < 5; j++) {
								arr[i] += rand() % 26 + 65;
							}
						}
						init = true;
					}
							break;
					case 2:
						cout << "������� 5 ����" << endl;
						for (int i = 0; i < 5; i++) {
							cin >> arr[i];
						}
						init = true;
						break;
					default:
						cerr << "�������� ����!";
						break;
					}
				}
				stacc<string> ist(arr, 5);
				visitorMax<string> max;
				visitorMin<string> min;
				visitorIMax<string> imax;
				visitorIMin<string> imin;
				cout << "����: " << ist << endl;
				cout << "VisitorMAX :" << ist.accept(max) << endl;
				cout << "VisitorIMAX(c ����������) :" << ist.accept(imax) << endl;
				cout << "VisitorMIN :" << ist.accept(min) << endl;
				cout << "VisitorIMIN(� ����������) :" << ist.accept(imin) << endl;
				system("pause");
				system("cls");
				break;
			}
			case 3:
				return 0;
			default:
				cerr << "�������� ����!" << endl;
				system("pause");
				system("cls");
				break;
			}
		}
	}
	catch (const char* err) {
		cout << err << endl;
	}
	system("pause");
	return 0;
}