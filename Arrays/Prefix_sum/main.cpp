#include <iostream>
#include <random>
#include <unordered_map>
#include <array>
#include <deque>
#include <unordered_set>
#include <set>
#include <algorithm>

//Основная идея Prefix_sum - найти какую-то сумму в массиве за O(n), а если массив префиксов посчитан, то за O(1)
// k = prefix[r] - prefix[l-1], где k - сумма подмассива l-r, 
// если l - 0, то prefix[l-1] = 0 (мы считаем что предсумма равная 0 уже существует)
// Можно так-же искать сумму левого и правого подмассива - либо с двух сторон, либо с какого-то индекса через allSum 


//Дан массив целых чисел nums (могут быть отрицательные) и число k. 
//Найти количество непрерывных подмассивов, сумма которых равна k.
size_t subArrayNum(const std::vector<int>& arr, int target)
{
    if(arr.empty())
    {
        return 0;
    }

    std::unordered_map<int,size_t> prefix_m; //значение префикса - количество таких префиксов
    prefix_m[0] = 1;
    int currentPrefix = 0;
    size_t res = 0;

    for(size_t i = 0;i<arr.size();++i)
    {
        currentPrefix += arr[i];
        int requirePrefix = currentPrefix - target;
        res += prefix_m[requirePrefix];
        ++prefix_m[currentPrefix];
    }

    return res;
}

//дан массив nums и несколько запросов вида (l, r) — 
//для каждого нужно посчитать сумму элементов nums[l..r] (включительно). 
//Запросов может быть много (Q штук).

struct IntervalSum{
    IntervalSum(const std::vector<int>& v)
    {
        if(v.empty())
        {
            return;
        }
        prefix.resize(v.size());
        prefix[0] = v[0];
        for(int i = 1; i<v.size(); ++i)
        {
            prefix[i] = prefix[i-1] + v[i];
        }
    }
    int getIntervalSum(size_t l, size_t r) const
    {
        if(l>r || r >= prefix.size())
        {
            throw std::runtime_error("[IntervalSum]: incorrect input indexes (l,r)");
        }
        if(l == 0)
        {
            return prefix[r]; 
        }
        else
        {
            return prefix[r] - prefix[l-1];
        }
    }
    std::vector<int> prefix;
};

int64_t getPivot(const std::vector<int>& v)
{
    int sum = 0;
    for(int i : v)
    {
        sum += i;
    }
    int currentPrefix = 0;
    int prevPrefix = 0;
    for(int i =0;i<v.size();++i)
    {
        currentPrefix += v[i];
        if(prevPrefix == sum - currentPrefix)
        {
            return i;
        }
        prevPrefix = currentPrefix;
    }
    return -1;
}

//Дана 2D-матрица целых чисел matrix размером m x n. 
//Нужно обрабатывать несколько запросов вида (row1, col1, row2, col2) — для каждого 
//посчитать сумму элементов в прямоугольнике 
//от (row1, col1) (верхний левый угол) до (row2, col2) (нижний правый угол), включительно.

class Sum2D{
    public:
    Sum2D(int** arr, size_t m_, size_t n_) : m(m_+1), n(n_+1) 
    {
        prefix = new int*[m];
        for(size_t i = 0; i<m; ++i)
        {
           prefix[i] = new int[n];  
        }
        
        for(size_t i = 0; i < m; ++i)
        {
            prefix[i][0] = 0;
        }
        for(size_t j = 1; j < n; ++j)
        {
            prefix[0][j] = 0;
        }

        for(size_t i = 1; i < m; ++i)
        {
            for(size_t j = 1; j < n; ++j)
            {
                prefix[i][j] = arr[i-1][j-1] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1];
            }
        }
    }

    int sum(size_t row1, size_t col1, size_t row2, size_t col2)
    {
        ++row1; ++col1; ++row2; ++col2;

        if(row1>=m || row2 >=m || row1>row2)
        {
            throw std::runtime_error("[Sum2D]: error of row1 or row2 indexes");
        }
        if(col1>=n || col2 >=n || col1>col2)
        {
            throw std::runtime_error("[Sum2D]: error of col1 or col2 indexes");
        }
        return prefix[row2][col2] - prefix[row1-1][col2] - prefix[row2][col1 - 1] + prefix[row1 - 1][col1 - 1];
    }


    ~Sum2D() {
        for(size_t i = 0; i<m; ++i)
        {
           delete prefix[i];  
        }
        delete prefix;
    }
    private:
    int** prefix;
    const size_t m; //rows
    const size_t n; //colums
};


int main()
{
    // std::random_device rd;
    // std::mt19937 gen{rd()};    
    // std::uniform_int_distribution<unsigned> dist{0,10};
    std::vector<int> arr{1,-1,1};
    std::cout<<subArrayNum(arr,1);
    return 0;
}