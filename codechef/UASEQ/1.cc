#include <iostream>
#include <algorithm>
#include <string.h>
#include <limits>
#include <stdio.h>
#include <vector>

#define gc getchar_unlocked
#define pc putchar_unlocked
int scan_d() {int ip=getchar_unlocked(),ret=0,flag=1;for(;ip<'0'||ip>'9';ip=getchar_unlocked())if(ip=='-'){flag=-1;ip=getchar_unlocked();break;}for(;ip>='0'&&ip<='9';ip=getchar_unlocked())ret=ret*10+ip-'0';return flag*ret;}
 
void print_d(int n) {if(n<0){n=-n;pc('-');}int i=10;char output_buffer[10];do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{pc ( output_buffer [ i ] ) ; } while ( ++i< 10 ) ; pc(' ');}

//max(10,n-2)
const static size_t kMaxMapSize = 10;
static struct d_map_ {
	int d_;
	int count_;
	bool operator>(const d_map_& o) const{
		return this->count_ > o.count_;
	}

} d_map [kMaxMapSize];

static inline void insert_into_dmap(int d) {
	if (d <= 0)
		return;
	size_t i;
	for(i = 0; i < kMaxMapSize; i++) {
		if (!d_map[i].d_ || d_map[i].d_ == d)
			break;
	}
	d_map[i].d_ = d;
	d_map[i].count_++;
}

static inline void remove_unwanted_d() {
	size_t i;
	for(i = 1; i < kMaxMapSize; i++) {
		if (d_map[i].count_ < d_map[i-1].count_)
			break;
	}
	d_map[i].d_ = 0;
}


#define getai(a0, d, i) (int)(a0 + (i * d))
#define geta0(ai, d, i) (int)(ai - (i * d))

static inline bool is_valid_progression(const int* arr, size_t n, unsigned k, int a0, size_t d) {
	unsigned accept_level = 0;
	size_t i;
	for (i = 0; i < n && accept_level <= k; i ++) {
		if (getai(a0, d, i) != arr[i])
			accept_level ++;
	}
	return (i == n && accept_level <= k);
}

static inline void dumpSeq(int a0, int d, size_t n) {
	for (size_t i = 0; i < n; i++)
		print_d(getai(a0, d, i));
}

int main(int argc, char** argv) {
	unsigned k;
	int a0;
	bool min_set = false;
	size_t d, n;
	struct { int a0_; size_t d_;} a0_d_cache[kMaxMapSize];
	n = scan_d();
	k = scan_d();

	int* arr = new int[n];

	arr[0] = scan_d();
	for (size_t i = 1; i < n; i++) {
		arr[i] = scan_d();
		insert_into_dmap(arr[i] - arr[i-1]);
	}
	std::sort(d_map, d_map + kMaxMapSize, std::greater<d_map_>());
	remove_unwanted_d();
	size_t cache_index = 0;
	for(size_t j = 1; j < n; j++) {
		for(size_t i = 0; i < kMaxMapSize && d_map[i].d_; i++) {
			int estimated_a0 = geta0(arr[j],d_map[i].d_,j);
			bool is_validated = false;
			for (size_t k = 0; k < cache_index && !is_validated; k++) 
				is_validated = (a0_d_cache[k].a0_ == estimated_a0 && a0_d_cache[k].d_ == d_map[i].d_);
			
			if (!is_validated && is_valid_progression(arr, n, k, estimated_a0, d_map[i].d_)) {
				if (!min_set) {
					min_set = true;
					a0 = estimated_a0; d = d = d_map[i].d_;
				} else if (estimated_a0 < a0 || (estimated_a0 == a0 && d_map[i].d_ < d)) {
					a0 = estimated_a0; d = d = d_map[i].d_;
				}
				a0_d_cache[cache_index].a0_ = a0;
				a0_d_cache[cache_index].d_ = d;
				cache_index ++;
			}
		}
	}
	
	dumpSeq(a0, d, n);
  return 0;
}
