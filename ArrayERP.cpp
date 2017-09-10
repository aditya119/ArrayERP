#include<iostream>
#include<cstring>
#include<cstdlib>
#include<fstream>
using namespace std;

struct address
{
	int h_no, pin;
	char street[20], city[20];
	void input();
};

typedef struct address address;

void address :: input()
{
	cout << "house number:\n";
	cin >> h_no;
	cout << "street:\n";
	cin >> street;
	cout << "city:\n";
	cin >> city;
	cout << "pin:\n";
	cin >> pin;
}

struct name
{
	char first[15], middle[15], last[15];
	void input();
	void output();
};

typedef struct name name;

void name :: input()
{
	cout << "first name:\n";
	cin >> first;
	cout << "middle name:(enter '0' if not applicable)\n";
	cin >> middle;
	cout << "last name:\n";
	cin >> last;
}

void name :: output()
{
	if(middle[0] == '0')
	{
		cout << first << " " << last << endl;
	}
	else
	{
		cout << first << " " << middle << " " << last << endl;
	}
}

class record
{
	public:
		int stu_id;
		name stu_name, f_name;
		char branch[3];
		address a;
		friend void view(record rec[], int n);
		friend int input(record rec[], int n);
		friend int remove(record rec[], int n);
		friend void update(record rec[], int n);
};

void view(record rec[], int n)
{
	system("clear");
	if(n == 0)	//check underflow
	{
		cout << "list empty\n";
		return;
	}
	for(int i = 0; i < n; i++)
	{
		cout << "student id: " << rec[i].stu_id << endl;
		cout << "name: ";
		rec[i].stu_name.output();
		cout << "father's name: ";
		rec[i].f_name.output();
		cout << "branch: " << rec[i].branch << endl;
		cout << "house number: " << rec[i].a.h_no << endl;
		cout << "street: " << rec[i].a.street << endl;
		cout << "city: " << rec[i].a.city << endl;
		cout << "pin: " << rec[i].a.pin << endl << endl;
	}
}

int input(record rec[], int n)
{
	system("clear");
	if(n == 99)	//check overflow
	{
		cout << "list full\ncannot enter any more records\n";
		return n;
	}
	cout << "student id:\n";
	cin >> rec[n].stu_id;
	cout << "name:\n";
	rec[n].stu_name.input();
	cout << "father's name:\n";
	rec[n].f_name.input();
	cout << "branch:\n";
	cin >> rec[n].branch;
	rec[n].a.input();
	n++;
	return n;
}

int remove(record rec[], int n, int x)
{
	if(n == 0)	//check underflow
	{
		cout << "list empty\n";
		return 0;
	}
	for(int i = 0; i < n; i++)
	{
		if(rec[i].stu_id == x)	//brings all records after 'x' a step above
		{
			for(int j = i; j < n-1; j++)
			{
				rec[j].stu_id = rec[j+1].stu_id;
				strcpy(rec[j].stu_name.first, rec[j+1].stu_name.first);
				strcpy(rec[j].stu_name.middle, rec[j+1].stu_name.middle);
				strcpy(rec[j].stu_name.last, rec[j+1].stu_name.last);
				strcpy(rec[j].f_name.first, rec[j+1].f_name.first);
				strcpy(rec[j].f_name.middle, rec[j+1].f_name.middle);
				strcpy(rec[j].f_name.last, rec[j+1].f_name.last);
				strcpy(rec[j].branch, rec[j+1].branch);
				rec[j].a.h_no = rec[j+1].a.h_no;
				strcpy(rec[j].a.street, rec[j+1].a.street);
				strcpy(rec[j].a.city, rec[j+1].a.city);
				rec[j].a.pin = rec[j+1].a.pin;
			}
			n--;
			return n;
		}
		if(rec[n-1].stu_id != x)
		{
			cout << "record doesn't exist\n";
			return n;
		}
	}
	return n;
}

void update(record rec[], int n)
{
	system("clear");
	if(n == 0)	//check underflow
	{
		cout << "list empty\n";
		return;
	}
	cout << "enter student id record you want to update:\n";
	int x;
	cin >> x;
	for(int i = 0; i < n; i++)
	{
		if(rec[i].stu_id == x)
		{
			cout << "what do you want to update?\n(N)ame\n(F)ather's name\n(B)ranch\n(A)ddress\n";
			char ch;
			cin >> ch;
			switch(ch)
			{
				case 'N': cout << "name:\n"; rec[i].stu_name.input(); break;
				case 'F': cout << "father's name:\n"; rec[i].f_name.input(); break;
				case 'B': cout << "branch:\n"; cin >> rec[i].branch; break;
				case 'A': rec[i].a.input(); break;
			}
			return;
		}
		if(rec[n-1].stu_id != x)
		{
			cout << "record doesn't exist\n";
			return;
		}
	}
}

int readFile(record rec[], int i)
{
	ifstream file("database", ios :: in | ios :: binary);
	while(file)
	{
		record *buffer;
		buffer = &rec[i];
		file.read((char*)buffer, sizeof(record));	//reads entire records one by one
		i++;
	}	//redundant node with stu_id also retrieved
	file.close();
	cout << i-1 << " records retrieved\n";
	return i;
}

void writeFile(record rec[], int n)
{
	ofstream file("database", ios :: trunc | ios :: binary);
	int i;
	for(i = 0; i < n; i++)
	{
		file.write ((char*)&rec[i], sizeof(record));	//writes entire records one by one
	}
	file.close();	
	cout << i << " records saved\n";
}

int main()
{
	record rec[100];
	char ch;
	int i = 0;
	system("clear");
	i = readFile(rec, i);
	i = remove(rec, i, 0);	//removes redundant node which has stu_id 0
	do
	{
		cout << "what do you want to do?\n(V)iew records\n(I)nput record\n(R)emove record\n(U)pdate record\n(C)ount records\n(E)xit\n";
		cin >> ch;
		switch(ch)
		{
			case 'V': view(rec, i); break;
			case 'I': i = input(rec, i); break;
			case 'R': cout << "enter student id record you want to delete:\n"; int x; cin >> x; i = remove(rec, i, x); cout << x << " deleted\n"; break;
			case 'U': update(rec, i); break;
			case 'C': cout << i << " records\n";
		}
	}
	while(ch != 'E');
	writeFile(rec, i);
	return 0;
}
