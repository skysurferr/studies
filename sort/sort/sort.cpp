#include <vector>
#include <vector>
#include <string>
using namespace std;

static void print_array(const string& title, vector<int>& arr)
{
	printf("%s ", title.c_str());
	for(auto& i : arr)
	{
		printf("%d ", i);
	}
	printf("\n");
}

static void merge_blocks(const size_t left_limit, const size_t right_limit, int*& buf, int*& lptr, int*& rptr)
{
	size_t k = 0;
	size_t j = 0;
	while((k < left_limit) && (j < right_limit))
	{
		if(*lptr <= *rptr)
		{
			*buf = *lptr++;
			++k;
		}
		else
		{
			*buf = *rptr++;
			++j;
		}
		++buf;
	}
	while(k < left_limit)
	{
		*buf = *lptr++;
		++k;
		++buf;
	}
	while (j < right_limit)
	{
		*buf = *rptr++;
		++j;
		++buf;
	}
}

static void merge(vector<int>& input, const size_t merge_size, int* buf)
{
	int* lptr = &input[0];
	int* rptr = lptr + merge_size;
	int* buf_start = buf;

	const size_t block_num = (input.size() / merge_size) / 2;        // number of block pairs of equal size
	const size_t rest = input.size() - block_num * 2 * merge_size;   // possible values [0 - merge_size * 2]

	for(size_t i = 0; i < block_num; ++i)
	{
		merge_blocks(merge_size, merge_size, buf, lptr, rptr);
		lptr += merge_size;
		rptr += merge_size;
	}

	if(rest)
	{
		if(rest <= merge_size)
		{
			memcpy(buf, lptr, rest * sizeof(int));
		}
		else
		{
			merge_blocks(merge_size, rest % merge_size, buf, lptr, rptr);
		}
	}

	memcpy(&input[0], buf_start, input.size() * sizeof(int));
}

void merge_sort(vector<int>& in)
{
	size_t cur_merge_size = 1;
	const size_t input_size = in.size();
	if(input_size)
	{
		const auto buf = new int[input_size];
		while(cur_merge_size < input_size)
		{
			merge(in, cur_merge_size, buf);
			cur_merge_size <<= 1;
		}

		delete[] buf;
	}
}

int main()
{
	vector<int> data = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	print_array("input:", data);
	merge_sort(data);
	print_array("sorted:", data);

}