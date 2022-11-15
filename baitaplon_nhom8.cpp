#include <iostream>
#include <string>
using namespace std;

struct Student
{
	string sName;
	int day;
	int month;
	int year;
	string sAddress;
	string sSex;
	float fPhysic;
	float fMath;
	float fChemistry;
	float fAVR;
};

struct Node
{
	Student Data;
	Node* pNext;
};

struct List
{
	Node* pHead;
	Node* pTail;
};

Node* NewNode(Student);
void AddBack(List&, Node*);
void AddFront(List&, Node*);
void FreeNode(Node*);
void Remove(List&, string);
void Update(Node*);
bool ImportList(List&, int&);
void ImportStudent(Student&);
void ExportList(List);
void ExportStudent(Student);
bool IsEmptyList(List);
void SortIncList(List);
int ComPare(Student, Student);
Node* Search(List, string);
void NhapTen(string&);
bool CheckNgay(Student);
void Change(string&);
void Change(int&);
void Change(float&);
void Menu();

int main()
{
	int n;
	List l = { NULL, NULL };
	if (ImportList(l, n)) return 0;
		
		int x;
		do
		{
			cout << "\n\n";
			Menu();
			cout<<"\nNhap so ban muon chon:  ";
			cin>>x;
			cin.ignore();
		switch (x)
		{
			case 0:
			{
				cout << "Tam biet\n";
				break;
			}
			case 1:
				{
					Student t;
					Node* p;
						cout << "Nhap thong tin hoc sinh :\n";
						ImportStudent(t);
						p = NewNode(t);
						if (p == NULL)
						{
							cout << "Error";
							break;
						}
						else
						{
							AddBack(l, p);
						}
						break;
				}
			case 2:
				{
					Student t;
					Node* p;
					cout << "Nhap thong tin hoc sinh :\n";
					ImportStudent(t);
					p = NewNode(t);
					if (p == NULL)
					{
							cout << "Error";
							break;
					}
					else
					{
							AddFront(l, p);
					}
					break;	
				}
			case 3:
				{
					cout << "Ban muon xoa sinh vien nao \n";
					string name;
					NhapTen(name);
					Remove(l,name);
					break;	
				}
			case 4:	
				{
					cout << "Ban cap nhat sinh vien nao \n";
					string name;
					NhapTen(name);
					Node* alt = Search(l, name);
					Update(alt);
					break;	
				}
			case 5:
				{
					ExportList(l);
					break;
				}
			case 6:
				{
					if (IsEmptyList(l)==false)
						cout<<"Danh sach sinh vien khong rong";
					else
						cout<<"Danh sach sinh vien rong";
					break;
				}	
			case 7:
				{
					SortIncList(l);
					cout << "Da sap xong\n";
					break;
				}
			case 8:
				{
					string name;
					cout << "Chon 2 sinh vien can so sanh diem\n";
					cout << "Sinh vien thu nhat: \n";
					NhapTen(name);
					Node* STa = Search(l, name);
					if (STa == NULL)
					{
						cout << "Nhap sai\n";
						break;
					}
					cout << "Sinh vien thu hai: \n";
					NhapTen(name);
					Node* STb = Search(l, name);
					{
						cout << "Nhap sai\n";
						break;
					}
					int kq = ComPare(STa->Data, STb->Data);
					if (kq == 1)
						cout << STa->Data.sName << " Co diem cao hon \n";
					else if (kq == -1) cout << "Hai hoc sinh bang diem \n";
					else cout << STb->Data.sName << " Co diem cao hon \n";
					break;
				}
			case 9:
				{
					cout<<"Ban can tim ai\n ";
					string name;
					NhapTen (name);
					if (Search(l, name))
						cout << "Sinh vien co trong danh sach \n";
					else cout << "Khong co sinh vien: \n";
					break;
				}
				default:
				{
					cout << "Sai input, nhap lai\n";
					break;
				}
		}		
		} while (x != 0);
		
	
	return 0;	
}

