#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<cctype>
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
	void DeleteGroup(string name);//删除分组；
	void SaveGroup();//保存分组；
	void ReadGroup();//读取分组；
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
	ofstream fout;
	fout.open("addressgrouplist.txt", ios_base::app);
	if (length >= listsize) cout << "注意！注意！分组过多！" << endl;
	Group g;
	cout << "请输入组名：";
	cin >> g.name;
	group[length] = g;
	length++;
	fout << g.name;
	fout.close();
}
string AddressGroup::GetGroupName(int n) {
	return group[n].name;
}
int AddressGroup::GetLen() {
	return length;
}
void AddressGroup::DeleteGroup(string name) {
	for (int i = 0; i < length; i++) {
		if (group[i].name == name) {
			for (int j = i; j < length-1; j++) {
				group[j].name = group[j + 1].name;
			}
		}
	}
	length--;
}
void AddressGroup::SaveGroup() {
	int i;
	ofstream fout;
	fout.open("addressgrouplist.txt");
	fout << "组名" << endl;
	for (i = 0; i < length; i++) {
		fout << group[i].name << endl;
	}
	fout.close();
}
void AddressGroup::ReadGroup() {
	int i = 0;
	char data[100];
	ifstream fin;
	fin.open("addressgrouplist.txt");
	fin.getline(data, 99);
	while (fin >> group[i].name) {
		cout << group[i].name<<endl;
		length = i+1;
		i++;
	}
	fin.close();
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
	void Delete(string name);//删除一条记录；
	void GetElem(int i);//获取第i个记录的值；
	int Locate(string name);//元素定位；
	void Clear();//清空记录；
	int Empty();//检测通讯录是否为空；
	int Full();//检测通讯录是否已满；
	int Length();//检测通讯录的长度；
	void ListDisp();//输出通讯录；
	void Save();//将通讯录存入文件,保存时按姓名有序保存；
	void Read();//从文件中读取通讯录；
	void Change(int,int);//修改记录的信息；
	void SortName();//按姓名排序；
	void SortPhone();//按号码排序；
	int FindName(string);//按姓名查找通讯录中的记录；
	int FindPhone(string);//按手机号码查找通讯录中的记录；
	void MoveName(string);//使查找和显示的记录位置按姓名前移或后移；
	void MovePhone(string);//使查找和显示的记录位置按手机号前移或后移
	void GroupDisplay();//分组显示；
	void AddToGroup(int);//加入组；
	void ChangeGroup(int);//改变分组;
	void MoveOutGroup(int);//移出分组；
	void Display(string name);//详细显示单个联系人的信息。
	bool Justice(string, string);//判断姓名，电话号码是否合法；
};
bool AddressList::Justice(string name, string phone) {
	if (name == "") {
		cout << "姓名不能为空！" << endl;
		return 0;
	}
	if (phone.length() > 11 || phone.length() <= 0) {
		cout << "手机号格式错误！" << endl;
		return 0;
	}
	for (char c : phone) {
		if (isalpha(c)) {
			cout << "手机号码格式错误！" << endl;
			return 0;
		}
	}
	return 1;
}
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
		do {
			cout << "请输入姓名，单位，住址，电话：";
			cin >> elem[i].name >> elem[i].company_name >> elem[i].address >> elem[i].phone;
			elem[i].id = i;
		} while (!Justice(elem[i].name, elem[i].phone));
	}
	length = n;
}
void AddressList::Insert() {
	ofstream fout;
	fout.open("addresslist.txt",ios_base::app);
	if (length > listsize-1) cout << "通讯录已满。" << endl;
	Human e;
	do{
	cout << "请输入姓名，单位，住址，电话：";
	cin >> e.name >> e.company_name >> e.address >> e.phone;
	} while (!Justice(e.name, e.phone));
	e.id = length+1;
	elem[length+1] = e;
	fout<< elem[length + 1].id << setw(21) << elem[length + 1].name << setw(21) << elem[length + 1].company_name << setw(21) << elem[length + 1].address << setw(21) << elem[length + 1].phone << endl;
	length++;
	fout.close();
}
void AddressList::Delete(string name) {      //删除姓名为name的记录
	Human e;
	int i, j;
	for (i = 1; i <= length; i++) {
		if (elem[i].name == name)
		{
			e = elem[i]; break;
		}
	}
	if (length == 0) cout << "无法删除，通讯录记录为空！" << endl;
	if (e.id<1 || e.id>length) cout << "删除位置异常！" << endl;
	for (j = i; j <= length; j++) {
		elem[j] = elem[j + 1];
	}
	length--;
	cout << name << "已被删除" << endl;;
}
int AddressList::Locate(string name) {
	int i;
	for (i = 1; i <= length; i++)
	{
		if (elem[i].name == name) return elem[i].id;
	}
	return 0;
}
void AddressList::GetElem(int n) {
	int i;
	for (i = 1; i <= length; i++)
		if (elem[i].id == n)
			cout << elem[i].id << "," << elem[i].name << "," << elem[i].company_name << "," << elem[i].address << "," << elem[i].phone << "," << elem[i].group_name << endl;
		else cout << "找不到id为" << n << "的记录！" << endl;
}
void AddressList::ListDisp() {
	int i;
	cout << "ID" << setw(20) << "姓名" << setw(20) << "单位" << setw(20) << "地址" << setw(20) << "电话" << endl;
	for (i = 1; i <= length; i++) {
		cout << elem[i].id << setw(21) << elem[i].name << setw(21) << elem[i].company_name << setw(21) << elem[i].address << setw(21) << elem[i].phone << endl;
	}
	cout << endl;
}
void AddressList::Change(int id,int i) {
	do{
		switch (i)
		{
		case 1:
			cout << "请输入姓名：";
			cin >> elem[id].name;

			break;
		case 2:
			cout << "请输入住址：";
			cin >> elem[id].address;
			break;
		case 3:
			cout << "请输入单位：";
			cin >> elem[id].company_name;
			break;
		case 4:
			cout << "请输入手机号：";
			cin >> elem[id].phone;
			break;
		default:
			break;
		}
	}while(!Justice(elem[id].name, elem[id].phone));
	cout << "修改完成。请保存修改。" << endl;
}
void AddressList::SortName() {
	int high, low, m;
	for (int i = 2; i <= length; i++) {
		elem[0] = elem[i];
		low = 1;
		high = i - 1;
		while (low <= high) {
			m = (low + high) / 2;
			if (elem[0].name < elem[m].name)
				high = m - 1;
			else
				low = m + 1;
		}
		for (int j = i - 1; j >= high + 1; --j)
			elem[j + 1] = elem[j];
		elem[high + 1] = elem[0];
	}
}
void AddressList::SortPhone() {
	int high, low, m;
	for (int i = 2; i <= length; i++) {
		elem[0] = elem[i];
		low = 1;
		high = i - 1;
		while (low <= high) {
			m = (low + high) / 2;
			if (elem[0].phone < elem[m].phone)
				high = m - 1;
			else
				low = m + 1;
		}
		for (int j = i - 1; j >= high + 1; --j)
			elem[j + 1] = elem[j];
		elem[high + 1] = elem[0];
	}
}
void AddressList::AddToGroup(int id) {
	int i, n;
	ReadGroup();
	string groupname;
	cout << "你想把" << elem[id].name << "加入哪个分组？"<<endl;
	for (i = 0; i < GetLen(); i++)
	{
		cout << i + 1 << "." << GetGroupName(i) << endl;
	}
	cin >> n;
	elem[id].group_name = GetGroupName(n - 1);
}
void AddressList::ChangeGroup(int id) {
	int n;
	ReadGroup();
	cout << "把" << elem[id].name << "加到分组：";
	for (int i = 0; i < GetLen(); i++)
	{
		cout << i + 1 << "." << GetGroupName(i) << endl;
	}
	cin >> n;
	elem[id].group_name = GetGroupName(n - 1);
}
void AddressList::MoveOutGroup(int id) {
	elem[id].group_name = "";
}
void AddressList::GroupDisplay() {
	int i,j;
	for (i = 0; i < GetLen(); i++) {
		cout << GetGroupName(i) << endl;
		cout << "ID" << setw(20) << "姓名" << setw(20) << "单位" << setw(20) << "地址" << setw(20) << "电话" << endl;
		for (j=1;j<=length;j++) {	
			if (elem[j].group_name == GetGroupName(i)) {
				cout << elem[j].id << setw(21) << elem[j].name << setw(21) << elem[j].company_name << setw(21) << elem[j].address << setw(21) << elem[j].phone << endl;
			}
		}
	}
}
int AddressList::FindName(string name) {
	SortName();
	int mid,flag;
	int low = 1, high = length;
	while (low <= high) {
		mid = (low + high) / 2;
		if (name < elem[mid].name) high = mid - 1;
		else if (name > elem[mid].name) low = mid + 1;
		else {
			flag = mid; break;
		}
	}
	return flag;
}
int AddressList::FindPhone(string phone) {
	SortPhone();
	int mid,flag;
	int low = 1, high = length;
	while (low <= high) {
		mid = (low + high) / 2;
		if (phone < elem[mid].phone) high = mid - 1;
		else if (phone > elem[mid].phone) low = mid + 1;
		else { flag = mid; break; }
	}
	return flag;
}
void AddressList::Save() {
	int i;
	SortName();
	ofstream fout;
	fout.open("addresslist.txt");
	fout << "ID" << setw(20) << "姓名" << setw(20) << "单位" << setw(20) << "地址" << setw(20) << "电话" << endl;
	for (i = 1; i <= length; i++) {
		fout << elem[i].id << setw(21) << elem[i].name << setw(21) << elem[i].company_name << setw(21) << elem[i].address << setw(21) << elem[i].phone <<endl;
	}
	fout.close();
}
void AddressList::Read() {
	int i=1;
	char data[100];
	ifstream fin;
	fin.open("addresslist.txt");
	fin.getline(data, 99);
	cout << data << endl;
	while (fin >> elem[i].id >> elem[i].name >> elem[i].company_name >> elem[i].address >> elem[i].phone) {
		cout << elem[i].id << setw(21) << elem[i].name << setw(21) << elem[i].company_name << setw(21) << elem[i].address << setw(21) << elem[i].phone << endl;
		length = i;
		i++;
	}
	fin.close();
}
void AddressList::MoveName(string name) {
	int flag;
	flag = FindName(name);
	Human e;
	e = elem[1];
	elem[1] = elem[flag];
	elem[flag] = e;
	ListDisp();
	e = elem[1];
	elem[1] = elem[flag];
	elem[flag] = e;
}
void AddressList::Display(string name) {
	for (int i = 1; i <= length; i++) {
		if (elem[i].name == name) {
			cout << "编号:" << elem[i].id << endl;
			cout << "姓名：" << elem[i].name << endl;
			cout << "住址:" << elem[i].address << endl;
			cout << "单位:" << elem[i].company_name << endl;
			cout << "手机号:" << elem[i].phone << endl;
			cout << "分组：";
			if (elem[i].group_name == "") cout << "无" << endl;
			else cout << elem[i].group_name << endl;
		}
	}
}
void AddressList::MovePhone(string phone) {
	int flag;
	flag = FindPhone(phone);
	Human e;
	e = elem[1];
	elem[1] = elem[flag];
	elem[flag] = e;
	ListDisp();
	e = elem[1];
	elem[1] = elem[flag];
	elem[flag] = e;
}