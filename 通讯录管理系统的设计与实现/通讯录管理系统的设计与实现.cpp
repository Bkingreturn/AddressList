// 通讯录管理系统的设计与实现.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "AddressList.h"

int main()
{
	int i; 
	string name;
	string phone;
	AddressList L(200,20);
	int choices;
	do {
		cout << "1-创建通讯录" << endl;
		cout << "2-添加联系人" << endl;
		cout << "3-删除联系人" << endl;
		cout << "4-显示联系人信息" << endl;
		cout << "5-查找联系人" << endl;
		cout << "6-创建分组" << endl;
		cout << "7-将联系人xx添加到分组xx中" << endl;
		cout << "8-分组显示联系人" << endl;
		cout << "9-保存" << endl;
		cout << "10-读取" << endl;
		cout << "11-退出" << endl;
		cout << "Enter Choice:";
		cin >> choices;
		switch (choices)
		{
		case 1:
			cout << "请输入要创建的通讯录的联系人个数：";
			cin >> i;
			L.CreateAddressList(i);
			break;
		case 2:
			L.Insert();
			break;
		case 3:
			cout << "请输入您想要删除的联系人：";
			cin >> name;
			L.Delete(name);
			break;
		case 4:
			L.ListDisp();
			break;
		case 5:
			cout << "请输入你想要的查找方式【按姓名查找（1），按手机号查找（2）】：";
			cin >> i;
			if (i == 1) {
				cout << "请输入你想要查找的联系人姓名：";
				cin >> name;
				L.MoveName(name);
			}
			else if (i == 2) {
				cout << "请输入你想要查找的联系人手机号：";
				cin >> phone;
				L.MovePhone(phone);
			}
			break;
		case 6:
			cout << "请输入您想创建的分组数：";
			cin >> i;
			L.CreateGroup(i);
			break;
		case 7:
			cout << "输入您想要进行分组的联系人：";
			cin >> name;
			L.AddToGroup(name);
			break;
		case 8:
			L.GroupDisplay();
			break;
		case 9:
			L.Save();
			break;
		case 10:
			L.Read();
			break;
		case 11:
			break;
		default:
			cout << "非法选择！";
			break;
		}
	} while (choices != 11);
    return 0;
}

