#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

template <typename T> class juzhen {
	
private:
	T* data;
	unsigned hang;
	unsigned lie;
	
public:
	juzhen() : hang(0),lie(0) { data = new T; }
	juzhen(unsigned h, unsigned l);
	juzhen(T* t, unsigned h, unsigned l);
	juzhen(const juzhen<T> & j);
	juzhen<T> & operator=(const juzhen<T> & j);
	juzhen<T> operator*(const juzhen<T> & j);
	template<typename TT>
	juzhen<TT> operator*(const TT & n);
	juzhen<T> operator+(const juzhen<T> & j);
	bool operator==(const juzhen<T> & j);
	
	~juzhen() { delete [] data; }
public:
	template<typename TT>
	friend ostream & operator<<(ostream & os, const juzhen<TT> & j);
};

template<typename T>
juzhen<T>::juzhen(unsigned h, unsigned l) : hang(h),lie(l){
	data = new T[hang*lie];
	for(T* p =data; p != &data[hang*lie]; p++) { *p = 0; }
}
template<typename T>
juzhen<T>::juzhen(T* t, unsigned h, unsigned l) : hang(h),lie(l){
	data = new T[hang*lie];
	for(T* p = data; p!= &data[hang*lie]; p++,t++) { *p = *t; }
}
template<typename T>
juzhen<T>::juzhen(const juzhen<T> & j) : hang(j.hang),lie(j.lie) { ////
	data = new T[hang*lie];
	for(T *p1 = data, *p2 = j.data; p1 != &data[hang*lie]; p1++,p2++) { *p1 = *p2; }
} 
template<typename T>
juzhen<T> & juzhen<T>::operator=(const juzhen<T> & j) {
	if(this = &j) { return *this; }
	delete [] data;
	hang = j.hang;
	lie = j.lie;
	data = new T[hang*lie];
	for(T *p1 = data, *p2 = j.data; p1 != &data[hang*lie]; p1++, p2++) { *p1 = *p2; }
	return *this;
}
template<typename T>
bool juzhen<T>::operator==(const juzhen<T> & j) {
	if(hang != j.hang || lie != j.lie)
		return 0;
	T *p1 = data;
	for(T *p2 = j.data; *p1 != *p2 && p1 != &data[hang*lie]; p1++, p2++);
	if(p1 == &data[hang*lie])
		return 1;
	return 0;
}
template<typename T>
juzhen<T> juzhen<T>::operator*(const juzhen<T> & j) {
	if(lie != j.hang) {
		cout << "juzhen<T>::" << this << "与" << &j << "无法相乘！\n";
		juzhen<T> re(hang, j.lie);
		return re;		////可以吗？
	}
	const unsigned rh = hang, rl = j.lie, h, l;
	T p[rh*rl];
	for(unsigned n = 0; n != rh*rl ;n++) {
		h = n/rl;
		l = n%rl;
		p[h*rl+l] = 0;
		for(int i = 0; i != lie; i++) {
			p[h*rl+l] += data[h*lie+i]*data[i*j.lie+l];
		}
	}
	juzhen<T> re(p, rh, rl);
	return re;
}
template<typename T>
template<typename TT>
juzhen<TT> juzhen<T>::operator*(const TT & n) {
	TT p[hang*lie];
	T *p2 = data;
	for(TT *p1 = p ; p1 != &p[hang*lie]; p1++, p2++) { *p1 = n * (*p2); }
	juzhen<TT> re(p, hang, lie);
	return re;
}
template<typename T>
juzhen<T> juzhen<T>::operator+(const juzhen<T> & j) {
	if(hang != j.hang || lie != j.lie) {
		cout << "juzhen<T>::" << this << "与" << &j << "无法相加！\n";
		juzhen<T> re(hang, lie);
		return re;
	}
	T p[hang*lie];
	T *p1 = data, p2 = j.data, p3 = p;
	for( ; p1 != &data[hang*lie]; p1++, p2++, p3++);
	juzhen<T> re(p, hang, lie);
	return re;
}
template<typename T>
ostream & operator<<(ostream & os, const juzhen<T> & j){
	unsigned k;
	for(unsigned i = 0; i != j.hang; i++) {
		if(i == 0)
			os << " ~" <<setw(j.lie*2 - 1) << ' ' << "~ \n";	
		for(k = 0; k != j.lie; k++){
			if(k == 0)
				os << "| ";
			os << j.data[i*j.lie+k] << ' ';
			if(k == j.lie - 1)
				os << "|\n";
		}
		if(i == j.hang - 1)
			os << " ~" << setw(j.lie*2 - 1) << ' ' << "~ \n";
	}
	return os;
}

int main(){
	int p[12] = {1, 3, 1, 4};
	juzhen<int> j(p, 2, 2);
	juzhen<double> re = j * 2.5;
	cout << re;
}
