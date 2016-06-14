
#include<iostream>
#include<string>
#include<fstream>
#include<vector>

// AVL tree (balanced tree)

struct node // the node
{
    int value;		// integer value of the node
    node* leftT;     	// root of the left subtree
    node* rightT; 	// root of the right subtree
    int height; 	// the height in the tree
};

class AVL_Tree
{
    public:
        AVL_Tree();
        ~AVL_Tree();
        void insert(int value); 	// insert value(node)
        void destroy();			// destroy the whole tree
        void search(int value);		// search value in the tree
        void deleteNode(int value);
        std::vector<int> iter(int value, std::vector<int> &nodes);
        void findRoot();
        int getSize();
        void printT();
    private:
        node* root;					// the root of the tree
        int size;
        void insert(int value, node* &rt);
        node* search(int value, node* rt);
        int isBalanced(node* rt);
        void balancing(node* &rt);
        void findHeight(node* rt);
        void destroy(node* rt);
        void rotateR(node* &rt);
        void rotateL(node* &rt);
        void printT(node* rt);
        void deleteNode(int value, node* &rt);
        node* min(node* rt);
        std::vector<int> iterHelper(node* tmp);
};

AVL_Tree::AVL_Tree()
{
    this->root = NULL;
}

AVL_Tree::~AVL_Tree()
{
    destroy();
}

void AVL_Tree::destroy()
{
    destroy(this->root);
}

void AVL_Tree::destroy(node* rt)
{
    if(rt != NULL)
    {
        destroy(rt->leftT);
        destroy(rt->rightT);
        delete rt;
    }
}

int AVL_Tree::getSize()
{
    return this->size;
}

void AVL_Tree::insert(int value)
{
    if(this->root == NULL)
    {
        this->root = new node;
        this->root->leftT = NULL;
        this->root->rightT = NULL;
        this->root->value = value;
        this->root->height = 1;
        this->size = 1;
    }
    else
    {
        insert(value, this->root);
    }
}

void AVL_Tree::insert(int value, node* &rt)
{
    if(rt == NULL)
    {
        rt = new node;
        rt->value = value;
        rt->leftT = NULL;
        rt->rightT = NULL;
        rt->height = 1;
        ++this->size;
    }
    else
    {
        if(value < rt->value)
            insert(value, rt->leftT);
        else
            insert(value, rt->rightT);
    }
    balancing(rt);
}

int AVL_Tree::isBalanced(node* rt)
{
    int leftH = (rt->leftT ? rt->leftT->height : 0);
    int rightH = (rt->rightT ? rt->rightT->height : 0);
    return rightH - leftH;
}

void AVL_Tree::findHeight(node* rt)
{
    int leftH = (rt->leftT ? rt->leftT->height : 0);
    int rightH = (rt->rightT ? rt->rightT->height : 0);
    rt->height = (leftH > rightH ? leftH : rightH) + 1;
}

void AVL_Tree::balancing(node* &rt)
{
    findHeight(rt);
    if(isBalanced(rt) == 2)
    {
        //std::cout << rt->value << '\n';
        if(isBalanced(rt->rightT) < 0)
        {
            rotateR(rt->rightT);
        }
        rotateL(rt);
    }
    else if(isBalanced(rt) == -2)
    {
        //std::cout << rt->value << '\n';
        if(isBalanced(rt->leftT) > 0)
        {
            rotateL(rt->leftT);
        }
        rotateR(rt);
    }
}

void AVL_Tree::rotateL(node* &rt)
{
    node* tmpRt = rt;
    rt = rt->rightT;
    tmpRt->rightT = rt->leftT;
    rt->leftT = tmpRt;
    findHeight(tmpRt);
    findHeight(rt);
}

void AVL_Tree::rotateR(node* &rt)
{
    node* tmpRt = rt;
    rt = rt->leftT;
    tmpRt->leftT = rt->rightT;
    rt->rightT = tmpRt;
    findHeight(tmpRt);
    findHeight(rt);
}

