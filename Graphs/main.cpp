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


//У тебя n курсов, пронумерованных от 0 до n-1. 
//Дан список пар prerequisites, где prerequisites[i] = [a, b] означает 
//"чтобы взять курс a, нужно сначала закончить курс b". 
//Определи, можно ли закончить все курсы (то есть нет ли циклической зависимости).

bool findCircles(size_t n, const std::vector<std::pair<size_t,size_t>>& prerequisites)
{
    std::vector<size_t> graph(n,-1);
//[[1,0], [3,1], [0,3], [2,0]]
    for(const auto& pair : prerequisites)
    {
        graph[pair.second] = pair.first;
    }
    
    std::vector<bool> finit_find(n,false);

    auto CheckSequence = [&graph,&n,&finit_find](size_t current_index)
    {
        std::vector<bool> visited(n,false);
        visited[current_index] = true;

        current_index = graph[current_index];

        while(true)
        {
            if(visited[current_index])
            {
                return true; //Цикл есть
            }
            if(graph[current_index] == -1 || finit_find[current_index])
            {
                for(size_t i = 0; i < visited.size(); ++i)
                {
                    finit_find[i] = visited[i] || finit_find[i] ? true : false;
                }
                return false; //Цикла нету
            }
            visited[current_index] = true;
            current_index = graph[current_index];
        }

    };

    for(size_t i = 0; i < n; ++i)
    {
        if(finit_find[i])
        {
            continue;
        }
        else if(CheckSequence(i))
        {
            return true; //Цикл есть
        }
    }

    return false; //Цикла нету
}



int main()
{
    // std::random_device rd;
    // std::mt19937 gen{rd()};    
    // std::uniform_int_distribution<unsigned> dist{0,10};
    return 0;
}