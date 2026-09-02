#include <iostream>
#include <vector>

//Что важно понять - Прямая работа с деревьями обычно предполагает спуск по нему, пока не выполниться условие
//Тут же мы спускаясь по дереву меняем условие, в этом основная сложность.
//Дерево устроено просто, например 0,1,2,3,4,5,6,7,8

//           [0,8]
//     [0,4]       [5,8]
//  [0,2] [3,4] [5,6] [7,8]
//[0,1] 2  3 4   5 6   7 8
// 0 1

//Важная особенность - мы не достраиваем до полного бинарного как в книге!!!
// size_t fullarrSize = 1u << static_cast<size_t>(std::ceil(std::log2(n))); - оставил для примера.
//Тут из-за того что мы не достраиваем до полного бинарного мы всегда тащим с собой l и r


class SegmentTree {
public:
    SegmentTree(std::vector<int>& arr) {
        n = arr.size();
        //size_t fullarrSize = 1u << static_cast<size_t>(std::ceil(std::log2(n)));
        tree.resize(4*n);
        build(arr, 1, 0, n - 1);
    }
    
    int query(int l, int r) {
        return queryHelper(1, 0, n - 1, l, r);
    }

    void update(int idx, int val) {
        updateTreeNode(idx,val,1,0,n-1);
    }

private:
    std::vector<int> tree;
    int n;
    

    void updateTreeNode(int idx, int val, int node, int l, int r) {
        if(l == r && idx == l)
        {
            tree[node] = val;
        }
        else if(idx >= l && idx <= r)
        {
            int middle = (l+r)/2;
            int left = (node*2);
            int right = (node*2)+1;
            if(idx <= middle)
            {
                updateTreeNode(idx, val, left, l, middle);
            }
            else
            {
                updateTreeNode(idx, val, right, middle+1, r);
            }
            tree[node] = tree[left] + tree[right];
        }
    }
    
    
    //Поиск - основная операция, и самая сложная. 
    //Идея не сложная - Если интервал совпадает полностью возвращаем tree[node]
    //Иначе запускаем рекурсивно правую и левую сторону. Если мы вышли за интервал, то l>r и мы возвращаем 0.
    //Самое важная тонкость - std::min(mid,r) и std::max(mid+1,l) так как иначе мы можем искусственно увеличить интервал поиска
    //Т.е. передать в рекурсивную функцию r больше чем он был и тогда ответ на интервале 4,8 может дать 4,10 и так далее
    int queryHelper(int node, int start, int end, int l, int r) {
        if(l>r)
        {
            return 0;
        }
        else if(start == l && end == r)
        {
            return tree[node];
        }
        else
        {
            int mid = (start+end)/2;
            return queryHelper((node*2), start, mid, l, std::min(mid,r)) + 
                                queryHelper((node*2)+1, mid+1, end, std::max(mid+1,l), r);
        }
    }


    //Тут идея тоже не сложная - в конструкторе мы заполнили массив с запасом. Тут просто работа с индексами. 
    //Мы рекурсивно спускаемся по дереву, пока не уткнумся в start == end - лист дерева. Отсюда рекурсия пойдет наверх.
    //Далее просто берем tree[node] = tree[left] + tree[right]; где tree[left] и tree[right] - уже заполненные строчки в 
    //рекурсивной функции через tree[node] = arr[start];
    void build(std::vector<int>& arr, int node, int start, int end) {
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