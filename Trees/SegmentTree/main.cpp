#include <iostream>
#include <vector>

class SegmentTree {
public:
    SegmentTree(std::vector<int>& arr) {
        n = arr.size();
        //size_t fullarrSize = 1u << static_cast<size_t>(std::ceil(std::log2(n)));
        tree.resize(4*n);
        //build(arr, 1, 0, fullarrSize - 1);
        build(arr, 0, 0, n - 1);
    }
    
    int query(int l, int r) {
        // ваш код
    }

private:
    std::vector<int> tree;
    int n;
    
    void build(std::vector<int>& arr, int node, int start, int end) {
        // if(start>=n)
        // {
        //     return;
        // }
        //else 
        if(start == end)
        {
            tree[node] = arr[start];             
        }
        else
        {
            int left = node*2;
            int right = node*2+1;

            int middle = (start + end)/2;
            build(arr, left, start, middle);
            build(arr, right, middle+1, end);
            tree[node] = tree[left] + tree[right];
        }
    }
};



int main()
{
    std::cout<<"allright\n";
    return 0;
}