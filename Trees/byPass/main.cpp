#include <iostream>
#include <random>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

//Иди максимально влево, и клади все в стек
//Когда достаешь из стека посторяй
std::vector<int> inorderTraversal(TreeNode* root) {    
    std::vector<int> res;
    if(!root)
    {
        return res;
    }

    std::stack<TreeNode*> st;
    auto goToLeft = [&st](TreeNode* node){
        while(node->left)
        {
            st.push(node);
            node = node->left;
        }
        return node;
    };

    TreeNode* currentNode = goToLeft(root);

    while(true)
    {
        res.push_back(currentNode->val);
        if(currentNode->right)
        {
            currentNode = goToLeft(currentNode->right);
        }        
        else
        {
            if(st.empty())
            {
                break;
            }
            else
            {    
                currentNode = st.top();
                st.pop();
            }            
        }
    }
    return res;
}

//корень → лево → право.
std::vector<int> PreorderTraversal(TreeNode* root)
{
    std::vector<int> res;
    if(!root)
    {
        return res;
    }

    std::stack<TreeNode*> st;
    st.push(root);
    while(!st.empty())
    {
        TreeNode* currentNode = st.top();
        st.pop();
        res.push_back(currentNode->val);
        
        if(currentNode->right) { st.push(currentNode->right); }
        if(currentNode->left) { st.push(currentNode->left); }
    }

    return res;
}

//Postorder — порядок лево → право → корень
std::vector<int> postorderTraversal(TreeNode* root)
{

    std::vector<int> res;
    if(!root)
    {
        return res;
    }

    std::stack<TreeNode*> st;
    st.push(root);

    while(!st.empty())
    {
        TreeNode* currentNode = st.top();
        st.pop();
        res.push_back(currentNode->val);
                
        if(currentNode->left) { st.push(currentNode->left); }
        if(currentNode->right) { st.push(currentNode->right); }
    }


    std::reverse(res.begin(),res.end());

    return res;
}


//Вернуть vector<vector<int>>, где каждый вложенный vector — 
//это значения узлов одного уровня дерева, сверху вниз
std::vector<std::vector<int>> levelOrder(TreeNode* root) {
    std::vector<std::vector<int>> res;

    if(!root)
    {
        return res;
    }

    std::queue<TreeNode*> q;
    q.push(root);
    
    size_t size = 0;
    size_t next_size = 1;


    res.push_back(std::vector<int>());

    while(!q.empty())
    {
        if(size == next_size)
        {
            res.push_back(std::vector<int>());
            next_size = q.size();
            size = 0;  
        }

        TreeNode* currentNode = q.front();
        q.pop();
        
        res.back().push_back(currentNode->val);
        ++size;

        if(currentNode->left)
        {
            q.push(currentNode->left);
        }
        if(currentNode->right)
        {
            q.push(currentNode->right);
        }
    }
    return res;
}


// вернуть высоту дерева (количество узлов на самом длинном пути от корня до листа)
// Идиоматичная рекурсивная версия:
int maxDepth(TreeNode* root) {
    if (!root) return 0;
    return 1 + std::max(maxDepth(root->left), maxDepth(root->right));
}

// Версия без рекурсии:
int maxDepthNoRecursion(TreeNode* root) {
    if(!root)
    {
        return 0;
    }

    std::queue<TreeNode*> q;
    q.push(root);
    int height = 1;

    int size = 0;
    int next_size = q.size(); //1

    while(!q.empty())
    {
        if(size == next_size)
        {
            ++height;
            next_size = q.size();
            size = 0;
        }

        TreeNode* currentNode = q.front();
        q.pop();
        ++size;

        if(currentNode->left) {q.push(currentNode->left);}
        if(currentNode->right) {q.push(currentNode->right);}
    }
    return height;
}



// Дерево называется сбалансированным, если для КАЖДОГО узла 
// разница высот его левого и правого поддеревьев не превышает 1
//Версия с рекурсией и сложностью O(n^2)
bool isBalanced(TreeNode* root) {
    if(!root)
    {
        return true;
    }
    if(std::abs(maxDepthNoRecursion(root->left) - maxDepthNoRecursion(root->right)) <= 1)
    {
        return isBalanced(root->left) && isBalanced(root->right);
    }
    else
    {
        return false;
    }
}

//Версия с рекурсией и сложностью O(N) (Мы объединили две реккурсии)
int get_height(TreeNode* root)
{
    if(!root)
    {
        return 0;
    }

    int res_1 = get_height(root->left);
    if(res_1 == -1)
    {
        return -1;
    }
    int res_2 = get_height(root->right);
    if(res_2 == -1 || std::abs(res_1 - res_2) > 1)
    {
        return -1;
    }
    return 1 + std::max(res_1, res_2);
}


bool isBalanced_2(TreeNode* root)
{
    if(!root)
    {
        return true;
    }
    return get_height(root) != -1;
}

//Версия без рекурсии
bool isBalancedNoRecursion(TreeNode* root)
{
    if(!root)
    {
        return true;
    }
    std::unordered_map<TreeNode*,int> m;
    std::stack<TreeNode*> st;

    st.push(root);
    while(!st.empty())
    {
        TreeNode* currentNode = st.top();
        //st.pop();

        bool leftIsCalc = true;
        bool rightIsCalc = true;
        std::unordered_map<TreeNode*,int>::iterator it_left;
        std::unordered_map<TreeNode*,int>::iterator it_right;
        if(currentNode->left)
        {
            it_left = m.find(currentNode->left);
            if(it_left == m.end())
            {
                leftIsCalc = false; //Значит нода существует, но значение не посчитано
            }    
        }
        
        if(currentNode->right)
        {
            it_right = m.find(currentNode->right); 
            if(it_right == m.end())
            {
                rightIsCalc = false; //Значит нода существует, но значение не посчитано
            }    
        }


        if(leftIsCalc && rightIsCalc)
        {
            int leftHeight = currentNode->left ? it_left->second : -1;
            int rightHeight = currentNode->right ? it_right->second : -1;
            int delta = std::abs(leftHeight - rightHeight);
            if(delta > 1)
            {
                return false;
            }
            else
            {
                m[currentNode] = std::max(leftHeight,rightHeight) + 1;     
                st.pop();
            }
        }
        else
        {   
            if(currentNode->right) {st.push(currentNode->right);}
            if(currentNode->left) {st.push(currentNode->left);}
        }
    }
    return true;
}

int main()
{
    // std::random_device rd;
    // std::mt19937 gen{rd()};    
    // std::uniform_int_distribution<unsigned> dist{0,10};


    return 0;
}