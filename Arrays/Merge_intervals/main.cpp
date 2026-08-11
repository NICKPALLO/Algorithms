#include <iostream>
#include <random>
#include <unordered_map>
#include <array>
#include <deque>
#include <unordered_set>
#include <set>
#include <algorithm>

//Основная идея - интервалы нужно отсортировать по началу. Далее есть несколько подходов: итерируемся по массиву интервалов 
// и записываем левый и правый в отдельный res. Главное - когда мы отсортировали массив по началу интервалов мы можем ставить различные
// но четкие условия, часто смотреть только на конец или начало. 
// Интересный паттерн - разделять массив интервалов на три части - до чего-то не включительно, в каком-то интервале включительно
// после интервала не включительно.




//Дан массив интервалов intervals, где intervals[i] = [start_i, end_i]. 
//Объединить все пересекающиеся интервалы и вернуть массив непересекающихся интервалов, покрывающих все исходные.

std::vector<std::pair<int,int>> mergeIntervals(std::vector<std::pair<int,int>>& intervals)
{
    if(intervals.empty())
    {
        return {};
    }
    std::sort(intervals.begin(),intervals.end(),[](const std::pair<int,int>& a, const std::pair<int,int>& b){
        return a.first<b.first;
    });

    std::vector<std::pair<int,int>> res;

    size_t l = 0;
    int last = intervals[l].second;

    for(size_t r = 1; r<intervals.size(); ++r)
    {   
        if(intervals[r].first <= last)
        {
            last = std::max(intervals[r].second,last);
        }
        else
        {
            res.push_back({intervals[l].first,last});
            l = r;
            last = intervals[l].second;
        }
    }
    res.push_back({intervals[l].first,last});

    return res;//NRVO
}
//Даны два массива отсортированных по началу интервалов.
std::vector<std::pair<int,int>> mergeIntervals(const std::vector<std::pair<int,int>>& i_1, const std::vector<std::pair<int,int>>& i_2)
{
    std::vector<std::pair<int,int>> res;
    if(i_1.empty() && i_2.empty())
    {
        return res;
    }
    else if(i_1.empty())
    {
        return i_2;
    }
    else if(i_2.empty())
    {
        return i_1;
    }

    size_t it_1 = 0;
    size_t it_2 = 0;

    int l,r;

    auto update_lr = [&](){
        if(it_1 >= i_1.size() && it_2 >= i_2.size())
        {
            return;
        }
        else if(it_1 >= i_1.size())
        {
            l = i_2[it_2].first;
            r = i_2[it_2].second;
            ++it_2;
        }
        else if(it_2 >= i_2.size())
        {
            l = i_1[it_1].first;
            r = i_1[it_1].second;
            ++it_1;
        }
        else if(i_1[it_1].first < i_2[it_2].first)
        {
            l = i_1[it_1].first;
            r = i_1[it_1].second;
            ++it_1;
        }
        else
        {
            l = i_2[it_2].first;
            r = i_2[it_2].second;
            ++it_2;
        }
    };

    update_lr();

    bool notMerge_1;
    bool notMerge_2;

    while(it_1<i_1.size() || it_2<i_2.size())
    {
        notMerge_1 = true;
        notMerge_2 = true;
        
        if(it_1 < i_1.size())
        {
            if(i_1[it_1].first <= r)
            {
                r = std::max(r,i_1[it_1].second);
                ++it_1;
                notMerge_1 = false;
            }
        }
        if(it_2 < i_2.size())
        {
            if(i_2[it_2].first <= r)
            {
                r = std::max(r,i_2[it_2].second);
                ++it_2;
                notMerge_2 = false;
            }
        }
        if(notMerge_1 && notMerge_2)
        {
            res.push_back({l,r});
            update_lr();
        }
    }
    res.push_back({l,r});
    return res;
}


//Дан список уже непересекающихся интервалов, отсортированных по началу (intervals), и один новый интервал newInterval. 
//Нужно вставить newInterval в список, слив его с пересекающимися интервалами при необходимости, 
//сохранив общую отсортированность и непересекаемость.
void insertInverval(std::vector<std::pair<int,int>>& v, std::pair<int,int>& interval)
{
    for(size_t i =0; i<v.size(); ++i)
    {
        if(v[i].second >= interval.first)
        {
            if(v[i].first > interval.second)
            {
                //Интервалы не пересекаются
                v.insert(v.begin()+i,interval);
                break;
            }

            //интервалы пересекаются
            v[i].first = std::min(v[i].first,interval.first);
            size_t k = i;
            while(k<v.size() && interval.second >= v[k].second)
            {
                ++k;
            }
            if(k<v.size() && interval.second >= v[k].first)
            {
                //Удаляем от i+1 до k
                v[i].second = v[k].second;
                ++k;
            }
            else
            {
                //Удаляем от i+1 до k-1 включительно
                v[i].second = interval.second;
            }
            if(i+1<=k)
            {
                v.erase(v.begin()+i+1,v.begin()+k);
            }
            break;
        }
        if(i == v.size()-1)
        {
            v.push_back(interval);
        }
    }
}

// ГОРАЗДО более простое решение. Это решение является стандартом.
std::vector<std::pair<int,int>> insertInterval(std::vector<std::pair<int,int>>& v, std::pair<int,int> interval)
{
    std::vector<std::pair<int,int>> res;
    size_t i = 0;

    // Зона 1: интервалы целиком до newInterval
    while (i < v.size() && v[i].second < interval.first)
        res.push_back(v[i++]);

    // Зона 2: все, что пересекается — сливаем в один
    while (i < v.size() && v[i].first <= interval.second)
    {
        interval.first = std::min(interval.first, v[i].first);
        interval.second = std::max(interval.second, v[i].second);
        ++i;
    }
    res.push_back(interval);

    // Зона 3: интервалы целиком после
    while (i < v.size())
        res.push_back(v[i++]);

    return res;
} 

//Правильное решение задачи на сдлияние двух интеравалов
std::vector<std::pair<int,int>> mergeTwoSortedLists(
    const std::vector<std::pair<int,int>>& a,
    const std::vector<std::pair<int,int>>& b)
{
    std::vector<std::pair<int,int>> res;
    size_t i = 0, j = 0;
    bool active = false;
    int l = 0, r = 0;

    while (i < a.size() || j < b.size())
    {
        std::pair<int,int> cur = (j >= b.size() || (i < a.size() && a[i].first <= b[j].first))
                                  ? a[i++] : b[j++];

        if (!active)                    { l = cur.first; r = cur.second; active = true; }
        else if (cur.first <= r)        { r = std::max(r, cur.second); }
        else                             { res.push_back({l, r}); l = cur.first; r = cur.second; }
    }
    if (active) res.push_back({l, r});
    return res;
}

int main()
{
    std::random_device rd;
    std::mt19937 gen{rd()};    
    std::uniform_int_distribution<unsigned> dist{1,10};

    std::vector<std::pair<int,int>> intervals;

    for(int i = 0;i<10;++i)
    {   
        int val = dist(gen);
        intervals.push_back({val,val+dist(gen)});
    }

    for(const auto& interval : intervals)
    {
        std::cout<<interval.first<<" "<<interval.second<<std::endl;
    }




    return 0;
}