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

//Самые основы - обходы. Все нужно знать наизусть.

//Иди максимально влево, и клади все в стек
//Когда достаешь из стека посторяй
//Inroder - выучить (лево - корень - право)
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
//Выучить
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
//Можно выучить но важнее следующий
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

//Идиоматичный (Без разворота)
//Выучить
std::vector<int> postorderTraversal_2(TreeNode* root)
{
    std::stack<TreeNode*> st;
    TreeNode* cur = root;
    TreeNode* lastVisited = nullptr;

    while (cur || !st.empty()) {
        // 1. Спускаемся максимально влево, складывая по пути в стек
        while (cur) {
            st.push(cur);
            cur = cur->left;
        }
        
        TreeNode* peekNode = st.top();
        
        // 2. Если есть правый ребёнок и мы его ЕЩЁ не обработали — идём туда
        if (peekNode->right && lastVisited != peekNode->right) {
            cur = peekNode->right;
        } else {
            // 3. Иначе — оба ребёнка обработаны (или их не было), можно обработать сам узел
            // ... обработка peekNode ...
            lastVisited = peekNode;
            st.pop();
        }
    }
}

//Вернуть vector<vector<int>>, где каждый вложенный vector — 
//это значения узлов одного уровня дерева, сверху вниз
//То как вывести по уровням - выучить
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




//Основы Bottom-Up задачи - тут дети передают какую-то информацию родителям

// вернуть высоту дерева (количество узлов на самом длинном пути от корня до листа)
// Идиоматичная рекурсивная версия:
//Выучить
int maxDepth(TreeNode* root) {
    if (!root) return 0;
    return 1 + std::max(maxDepth(root->left), maxDepth(root->right));
}

// Версия без рекурсии:
//Обход в глубину - выучить
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
//Не учим
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
//Выучить!!!
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

//Версия без рекурсии но по памяти O(N)
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

//Версия без рекурсии но по памяти O(H) O(logN)
bool isBalancedNoRecursion(TreeNode* root)
{
    std::stack<TreeNode*> st;
    std::stack<int> heights;

    TreeNode* cur = root;
    TreeNode* lastVisited = nullptr;

    while(cur || !st.empty())
    {
        while(cur)
        {
            st.push(cur);
            cur = cur->left;
        }

        TreeNode* node = st.top();
        if(node->right && node->right != lastVisited)
        {
            cur = node->right;
        }
        else
        {
            int height_1, height_2; 
            if(node->left && node->right)
            {
                height_1 = heights.top();
                heights.pop();
                height_2 = heights.top();
                heights.pop();
            }
            else if(node->left || node->right)
            {
                height_1 = heights.top();
                heights.pop();
                height_2 = 0;
            }
            else
            {
                height_1 = 0;
                height_2 = 0;
            }

            if(std::abs(height_1 - height_2) > 1)
            {
                return false;
            }
            heights.push(std::max(height_1,height_2) + 1);

            lastVisited = node;
            st.pop();
        }
    }
    return true;
}

//Найти максимальное расстояние между двумя нодами. Неважно через root или нет.
int getMaxDiameter(TreeNode* root)
{
    int maxDiameter = 0;

    std::stack<TreeNode*> st;
    std::stack<int> heights;

    TreeNode* cur = root;
    TreeNode* lastVisited = nullptr;

    while(cur || !st.empty())
    {
        while(cur)
        {
            st.push(cur);
            cur = cur->left;
        }

        TreeNode* node = st.top();
        if(node->right && node->right != lastVisited)
        {
            cur = node->right;
        }
        else
        {
            int height_1, height_2; 
            if(node->left && node->right)
            {
                height_1 = heights.top();
                heights.pop();
                height_2 = heights.top();
                heights.pop();
            }
            else if(node->left || node->right)
            {
                height_1 = heights.top();
                heights.pop();
                height_2 = 0; 
            }
            else
            {
                height_1 = 0;
                height_2 = 0;
            }
            maxDiameter = std::max(height_1+height_2,maxDiameter); 

            heights.push(std::max(height_1,height_2) + 1);

            lastVisited = node;
            st.pop();
        }
    }
    return maxDiameter;
}

//То же самое но с рекурсией
int getHeight(TreeNode* node, int& maxDiameter)
{
    if(!node)
    {
        return 0;
    }
    int leftHeight = getHeight(node->left,maxDiameter);
    int rightHeight = getHeight(node->right,maxDiameter);
    maxDiameter = std::max(leftHeight + rightHeight,maxDiameter);

    return std::max(leftHeight,rightHeight) + 1; 
}

int getMaxDiameterRecursion(TreeNode* root)
{
    int maxDiameter = 0;
    getHeight(root,maxDiameter);
    return maxDiameter;
}



//Задачи Top Down - родитель сообщает потомкам информацию

// Вернуть true, если существует путь от КОРНЯ до ЛИСТА,
// сумма значений на котором равна targetSum
bool hasPathSum(TreeNode* root, int targetSum) {
    if(!root)
    {
        return false;
    }

    targetSum -= root->val;

    if(!root->left && !root->right && targetSum == 0)
    {
        return true;
    }
    return hasPathSum(root->left,targetSum) || hasPathSum(root->right,targetSum);
}

// Проверить, является ли дерево корректным BST
bool isValidBST(TreeNode* root, int64_t min = std::numeric_limits<int64_t>::min(), int64_t max = std::numeric_limits<int64_t>::max()) {
    if(!root)
    {
        return true;
    }

    return static_cast<int64_t>(root->val) > min && static_cast<int64_t>(root->val) < max && 
        isValidBST(root->left,min,static_cast<int64_t>(root->val)) && 
        isValidBST(root->right,static_cast<int64_t>(root->val),max);
}


// Вернуть k-ое по величине (k-ое наименьшее, 1-indexed) значение в BST
int kthSmallest(TreeNode* root, int k) {
    
    if(!root)
    {
        return std::numeric_limits<int>::min();
    }

    std::stack<TreeNode*> st;

    auto goToLeft = [&st](TreeNode* node){
        while(node)
        {
            st.push(node);
            node = node->left;
        }
    };

    int grade = 0;
    goToLeft(root);

    while(!st.empty())
    {
        TreeNode* currentNode = st.top();
        st.pop();

        if(++grade == k)
        {
            return currentNode->val;
        }

        goToLeft(currentNode->right);
    }      
    return std::numeric_limits<int>::min();
}

// root — корень BST
// p, q — два узла, ГАРАНТИРОВАННО существующие в дереве
// Вернуть их наименьшего общего предка (LCA)
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    TreeNode* lowestAncestor = root;
    while(true)
    {    
        if(p->val < lowestAncestor->val && q->val < lowestAncestor->val)
        {
            lowestAncestor = lowestAncestor->left;
        }
        else if(p->val > lowestAncestor->val && q->val > lowestAncestor->val)
        {
            lowestAncestor = lowestAncestor->right;
        }   
        else
        {
            break;
        }
    }
    return lowestAncestor;
}



// root — корень ОБЫЧНОГО бинарного дерева (НЕ BST, никакого порядка значений)
// p, q — гарантированно существуют в дереве
// Вернуть LCA
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root) return nullptr;
    if (root == p || root == q) return root;
    
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    
    if(left)
    if(!left && !right)
    {
        return nullptr;
    }

    // Что нужно сделать с left и right, чтобы получить ответ?
}

int main()
{
    // std::random_device rd;
    // std::mt19937 gen{rd()};    
    // std::uniform_int_distribution<unsigned> dist{0,10};


    return 0;
}