#include <iostream>
#include <random>
#include <unordered_map>
#include <array>
#include <deque>
#include <unordered_set>
#include <set>
#include <algorithm>

//Дан массив строк strs.Сгруппировать анаграммы вместе
// (все строки, которые являются анаграммами друг друга, 
// должны попасть в одну группу).
// Порядок групп и порядок строк внутри группы не важен.
struct ArrayHasher {
    std::size_t operator()(const std::array<size_t,26>& arr) const noexcept {
        std::size_t h = 0;
        for(int i = 0;i<arr.size();++i)
        {
            h ^= std::hash<int64_t>()(arr[i]) + 0x9e3779b9 + (h << 6) + (h >> 2);
        }
        return h;
    }
};

std::array<size_t,26> createArray(const std::string& s)
{
    std::array<size_t,26> arr;
    arr.fill(0);
    for(size_t i =0;i<s.size();++i)
    {
        ++arr[static_cast<size_t>(s[i])-97];
    }
    return arr;//NRVO
}

std::vector<std::vector<size_t>> findAnnogramGroups(const std::vector<std::string>& strs)
{
    std::vector<std::vector<size_t>> results;

    std::unordered_map<std::array<size_t,26>,std::vector<size_t>,ArrayHasher> annograms;

    for(size_t i =0;i<strs.size();++i)
    {
        annograms[createArray(strs[i])].push_back(i);
    }

    for(const auto& group : annograms)
    {
        results.push_back(std::move(group.second));
    }
    return results;//NRVO
}

//Дан массив целых чисел nums (без дубликатов). 
// Найти длину самой длинной последовательности идущих подряд чисел 
// (не обязательно расположенных подряд в массиве — 
// важен только сам факт, что числа образуют непрерывный диапазон, 
// например [1,2,3,4]).
size_t getMaxSequence(const std::vector<int>& arr)
{
    std::vector<std::deque<int>> sequences;
    sequences.resize(arr.size()); // не изменяется размер чтобы не было инвалидации ссылок
    std::unordered_map<int,std::deque<int>*> sequences_ends;
    std::unordered_map<int,std::deque<int>*> sequences_begins;

    for(size_t i =0;i<arr.size();++i)
    {
        auto it_end = sequences_ends.find(arr[i]);
        auto it_begin = sequences_begins.find(arr[i]);
        if(it_end != sequences_ends.end() && it_begin != sequences_begins.end())
        {
            //объединяем две последовательности
            it_end->second->push_back(arr[i]);
            for(size_t j = 0;j<it_begin->second->size();++j)
            {
                it_end->second->push_back(it_begin->second->operator[](j));
            }
            it_begin->second->clear();
            // sequences_begins.erase(it_end->second->back());
            sequences_ends[it_end->second->back()+1] = it_end->second;
            sequences_ends.erase(arr[i]);
            sequences_begins.erase(arr[i]);
        }
        else if(it_end != sequences_ends.end())
        {
            it_end->second->push_back(arr[i]);
            sequences_ends[arr[i]+1] = it_end->second;
            sequences_ends.erase(arr[i]);
        }
        else if(it_begin != sequences_begins.end())
        {
            it_begin->second->push_front(arr[i]);
            sequences_begins[arr[i]-1] = it_begin->second;
            sequences_begins.erase(arr[i]);
        }
        else
        {
            sequences[i].push_back(arr[i]);
            sequences_begins[arr[i] - 1] = &sequences[i];
            sequences_ends[arr[i] + 1] = &sequences[i];
        }
    }
    size_t max_size = 0;
    for(const auto& s : sequences)
    {
        max_size = std::max(s.size(),max_size);
    }
    return max_size;
}

size_t getMaxSequence_2(const std::vector<int>& arr) //Правильное решение
{
    if(arr.empty())
    {
        return 0;
    }
    std::unordered_set<int> s;
    for(const auto i : arr)
    {
        s.insert(i);
    }

    size_t max_size = 1;
    for(auto i : s)
    {
        if(s.find(i-1) == s.end())
        {
            size_t size = 1;
            while(s.find(++i) != s.end())
            {
                ++size;
            }
            max_size = std::max(size,max_size);
        }
    }
    return max_size;
}

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

int main()
{
    // std::random_device rd;
    // std::mt19937 gen{rd()};    
    // std::uniform_int_distribution<unsigned> dist{0,10};
    std::vector<int> arr{1,-1,1};
    std::cout<<subArrayNum(arr,1);
    return 0;
}