Node* NewNode(Student a)
{
	Node* p = new Node;
	if (p == NULL) return NULL;
	p->Data = a;
	p->pNext = NULL;
	return p;
}
//them sinh vien vao cuoi danh sach
void AddBack(List& l, Node* p)
{
	if (IsEmptyList(l))
		l.pHead = l.pTail = p;
	else
	{
		l.pTail->pNext = p;
		l.pTail = p;
	}
}
//them sinh vien vao dau danh sach
void AddFront(List& l, Node* p)
{
	if (IsEmptyList(l))
		l.pHead = l.pTail = p;
	else
	{
		p->pNext = l.pHead;
		l.pHead = p;
	}
}
void FreeNode(Node* del)
{
	delete del;
}
void Remove(List& l, string name)
{
	Node* del;
	if (l.pHead->Data.sName == name)
	{
		del = l.pHead;
		l.pHead = l.pHead->pNext;
		FreeNode(del);
	}
	else
	{
		for (Node* i = l.pHead; i != NULL; i = i->pNext)
			if (i->pNext->Data.sName == name)
			{
				if (i->pNext == l.pTail)
				{
					del = l.pTail;
					i->pNext = NULL;
					FreeNode(del);
					return;
				}
				else
				{
					del = i->pNext;
					i->pNext = del->pNext;
					FreeNode(del);
					return;
				}
			}
	}
}
void Update(Node* alt)
{	
	cout << "Nhap -1 neu khong muon cap nhat\n";
	cout << "Nhap dung thong tin cap nhat de cap nhat\n";
	cout << "Cap nhat ten HS (ban dau:", alt->Data.sName, "):\n";
	Change(alt->Data.sName);
	do {
		cout << "Cap nhat ngay sinh HS (ban dau:", alt->Data.day, "):\n";
		Change(alt->Data.day);
		cout << "Cap nhat thang sinh HS (ban dau:", alt->Data.month, "):\n";
		Change(alt->Data.month);
		cout << "Cap nhat nam sinh HS (ban dau:", alt->Data.year, "):\n";
		Change(alt->Data.year);
	} while (!CheckNgay(alt->Data));
	cout << "Cap nhat dia chi HS (ban dau:", alt->Data.sAddress, "):\n";
	Change(alt->Data.sAddress);
	bool checkSex = true;
	do
	{
		checkSex = false;
		cout << "Cap nhat gioi tinh HS (ban dau:", alt->Data.sSex, "):\n";
		Change(alt->Data.sSex);
		if (alt->Data.sSex == "nu" or alt->Data.sSex == "nam" or alt->Data.sSex == "Nu" or alt->Data.sSex == "Nam")
		{
			checkSex = true;
		}

		else
		{
			cout << "Ban da nhap sai moi nhap lai gioi tinh!\n";
			checkSex = false;
		}
	} while (checkSex == false);

	cout << "Cap nhat diem toan HS (ban dau:", alt->Data.fMath, "):\n";
	Change(alt->Data.fMath);
	cout << "Cap nhat diem ly HS (ban dau:", alt->Data.fPhysic, "):\n";
	Change(alt->Data.fPhysic);
	cout << "Cap nhat diem hoa HS (ban dau:", alt->Data.fChemistry, "):\n";
	Change(alt->Data.fChemistry);
}
//kiem tra rong
bool IsEmptyList(List l)
{
	if (l.pHead == NULL) return 1;
	return 0;
}
//nhap thong tin danh sach
bool ImportList(List& l, int& n)
{
	cout << "Nhap so luong hoc sinh: ";
	cin >> n;
	cin.ignore();
	int i;
	Student t;
	Node* p;
	for (i = 1; i <= n; i++)
	{
		cout << "Nhap thong tin hoc sinh thu " << i << ":\n";
		ImportStudent(t);
		p = NewNode(t);
		if (p == NULL)
		{
			cout << "Error";
			return 1;
		}
		else
		{
			AddBack(l, p);
		}
	}
	return 0;
}
//nhap thong tin sinh vien
void ImportStudent(Student& a)
{
	cout << "Nhap ten hoc sinh: ";
	getline(cin, a.sName);
	bool check;
	do {
		cout << "Nhap ngay sinh hoc sinh: \n";
		cout<<"Nhap ngay: ";
		cin>>a.day;
		cout<<"Nhap thang: ";
		cin>>a.month;
		cout<<"Nhap nam: ";
		cin>>a.year;	
		check = CheckNgay(a);
		if (!check)
			cout << "Nhap lai\n";
	} while (!check);	
	cout << "Nhap dia chi hoc sinh: ";
	cin.ignore();
	getline(cin, a.sAddress);
	do
	{
		check=false;
		cout << "Nhap gioi tinh hoc sinh: ";
		cin >> a.sSex;
		if(a.sSex=="nu" or a.sSex=="nam" or a.sSex=="Nu" or a.sSex=="Nam")
		{
			check=true;
		}
			
		else
		{
			cout<<"Ban da nhap sai moi nhap lai gioi tinh!\n"; 
			check=false;
		}			
	} while(check==false);
	
	cout << "Nhap diem toan: ";
	cin >> a.fMath;
	cout << "Nhap diem ly: ";
	cin >> a.fPhysic;
	cout << "Nhap diem hoa: ";
	cin >> a.fChemistry;
	cin.ignore();
	a.fAVR = (a.fMath + a.fPhysic + a.fChemistry) / 3;
}
//xuat thong tin danh sach
void ExportList(List l)
{
	for (Node* p = l.pHead; p; p = p->pNext)
	{
		cout << "\n";
		ExportStudent(p->Data);
		cout << "\n";
	}
	cout << "\n";
}
//xuat thong tin sinh vien
void ExportStudent(Student a)
{
	cout << "Ten hoc sinh: " << a.sName << "\n";
	cout << "Ngay sinh: " << a.day<<"/"<<a.month<<"/"<<a.year << "\n";
	cout << "Dia chi: "  << a.sAddress << "\n";
	cout << "Gioi tinh: " << a.sSex << "\n";
	cout << "Diem toan: " << a.fMath << "\n";
	cout << "Diem ly: " << a.fPhysic << "\n";
	cout << "Diem hoa: " << a.fChemistry << "\n";
	cout << "Diem TB: " << a.fAVR << "\n";
}

