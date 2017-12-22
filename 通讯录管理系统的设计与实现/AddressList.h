#pragma once
#include<iostream>
#include<string>
using namespace std;
struct Human
{
	string  group_name;
	int id;
	string name;
	string company_name;
	string address;
	string phone;
};

struct Group
{
	string name;
};
class AddressGroup {
private:
	Group *group;
	int length;
	int listsize;
public:
	AddressGroup() {};//默认构造函数；
	AddressGroup(int m);//构造函数,分配连续空间；
	~AddressGroup();//析构函数；
	void CreateGroup(int n);//创建m个分组；
	void AddGroup();//添加分组；
	string GetGroupName(int);//获取组名；
	int GetLen();//获取表长
};
AddressGroup::AddressGroup(int m) {
	group = new Group[m];//动态申请一组连续的内存空间；
	if (!group) cout << "内存分配失败！";
	length = 0;
	listsize = m;
}
AddressGroup::~AddressGroup() {
	delete[]group;
	group = NULL;
	length = 0;
	listsize = 0;
}
void AddressGroup::CreateGroup(int n) {
	if (n > listsize) cout << "参数非法！" << endl;
	for (int i = 0; i < n; i++) {
		cout << "请输入组名：";
		cin >> group[i].name;
	}
	length = n;
}
void AddressGroup::AddGroup() {
	if (length > listsize) cout << "注意！注意！分组过多！" << endl;
	Group g;
	cout << "请输入组名：";
	cin >> g.name;
	group[length] = g;
	length++;
}
string AddressGroup::GetGroupName(int n) {
	return group[n].name;
}
int AddressGroup::GetLen() {
	return length;
}

class AddressList:public AddressGroup {
private:
	Human *elem;//表基地址；
	int length;//表长；
	int listsize;//表容量；
public:
	AddressList(int m,int n):AddressGroup(n) {
		elem = new Human[m];//动态申请一组连续的内存空间；
		if (!elem) cout << "内存分配失败！";
		length = 0;
		listsize = m;
	};//构造函数，创造容量为m的通讯录；
	~AddressList();//析构函数，删除通讯录空间；
	void CreateAddressList(int n);//创建具有n个记录的通讯录；
	void Insert();//在通讯录尾插入一条记录；
	string Delete(string name);//删除一条记录；
	void GetElem(int i);//获取第i个记录的值；
	int Locate(string name);//元素定位；
	void Clear();//清空记录；
	int Empty();//检测通讯录是否为空；
	int Full();//检测通讯录是否已满；
	int Length();//检测通讯录的长度；
	void ListDisp();//输出通讯录；
	void Save();//将通讯录存入文件；
	void Read();//从文件中读取通讯录；
	void Find();//查找通讯录中的记录；
	void Sort();//将通讯录中的记录进行排序；
	void Move();//使查找和显示的记录位置前移或后移；
	void GroupDisplay();//分组显示；
	void AddToGroup(string);//加入组；
};
/*AddressList::AddressList(int m) {
	elem = new Human[m];//动态申请一组连续的内存空间；
	if (!elem) cout << "内存分配失败！";
	length = 0;
	listsize = m;
}*/
AddressList::~AddressList() {
	delete[]elem;
	elem = NULL;
	length = 0;
	listsize = 0;
}
void AddressList::CreateAddressList(int n) {
	if (n > listsize) cout << "参数非法！";
	cout << "请依次输入" << n << "条记录：" << endl;
	for (int i = 1; i <= n; i++) {
		cout << "请输入姓名，单位，住址，电话：";
		cin >> elem[i].name >> elem[i].company_name >> elem[i].address >> elem[i].phone;
		elem[i].id = i;
	}
	length = n+1;
}
void AddressList::Insert() {
	if (length > listsize) cout << "通讯录已满。" << endl;
	Human e;
	cout << "请输入姓名，单位，住址，电话：";
	cin >> e.name >> e.company_name >> e.address >> e.phone;
	e.id = length;
	elem[length] = e;
	length++;
}
string AddressList::Delete(string name) {      //删除姓名为name的记录
	Human e;
	int i, j;
	for (i = 1; i < length; i++) {
		if (elem[i].name == name)
			e = elem[i];
		else
			return "记录不存在";
	}
	if (length == 0) cout << "无法删除，通讯录记录为空！" << endl;;
	if (e.id<1 || e.id>length + 1) cout << "删除位置异常！" << endl;
	for (j = i; j < length; j++) {
		elem[j] = elem[j + 1];
	}
	length--;
	return "'" + name + "'已被删除";
}
int AddressList::Locate(string name) {
	int i;
	for (i = 1; i < length; i++)
	{
		if (elem[i].name == name) return elem[i].id;
	}
	return 0;
}
void AddressList::GetElem(int n) {
	int i;
	for (i = 1; i < length; i++)
		if (elem[i].id == n)
			cout << elem[i].id << "," << elem[i].name << "," << elem[i].company_name << "," << elem[i].address << "," << elem[i].phone << "," << elem[i].group_name << endl;
		else cout << "找不到id为" << n << "的记录！" << endl;
}
void AddressList::ListDisp() {
	int i;
	cout << "ID	姓名	单位		地址		电话		" << endl;
	for (i = 1; i < length; i++) {
		cout << elem[i].id << "	" << elem[i].name << "	" << elem[i].company_name << "	" << elem[i].address << "	" << elem[i].phone << "	"<<endl;
	}
	cout << endl;
}
void AddressList::AddToGroup(string name) {
	int i, n;
	string groupname;
	cout << "你想把" << name << "加入哪个分组？"<<endl;
	for (i = 0; i < GetLen(); i++)
	{
		cout << i + 1 << "." << GetGroupName(i) << endl;
	}
	cin >> n;
	for (i = 1; i < length; i++) {
		if (elem[i].name == name) elem[i].group_name = GetGroupName(n - 1);
	}
}
void AddressList::GroupDisplay() {
	int i,j;
	for (i = 0; i < GetLen(); i++) {
		cout << GetGroupName(i) << endl;
		cout << "ID	姓名	单位	地址	电话" << endl;
		for (j=1;j<length;j++) {	
			if (elem[j].group_name == GetGroupName(i)) {
				cout << elem[j].id << "	" << elem[j].name << "	" << elem[j].company_name << "	" << elem[j].address << "	" << elem[j].phone << "	" << endl;
			}
		}
	}
}
void AddressList::Find() {

}