#include <iostream>
#include <random>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <string>

//Дана 2D-сетка из '1' (земля) и '0' (вода). Остров — это группа земель, соединённых по горизонтали или вертикали (диагонали не считаются). Найди количество островов.

/*
Пример:
grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Ответ: 3*/


struct PairKeyHasher {
    std::size_t operator()(const std::pair<size_t,size_t>& p) const noexcept {
        return (std::hash<size_t>()(p.first) << 1) ^ std::hash<size_t>()(p.second);
    }
};

int getNumberOfIslands(const std::vector<std::vector<char>>& grid)
{
    int numberOfIslands = 0;
    std::unordered_set<std::pair<size_t,size_t>,PairKeyHasher> visited;

    auto visiteIsland = [&grid, &visited](size_t i, size_t j){
        std::stack<std::pair<size_t,size_t>> st;
        st.push({i,j});
        while(!st.empty())
        {
            auto pair = st.top();
            st.pop();
            visited.insert(pair);

            std::pair<size_t,size_t> left(pair.first-1,pair.second);
            std::pair<size_t,size_t> right(pair.first+1,pair.second);
            std::pair<size_t,size_t> top(pair.first,pair.second-1);
            std::pair<size_t,size_t> bottom(pair.first,pair.second+1);


            if(pair.first != 0 && grid[pair.first-1][pair.second] == '1' && visited.find({pair.first-1,pair.second}) == visited.end())
            {
                //Проверяем точку слева
                st.push({pair.first-1,pair.second});
            }
            if(pair.first+1 != grid.size() && grid[pair.first+1][pair.second] == '1' && visited.find({pair.first+1,pair.second}) == visited.end())
            {
                //Проверяем точку справа
                st.push({pair.first+1,pair.second});
            }
            if(pair.second != 0 && grid[pair.first][pair.second-1] == '1' && visited.find({pair.first,pair.second-1}) == visited.end())
            {
                //Проверяем точку сверху
                st.push({pair.first,pair.second-1});
            }
            if(pair.second+1 != grid[pair.first].size() && grid[pair.first][pair.second+1] == '1' && visited.find({pair.first,pair.second+1}) == visited.end())
            {
                //Проверяем точку снизу
                st.push({pair.first,pair.second+1});
            }

        }

    };


    for(size_t i = 0; i < grid.size(); ++i)
    {
        for(size_t j = 0; j < grid[i].size(); ++j)
        {
            if(grid[i][j] == '1' && visited.find({i,j}) == visited.end())
            {
                ++numberOfIslands;
                visiteIsland(i,j);
            }
        }
    }
    return 0;
}


int main()
{
    
    // std::random_device rd;
    // std::mt19937 gen{rd()};    
    // std::uniform_int_distribution<unsigned> dist{0,10};
    return 0;
}