void SortIncList(List l)//sort by avr (sap xep theo diem)
{
	Student temp;
	for (Node* p = l.pHead; p->pNext; p = p->pNext)//bubble sort(sap xep noi bot)
		for (Node* q = p->pNext; q; q = q->pNext)
			if ((bool)ComPare(p->Data, q->Data))
			{
				temp = p->Data;
				p->Data = q->Data;
				q->Data = temp;
			}
}

int ComPare(Student a, Student b)
{
	if (a.fAVR > b.fAVR) return 1;
	else if (a.fAVR == b.fAVR) return -1;
	return 0;
}
void NhapTen(string& a)
{ 
	cout << "Nhap ten: ";
	getline(cin, a);
}
bool CheckNgay(Student a)
{
	int day = a.day, month = a.month, year = a.year;
	switch (month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (day <= 0 || day > 31)
			return false;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		if (day <= 0 || day > 30)
			return false;
		break;
	case 2:
		if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
		{
			if (day <= 0 || day > 29)
				return false;
		}
		else if (day <= 0 || day > 28)
			return false;
		break;
	default:
		return false;
	}
	return true;
}
void Change(string& a)
{
	string s;
	getline(cin, s);
	if (s != "-1") a = s;
}
void Change(int& a)
{
	int s;
	cin >> s;
	cin.ignore();
	if (s != -1) a = s;
}
void Change(float& a)
{
	float s;
	cin >> s;
	cin.ignore();
	if (s != -1) a = s;
}
void Menu()
{
    cout << " *********************************************************\n";
	cout << "**   NHAP TRUONG HOP:                                    **\n";
	cout << "**   1: them sinh vien vao cuoi danh sach                **\n";
	cout << "**   2: them sinh vien vao dau danh sach                 **\n";
	cout << "**   3: Xoa                                              **\n";
	cout << "**   4: Cap nhat thong tin sinh vien                     **\n";
	cout << "**   5: Xuat danh sach sinh vien                         **\n";
	cout << "**   6: Kiem tra danh sach sinh vien co rong hay khong   **\n";
	cout << "**   7: Sap xep danh sach sinh vien                      **\n";
	cout << "**   8: So sanh diem 2 sinh vien                         **\n";
	cout << "**   9: Tim kiem sinh vien                               **\n";
	cout << "**   0: Thoat                                            **\n";
	cout << " *********************************************************\n";
}
Node* Search(List l, string name)//Search by name (tim kiem theo ten)
{
	for (Node* i = l.pHead; i != NULL; i = i->pNext)//Linear search (tim kiem tuan tu )
		if (i->Data.sName == name) return i;
	return NULL;
}
