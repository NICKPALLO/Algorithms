#include <iostream>
#include <random>
#include <vector>
#include <array>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <string>

constexpr bool createFile = false;


std::vector<std::array<int,3>> getTreeSum(const std::vector<int>& v)
{
    std::vector<std::array<int,3>> res;
    for(size_t i = 0;i<v.size();)
    {
        size_t L = i+1;
        size_t R = v.size()-1;

        int compearNum = v[i];
        if(compearNum>0) //Если число v[i] положительное
        {
            break;
        }

        while(L<R)
        {
            int left = v[L];
            int right = v[R];
            int sum = left + right;

            if(sum == -compearNum)
            {
                res.push_back(std::array<int,3>());
                res.back()[0] = compearNum;
                res.back()[1] = left;
                res.back()[2] = right;
                while(++L<R && v[L] == left){}
                while(L<--R && v[R] == right){}
            }
            else if(sum<-compearNum)
            {while(++L<R && v[L] == left){}}
            else
            {while(L<--R && v[R] == right){}}
        }
        while(++i<v.size() && v[i] == compearNum){}
    }
    return res;
}

unsigned getRaisedWater(const std::vector<unsigned>& heights)
{
    if(heights.empty())
    {
        return 0;
    }
    unsigned waterSum = 0;
    unsigned leftMax = 0;
    unsigned rightMax = 0;

    size_t l = 0;
    size_t r = heights.size()-1;

    while(l<r)
    {
        unsigned l_val = heights[l];
        unsigned r_val = heights[r];

        if(l_val<r_val)
        {
            if(l_val<leftMax)
            {
                waterSum+=leftMax-l_val;
            }
            else
            {
                leftMax = l_val;
            }
            ++l;
        }
        else
        {
            if(r_val<rightMax)
            {
                waterSum+=rightMax-r_val;
            }
            else
            {
                rightMax = r_val;
            }
            --r;  
        }
    }
    return waterSum;
}

//Дан массив положительных чисел nums и число target.
// Найти длину минимального подмассива(непрерывного), 
// сумма которого >= target.Если такого нет — вернуть 0.
size_t getMinDist(const std::vector<int>& v, const int target)
{
    if(v.empty())
    {
        return 0;
    }

    size_t l = 0;
    size_t r = 0;
    
    int sum = v[0];
    size_t res = std::numeric_limits<int>::max();
    if(sum>=target)
    {
        return 1;
    }

    while (r<v.size())
    {
        if(sum<target)
        {
            if(++r<v.size())
            {
                sum+=v[r];
            }
        }
        else
        {
            res = std::min(r-l+1,res);
            if(l == r)
            {
                return 1;
            }
            else
            {
                sum-=v[l++];
            }
        }
    }
    return res == std::numeric_limits<int>::max() ? 0 : res;
}

int main ()
{
    std::random_device rd;
    std::mt19937 gen{rd()};    
    std::uniform_int_distribution<unsigned> dist{0,9};

    std::vector<unsigned> v(10);
    for(size_t i = 0; i< v.size();++i)
    {
        v[i] = dist(gen);
    }
    

    auto maxNum = std::max_element(v.begin(),v.end());

    std::ofstream file("test.txt");
    if(createFile)
    {
        if(!file.is_open())
        {
            return 1;
        } 
    }
    else
    {
        if(file.is_open())
        {
            file.close();
        }
    }
    for(unsigned i = 0;i<*maxNum;++i)
    {
        for(size_t j =0; j<v.size(); ++j)
        {
            if(createFile)
            {
                file<<(v[j]>=(*maxNum)-i ? "O" : " ");
            }
            else
            {
                std::cout<< (v[j]>=(*maxNum)-i ? "O" : " ");
            }
        }
        if(createFile)
        {
            file<<"\n";
        }
        else
        {
            std::cout<<std::endl;
        }
    }
    for(size_t i = 0;i<v.size();++i)
    {
        if(createFile)
        {
            file<<v[i];
        }
        else
        {
            std::cout<<v[i];
        }
    }
    if(createFile)
    {
        file.close();
        #if defined(_WIN32)
        system("start test.txt");
        #elif defined(__APPLE__)
            system(("open " + "test.txt").c_str());
        #elif defined(__linux__)
            system(("xdg-open " + "test.txt").c_str());
        #endif
    }
    //std::sort(v.begin(),v.end());
    std::cout<<"\nRes = "<<getRaisedWater(v);
    return 0;
}