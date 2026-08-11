#include <iostream>
#include <vector>
#include <random>
#include <unordered_map>

int getMaxSum(std::vector<int>& v, int k)
{
    if(v.size()<k)
    {
        throw std::runtime_error("vector sise is less than k");
    }

    int maxSum = v[0]+v[1]+v[2];
    int preSum = maxSum;

    for(size_t i = 0;i<v.size()-k;++i)
    {
        preSum = preSum + v[i+k] - v[i];
        maxSum = std::max(maxSum,preSum);
    }

    for(const auto i : v)
    {
        std::cout<<i<<" ";
    }
    return maxSum;
}

//Дана строка s.Найти длину самой длинной подстроки 
// без повторяющихся символов.
size_t getMaxLengthUnique(std::string& str)
{
    if(str.empty())
    {
        return 0;
    }

    size_t l = 0;
    size_t r = 0;
    size_t maxLength = 1;
    std::unordered_map<char,size_t> seenChars;
    
    seenChars[str[r]] = r;

    while(++r<str.size())
    {
        auto it = seenChars.find(str[r]);
        if(it == seenChars.end())
        {
            seenChars[str[r]] = r;
        }
        else
        {
            size_t leftBorder = it->second;
            while(l<leftBorder)
            {
                seenChars.erase(str[l++]);
            }
            ++l;
            it->second = r;
        }
        maxLength = std::max(maxLength,r-l+1);
    }
    return maxLength;
}

//Даны строка s и строка p.Найти все стартовые индексы подстрок в s, 
// которые являются анаграммами p(то есть содержат те же символы 
// в том же количестве, в любом порядке).
class Counter{
    public:
        Counter(const std::string& p)
        {
            for(const auto& letter : p)
            {
                ++counter_map[letter];
            }
        }
        void addLetter(char l)
        {
            auto it = counter_map.find(l);
            if(it != counter_map.end())
            {
                --(it->second);
                amountNulls = it->second == 0 ? amountNulls+1 : (it->second == -1 ? --amountNulls : amountNulls);
            }
        }
        void eraseLetter(char l)
        {
            auto it = counter_map.find(l);
            if(it != counter_map.end())
            {
                ++(it->second);
                amountNulls = it->second == 0 ? amountNulls+1 : (it->second == 1 ? --amountNulls : amountNulls);
            }
        }
        bool isAnnogram()
        {
            return amountNulls == counter_map.size();
        }
    private:
        std::unordered_map<char,int> counter_map;
        int amountNulls = 0;
};

std::vector<size_t> getAnnograms(const std::string& str, const std::string& p)
{
    if(str.empty() || p.empty() || p.size()>str.size())
    {
        throw std::runtime_error("Error of p or str size");
    }
    std::vector<size_t> results;
    Counter counter(p);

    for(int i = 0;i<p.size();++i)
    {
        counter.addLetter(str[i]);
    }
    if(counter.isAnnogram())
    {
        results.push_back(0);
    }
    for(size_t i = p.size();i<str.size();++i)
    {
        counter.addLetter(str[i]);
        counter.eraseLetter(str[i-p.size()]);
        if(counter.isAnnogram())
        {
            results.push_back(i-p.size()+1);
        }
    }
    return results; //NRVO
}


//Даны строки s и t.Найти минимальную по длине подстроку в s, 
// которая содержит все символы из t
// (с учётом повторений — если в t два 'a', 
// то и в подстроке должно быть минимум два 'a').
// Если такой подстроки нет — вернуть пустую строку.
class Counter_str{
    public:
        Counter_str(const std::string& p)
        {
            for(const auto& letter : p)
            {
                ++counter_map[letter];
            }
        }
        void addLetter(char l)
        {
            auto it = counter_map.find(l);
            if(it != counter_map.end())
            {
                --(it->second);
                amountNPos = it->second == 0 ? amountNPos+1 : amountNPos;
            }
        }
        void eraseLetter(char l)
        {
            auto it = counter_map.find(l);
            if(it != counter_map.end())
            {
                ++(it->second);
                amountNPos = it->second == 1 ? amountNPos-1 : amountNPos;
            }
        }
        bool isAnnogram()
        {
            return amountNPos == counter_map.size();
        }
    private:
        std::unordered_map<char,int> counter_map;
        int amountNPos = 0;
};


std::string getAnnogramStr_1(const std::string& str, const std::string& p)
{
    if(str.empty() || p.empty() || p.size()>str.size())
    {
        throw std::runtime_error("Error of p or str size");
    }
    size_t l = 0;
    size_t r = str.size()-1; 

    Counter_str counter(p);
    for(int i =0;i<str.size();++i)
    {
        counter.addLetter(str[i]);
    }
    
    if(!counter.isAnnogram())
    {
        return "";
    }

    while(counter.isAnnogram() && l<r)
    {
        counter.eraseLetter(str[l++]);
    }
    counter.addLetter(str[--l]);
    while(counter.isAnnogram() && l<r)
    {
        counter.eraseLetter(str[r--]);
    }
    counter.addLetter(str[++r]);

    return str.substr(l,r-l+1);
}

std::string getAnnogramStr_2(const std::string& str, const std::string& p)
{
    if(str.empty() || p.empty() || p.size()>str.size())
    {
        throw std::runtime_error("Error of p or str size");
    }

    size_t l_min_str = 0;
    size_t minDist = str.size()+1;

    size_t l = 0;
    size_t r = p.size()-1; 

    Counter_str counter(p);
    for(size_t i = l;i<=r;++i)
    {
        counter.addLetter(str[i]);
    }

    if(counter.isAnnogram())
    {
        return str.substr(l,r-l+1);
    }

    while(++r<str.size())
    {
        counter.addLetter(str[r]);
        if(counter.isAnnogram())
        {
            while(counter.isAnnogram() && l<r)
            {
                counter.eraseLetter(str[l++]);
            }
            counter.addLetter(str[--l]); 
            if(r-l<minDist)
            {
                l_min_str = l;
                minDist = r-l;
            }
        }
    }
    return minDist == str.size()+1 ? "" : str.substr(l_min_str,minDist+1);
}


int main()
{
    std::random_device rd;
    std::mt19937 gen{rd()};    
    std::uniform_int_distribution<unsigned> dist{0,10};

    std::string str("ADOBECODEBANC");
    std::string p("A");

    auto res = getAnnogramStr_1(str,p);

    std::cout<<res;


    return 0;
}