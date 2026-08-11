#include <iostream>
#include <random>
#include <unordered_map>
#include <array>
#include <deque>
#include <unordered_set>
#include <set>
#include <algorithm>

//Основная идея и смысл - используется когда нужно найти максимальную/минимальную сумму на массиве.
//мы идем по массиву и считаем сумму - если она отрицательна, 
//то дальше смысла нету продолжать считать - прошлая сумма уже бессмысленна.


//Дан массив целых чисел nums 
//(могут быть отрицательные, может быть весь массив из отрицательных чисел). 
//Найти максимальную сумму непрерывного подмассива (подмассив должен содержать хотя бы один элемент).

int getMaxSum(const std::vector<int>& v)
{
    if(v.empty())
    {
        return 0;
    }
    int maxSum = std::numeric_limits<int>::min(); //если !v.empty() то maxSum не будет равен std::numeric_limits<int>::min()
    int sum = 0;
    for(int i =0;i<v.size();++i)
    {
        if(sum<0)
        {
            sum = v[i];
        }
        else
        {
            sum += v[i];
        }
        maxSum = std::max(maxSum,sum);
    }
    return maxSum;
}

//Тоже самое, но нужно вернуть индексы

std::pair<size_t,size_t> getMaxSumInterval(const std::vector<int>& v)
{
    if(v.empty())
    {
        return {0,0};
    }

    size_t l = 0;

    size_t max_l = 0;
    size_t max_r = 0;


    int maxSum = std::numeric_limits<int>::min(); //если !v.empty() то maxSum не будет равен std::numeric_limits<int>::min()
    int sum = 0;

    for(size_t r = 0; r < v.size(); ++r)
    {
        if(sum<0)
        {
            l = r;
            sum = v[r];
        }
        else
        {
            sum += v[r];
        }
        if(maxSum<sum)
        {
            maxSum = sum;
            max_l = l;
            max_r = r;
        }
    }
    return {max_l,max_r};
}


int main()
{
    // std::random_device rd;
    // std::mt19937 gen{rd()};    
    // std::uniform_int_distribution<unsigned> dist{0,10};

    std::cout << getMaxSum({-5,4});

    return 0;
}