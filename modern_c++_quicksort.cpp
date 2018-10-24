#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename FwdIt>
void quicksort(FwdIt begin, FwdIt end)
{
	auto n = std::distance(begin, end);

	if (n <= 0)
	{
		return;
	}

	FwdIt pivot = std::next(begin, n/2);
	nth_element(begin, pivot, end);
	quicksort(begin, std::prev(pivot));
	quicksort(std::next(pivot), end);
}


int main()
{
	std::vector<int> v = {5,8,3,1,4,7,9};
	quicksort(v.begin(), v.end());
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));

	char ch;
	cin >> ch;

	return 0;
}