void AVL_Tree::search(int value)
{
    if(this->root == NULL)
    {
        std::cout << "The tree is empty\n";
    }
    else
    {
        node* tmp = search(value, this->root);
        if(!tmp)
        {
            std::cout << "Element " << value <<" not found\n";
        }
        else
            std::cout << "Element " << tmp->value << " is found\n";
    }
}

node* AVL_Tree::search(int value, node* rt)
{
    if(rt == NULL)
        return NULL;
    else
    {
        if(value < rt->value)
            return search(value, rt->leftT);
        else if(value > rt->value)
            return search(value, rt->rightT);
        else
            return rt;
    }
}

void AVL_Tree::printT()
{
    if(this->root == NULL)
        std::cout << "The tree is empty";
    else
        printT(this->root);
    std::cout << '\n';
}

void AVL_Tree::printT(node* rt)
{
    if(rt != NULL)
    {
        std::cout << rt->value << " ";
        printT(rt->leftT);
        printT(rt->rightT);
    }
}

void AVL_Tree::deleteNode(int value)
{
    if(this->root == NULL)
        std::cout << "The tree is empty\n";
    else
        deleteNode(value, this->root);
}

void AVL_Tree::deleteNode(int value, node* &rt)
{
    if(rt == NULL)
    {
        std::cout << "Element not found\n";
    }
    else if(value < rt->value)
        deleteNode(value, rt->leftT);
    else if(value > rt->value)
        deleteNode(value, rt->rightT);
    else
    {
        if(rt->leftT == NULL && rt->rightT == NULL)
        {
            node* tmp = rt;
            rt = NULL;
            delete tmp;
        }
        else if(rt->rightT != NULL && rt->leftT != NULL)
        {
            node* tmp = min(rt->rightT);
            rt->value = tmp->value;
            deleteNode(rt->value,rt->rightT);
        }
        else
        {
            if(rt->leftT)
            {
                node* tmp = rt->leftT;
                rt->value = rt->leftT->value;
                rt->leftT = tmp->leftT;
                rt->rightT = tmp->rightT;
                delete tmp;
            }
            else if(rt->rightT)
            {
                node* tmp = rt->rightT;
                rt->value = rt->rightT->value;
                rt->rightT = tmp->rightT;
                rt->leftT = tmp->leftT;
                delete tmp;
            }
        }
        --this->size;
    }
    if(rt != NULL)
        balancing(rt);
}

node* AVL_Tree::min(node* rt)
{
    return (rt->leftT == NULL ? rt : min(rt->leftT));
}

void AVL_Tree::findRoot()
{
    if(this->root != NULL)
        std::cout << this->root->value << '\n';
}

/*std::vector<int> AVL_Tree::iter(int value)
{
    node* tmp = search(value, this->root);
    if(tmp)
    {
        return iterHelper(tmp);
    }
    else return NULL;
}

std::vector AVL_Tree::iterHelper(node* tmp)
{
    if(tmp)
    {

    }
}*/

int* readFile(std::string, int &size);

int main()
{
    int numbers[] = {34, 6, 54, 8, 65};
    int limit = sizeof(numbers) / sizeof(int);
    AVL_Tree newTree;
    for(int i = 0; i < limit; i++)
    {
        newTree.insert(numbers[i]);
    }
    newTree.printT();
    //newTree.findRoot();
    newTree.deleteNode(6);
    newTree.printT();
    //newTree.search(1);
    newTree.getSize();
    int sizeArr = 0;
    int* arr = readFile("fileName", sizeArr);

    return 0;
}

int* readFile(std::string fName, int &size)
{
    std::ifstream data;
    data.open(fName);
    int d;
    if(data.is_open())
    {
        std::vector<int> values;
        values.reserve(100);
        while(data >> d)
        {
            ++size;
            values.push_back(d);
        }
        int* tmp  = &values[0];
        return tmp;
    }
    else
    {
        return NULL;
    }
    data.close();
}
