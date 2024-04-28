#include <iostream>
#include <cstring>
using namespace std;
class String {
private:
	static int num;
	char *strr;
	int len;
	
public:
	String(const char *a) {
		len = strlen(a);
		strr = new char [len + 1];
		strcpy(strr, a);
	}
	
	String() {
		len = 0;
		strr = new char;
	}
	
	~String() {
		delete [] strr;
	}
	
	String(const String & s) {
		len = s.len;
		strr = new char [len + 1];
		strcpy(strr, s.strr);
	}
	
	String & operator=(const String & s) {
		if (this == &s)
			return *this;
		delete [] strr;
		len = s.len;
		strr = new char[len + 1];
		strcpy(strr, s.strr);
	}
	
	friend ostream & operator<<(ostream & os, const String & s) {
		os << s.strr;
		return os;
	}
	
	friend String & operator+(const char * a, String & s) {
		int len2 = strlen(a);
		int len3 = len2 + s.len;
		char * strrr = new char [len3 + 1];
		strcpy(strrr, a);
		strcat(strrr, s.strr);
		delete [] s.strr;
		s.strr = strrr;
		s.len = len3;
		return s;
	}
	
	String & operator+(const char * a) {
		int len2 = strlen(a);
		len += len2;
		char *strrr = new char[len + 1];
		strcpy(strrr, strr);
		strcat(strrr, a);
		delete [] strr;
		strr = strrr;
		return *this;
	}
	
	String & operator+(const String & s) {
		len += s.len;
		char *strrr = new char[len + 1];
		strcpy(strrr, strr);
		strcat(strrr, s.strr);
		delete [] strr;
		strr = strrr;
		return *this;
	}
	char & operator[](int i) {
		return strr[i];
	}
	
	friend istream & operator>>(istream & is, String & s) {
		int Len = 0;
		char *strrr;
		char tmp[21];
		char a, ch1;
		int i = 0;
		
		ch1 = cin.peek();
		while (ch1 == '\n' || ch1 == '\r' || ch1 == ' ' || ch1 == EOF) {
			if (ch1 == EOF) {
				cin.clear(); 
				cin.sync(); 
			} 
			else cin.get();
			ch1 = cin.peek();
		}
		
		while (true) {
			is.get(a);
			
			if (a == ' ' || a == '\n' || a == '\r' || a == EOF) {
				if (a == '\n')
					is.putback(a);
				if (Len == i) {
					strrr = new char[Len + 1];
					strcpy(strrr, tmp);
					break;
				} else {
					char *tmp2 = new char[Len + 1];
					strcpy(tmp2, strrr);
					strcat(tmp2, tmp);
					delete [] strrr;
					strrr = tmp2;
					break;
				}
			} else {
				tmp[i++] = a;
				tmp[i] = 0;
				Len++;
				if (i == 20) {
					if (Len == i) {
						strrr = new char[Len + 1];
						strcpy(strrr, tmp);
					} else {
						char *tmp2 = new char[Len + 1];
						strcpy(tmp2, strrr);
						strcat(tmp2, tmp);
						delete [] strrr;
						strrr = tmp2;
					}
					i = 0;
				}
			}
		}
		
		s.len = Len;
		s.strr[s.len+1] = 0;
		delete [] s.strr;
		s.strr = strrr;
		
		return is;
	}
	
	void getalot(istream & is) {
		int Len = 0;
		char *strrr;
		char tmp[21];
		char a;
		int i = 0;
		
		while (true) {
			if (!is.get(a)) {
				if (Len == i) {
					strrr = new char[Len + 1];
					strcpy(strrr, tmp);
					break;
				} else {
					char *tmp2 = new char[Len + 1];
					strcpy(tmp2, strrr);
					strcat(tmp2, tmp);
					delete [] strrr;
					strrr = tmp2;
					break;
				}
			} else {
				tmp[i++] = a;
				tmp[i] = 0;
				Len++;
				if (i == 20) {
					if (Len == i) {
						strrr = new char[Len + 1];
						strcpy(strrr, tmp);
					} else {
						char *tmp2 = new char[Len + 1];
						strcpy(tmp2, strrr);
						strcat(tmp2, tmp);
						delete [] strrr;
						strrr = tmp2;
					}
					
					i = 0;
				}
			}
			
			
		}
		
		len = Len;
		//cout<<"len = "<<len<<endl;
		delete [] strr;
		strr = strrr;
		
	}
	
	void stringlow() {
		for (int i = 0; i < len; i++) {
			if (isupper(strr[i]))
				strr[i] = tolower(strr[i]);
		}
	}
	
	void stringup() {
		for (int i = 0; i < len; i++) {
			if (islower(strr[i])) {
				//cout<< "  find  ";
				strr[i] = toupper(strr[i]);
			}
		}
	}
	
	int charcnt(char a) {
		int cnt = 0;
		
		for (int i = 0; i < len; i++) {
			if (strr[i] == a) {
				cnt++;
			}
		}
		return cnt;
	}
	
	virtual void show() {
		cout << *this;
	}
	
	char * point() {
		return strr;
	}
};
int String::num = 0;

class Story : public String {
private:
	String date;
	String week;
	String weather;
	
public:
	void setdata(istream & is) {
		is >> date >> week >> weather;
	}
	void setdata() {
		cout << "\ndata week weather：";
		cin >> date >> week >> weather;
	}
	void Write(istream & is) {
		cout << endl << this << "--Story write in: " << endl;
		String::getalot(is);
		cout << "\n________________________________________";
		setdata();
	}
	
	virtual void show() {
		cout << this << "Story show: \n";
		cout << *this << endl;
		cout << date << ' ' << week << ' ' << weather << endl;
	}
	virtual void show(ostream & os) {
		os << *this << endl;
		os << date << ' ' << week << ' ' << weather << endl;
	}
	Story(const Story & s): String(s) {
		date = s.date;
		week = s.week;
		weather = s.weather;
	}
	Story() {
	};
	const Story & operator=(const Story & s) {
		if(this == &s)
			return *this;
		String::operator=(s);
		date = s.date;
		week = week;
		weather = weather;
		return *this;
	}
};
