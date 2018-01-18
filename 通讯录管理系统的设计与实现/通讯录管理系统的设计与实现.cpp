// 通讯录管理系统的设计与实现.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "AddressList.h"
#include <cctype>

int main()
{
	int i; 
	int id;
	string name;
	string phone;
	AddressList L(200, 20);
	int choices;
	do {
		cout << "----------主菜单----------" << endl;
		cout << "1-创建通讯录" << endl;
		cout << "2-添加联系人" << endl;
		cout << "3-删除联系人" << endl;
		cout << "4-显示联系人信息" << endl;
		cout << "5-查找联系人" << endl;
		cout << "6-联系人详细信息" << endl;
		cout << "7-创建分组" << endl;
		cout << "8-删除分组" << endl;
		cout << "9-分组显示联系人" << endl;
		cout << "10-保存" << endl;
		cout << "11-读取" << endl;
		cout << "12-退出" << endl;
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
			cout << "请输入你想要查看的联系人姓名：";
			cin >> name;
			id=L.FindName(name);
			do {
				L.Display(name);
				cout << "1-修改姓名" << endl;
				cout << "2-修改住址" << endl;
				cout << "3-修改单位" << endl;
				cout << "4-修改手机号" << endl;
				cout << "5-改变分组" << endl;
				cout << "6-移出所属分组" << endl;
				cout << "7-加入分组" << endl;
				cout << "8-退出" << endl;
				cout << "Enter Choices:";
				cin >> choices;
				switch (choices)
				{
				case 1:
					L.Change(id, 1);
					break;
				case 2:
					L.Change(id, 2);
					break;
				case 3:
					L.Change(id, 3);
					break;
				case 4:
					L.Change(id, 4);
					break;
				case 5:
					L.ChangeGroup(id);
					break;
				case 6:
					L.MoveOutGroup(id);
					break;
				case 7:
					L.AddToGroup(id);
					break;
				case 8:
					break;
				default:
					break;
				}
			} while (choices!=8);
			break;
		case 7:
			cout << "请输入您想创建的分组数：";
			cin >> i;
			L.CreateGroup(i);
			break;
		case 8:
			cout << "输入您想要进行删除的分组：";
			cin >> name;
			L.DeleteGroup(name);
			break;
		case 9:
			L.GroupDisplay();
			break;
		case 10:
			do {
				cout << "1-保存通讯录" << endl;
				cout << "2-保存分组" << endl;
				cout << "3-退出" << endl;
				cout << "Enter Chioces:" << endl;
				cin >> choices;
				switch (choices)
				{
				case 1:
					L.Save();
					break;
				case 2:
					L.SaveGroup();
					break;
				case 3:
					break;
				default:
					break;
				}
			} while (choices!=3);
			
			break;
		case 11:
			L.Read();
			break;
		case 12:
			break;
		default:
			cout << "非法选择！";
			break;
		}
	} while (choices != 12);
    return 0;
}

