//SimpleArrays library.
union uarr {
int iarr[];
char carr[];
long larr[];
short sarr[];
long long llarr[];

};
class Array {
private:
union uarr uArr;
public:
int length;
};
