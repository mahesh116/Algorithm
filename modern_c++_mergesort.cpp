#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename FwdIt>
void mergesort(FwdIt begin, FwdIt end)
{
	auto n = std::distance(begin, end);

	if (n <= 1)
	{
		return;
	}

	FwdIt middle = std::next(begin, n / 2);
	mergesort(begin, middle);
	mergesort(middle, end);
	inplace_merge(begin, middle, end);
}


int main()
{
	std::vector<int> v = { 5,8,3,1,4,7,9 };
	mergesort(v.begin(), v.end());
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));

	char ch;
	cin >> ch;

	return 0;
}