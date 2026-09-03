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

int getNumberOfIslands(const std::vector<std::vector<char>>& grid)
{
    int numberOfIslands = 0;

    std::vector<std::vector<bool>> visited;
    visited.reserve(grid.size());
    for(size_t i = 0; i < grid.size(); ++i)
    {
        visited.push_back(std::vector<bool>(grid[i].size(),false));
    }


    auto visiteIsland = [&grid, &visited](size_t i, size_t j){
        std::stack<std::pair<size_t,size_t>> st;
        st.push({i,j});
        while(!st.empty())
        {
            auto pair = st.top();
            st.pop();

            std::pair<size_t,size_t> left(pair.first-1,pair.second);
            std::pair<size_t,size_t> right(pair.first+1,pair.second);
            std::pair<size_t,size_t> top(pair.first,pair.second-1);
            std::pair<size_t,size_t> bottom(pair.first,pair.second+1);

            if(pair.first != 0 && grid[left.first][left.second] == '1' && !visited[left.first][left.second])
            {
                visited[left.first][left.second] = true;
                st.push(left);
            }
            if(pair.first+1 != grid.size() && grid[right.first][right.second] == '1' && !visited[right.first][right.second])
            {
                visited[right.first][right.second] = true;
                st.push(right);
            }
            if(pair.second != 0 && grid[top.first][top.second] == '1' && !visited[top.first][top.second])
            {
                visited[top.first][top.second] = true;
                st.push(top);
            }
            if(pair.second+1 != grid[pair.first].size() && grid[bottom.first][bottom.second] == '1' && !visited[bottom.first][bottom.second])
            {
                visited[bottom.first][bottom.second] = true;
                st.push(bottom);
            }
        }
    };


    for(size_t i = 0; i < grid.size(); ++i)
    {
        for(size_t j = 0; j < grid[i].size(); ++j)
        {
            if(grid[i][j] == '1' && !visited[i][j])
            {
                ++numberOfIslands;
                visited[i][j] = true;
                visiteIsland(i,j);
            }
        }
    }
    return numberOfIslands;
}


int main()
{
    
    // std::random_device rd;
    // std::mt19937 gen{rd()};    
    // std::uniform_int_distribution<unsigned> dist{0,10};
    return 0;
}