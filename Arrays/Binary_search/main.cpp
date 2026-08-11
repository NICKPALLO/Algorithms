#include <iostream>
#include <random>
#include <algorithm>

//Основная идея - при реализации бинарного поиска нужно следить за целочисленным переполнением и за тем чтобы он правильно изменял границы
//и не пропускал элементы. Это не сложно, но чтобы не тупить нужно просто выучить функцию binSearch ниже. 
// binSearch on answer - когда у нас есть набор ответов функций от какого-то числа до нуля и среди этих ответов нужно найти какрой-то конкретный
// Тут можно не простичтывать каждый ответ а использовать бинарный поиск по массиву ответов: берем середину - проверяем решение, если оно валидно 
// все кайф. Иначе в зависимости от ответа идум вверх или вниз. 



int binSearch(const std::vector<int>& v, int target)
{
    int l = 0;
    int r = static_cast<int>(v.size())-1;

    while(l<=r)
    {
        int k = (l+r)/2;
        if(v[k] == target)
        {
            return k;
        }
        else if(target < v[k])
        {
            r = k-1;
        }
        else
        {
            l = k+1;
        }
    }
    return -1;
}

int getMinK(const std::vector<int>& piles, int h)
{
    if(piles.empty())
    {
        return -1;
    }


    int max = *(std::max_element(piles.begin(),piles.end()));
    int l = 1;
    int r = max;
    
    auto getKvalid = [&piles, &h](int k){
        int current_h = 0;
        for(int j = 0; j<piles.size(); ++j)
        {
            current_h += std::ceil(piles[j]/static_cast<double>(k)); 
        }
        return current_h<=h;
    };

    int res_k = -1;
    while(l<=r)
    {
        int k = (l+r)/2;
        bool current_k_valid = getKvalid(k);
        if(current_k_valid)
        {
            res_k = k;
            r = k-1;
        }
        else
        {
            l = k+1;
        }
    }
    return res_k;
}


int main()
{
    // std::random_device rd;
    // std::mt19937 gen{rd()};    
    // std::uniform_int_distribution<unsigned> dist{0,10};


    std::vector<int> piles = {3, 6, 7, 11};
    int h =8;

    std::cout<<getMinK(piles,h);

    //int max = *(std::max_element(piles.begin(),piles.end()));

    // for(int i = max; i >=1; --i)
    // {
    //     std::cout<<"k = "<<i;
    //     int current_h = 0;
    //     for(int j = 0;j<piles.size();++j)
    //     {
    //         current_h += std::ceil(piles[j]/static_cast<double>(i)); 
    //     }
    //     std::cout<<" h = "<<current_h << (current_h<=h ? " true\n" : " false\n");
    // }


    return 0;
}