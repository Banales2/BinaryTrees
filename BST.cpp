#include <iostream>
#include <queue>
using namespace std;

struct Node
{
    int data;
    Node *left, *right;

    Node(int d):data(d), left(NULL), right(NULL){}
};

class BST{
    private:
        Node *Root;
        vector <int> renglon;
        int cont = 1;

        void Insert(int&, Node*&);
        void ancestors(int&,vector <int>,Node*&);
        int whatLevelIm(int&, int,Node*&);
        void InOrder(Node*);
        void PreOrder(Node*);
        void PostOrder(Node*);
        void DeleteAll(Node*);
        void DeleteNode(int&,Node*&);
    public:
        BST():Root(NULL){}
        ~BST(){
            DeleteBST(Root);
            cout<<"\nDestructor: BST deleted";
        }
        void Insert(int &value){Insert(value, Root);}

        void InOrder(){InOrder(Root);}
        void PreOrder(){PreOrder(Root);}
        void PostOrder(){PostOrder(Root);}
        void DeleteAll(){DeleteAll(Root);}
        void BFT();
        void Display_Tree();
        int height();
        void ancestors(int busq){ancestors(busq,renglon, Root);}
        int whatLevelIm(int busq){whatLevelIm(busq,cont, Root);}

        void SubstituteToMin(Node*&, Node*&);
        void DeleteNode(int &value){ DeleteNode(value, Root);}

        void DeleteBST(Node*&);
        void visit(int);
};

void BST::Insert(int &value, Node *&currentNode){
    if (currentNode == NULL){
        currentNode = new Node(value);
    }else{
        if (value<currentNode->data)
            Insert(value, currentNode->left);
        else if (value>currentNode->data)
            Insert(value, currentNode->right);
        else
            cout << "Repeated element. \n";        
    }
}

void BST::ancestors(int &search, vector <int> acum, Node *&currentNode){
    if (currentNode == NULL){
        return;
    }else{
        if (search<currentNode->data){
            acum.push_back(currentNode->data);
            ancestors(search, acum, currentNode->left);
        }
        else if (search>currentNode->data){
            acum.push_back(currentNode->data);
            ancestors(search, acum, currentNode->right);
        }
        else
            for (int i = 0; i < acum.size(); i++)
            {
                cout<<acum[i]<<" ";
            }
    cout << endl;
    }
}

int BST::whatLevelIm(int &search, int acum, Node *&currentNode){
    if (currentNode == NULL){
        return -1;
    }else{
        if (search<currentNode->data){
            acum +=1;
            whatLevelIm(search, acum, currentNode->left);
        }
        else if (search>currentNode->data){
            acum += 1;
            whatLevelIm(search, acum, currentNode->right);
        }
        else
            return acum;
    }
}

void BST::PreOrder(Node *currentNode){
    cout<<"Preorder"<<endl;
    if(currentNode == NULL)
        return;
    cout << currentNode->data << " ";
    PreOrder(currentNode->left);
    PreOrder(currentNode->right);
}

void BST::InOrder(Node *currentNode){
    cout<<"InOrder"<<endl;
    if(currentNode == NULL)
        return;
    InOrder(currentNode->left);
    cout << currentNode->data << " ";
    InOrder(currentNode->right);
}

void BST::PostOrder(Node *currentNode){
    cout<<"PostOrder"<<endl;
    if(currentNode == NULL)
        return;
    PostOrder(currentNode->left);
    PostOrder(currentNode->right);
    cout << currentNode->data << " ";
}

void BST::BFT(){
    cout<<"Por niveles"<<endl;
    if (Root == NULL){
        cout << "El BST esta vacio"<<endl;
        return;
    }
    queue<Node*> Q;
    Q.push(Root);

    Node *Aux;
    while (!Q.empty()){
        Q.push(NULL);

        Aux = Q.front();
        while (Aux != NULL){
            cout << Aux->data << " ";

            if (Aux->left != NULL)
                Q.push(Aux->left);
            if (Aux->right != NULL)
                Q.push(Aux->right);

            Q.pop();
            Aux = Q.front();
        }
        Q.pop();
        cout << endl;
    }
}

void BST::Display_Tree(){
    if (Root == NULL){
        cout << "El arbol esta vacio"<<endl;
        return;
    }
    
    queue<Node*> Q;
    Q.push(Root);

    queue<int> padres;
    padres.push(-1);

    queue<char> dir;
    dir.push('^');

    Node *Aux;
    while (!Q.empty()){
        Q.push(NULL);

        Aux = Q.front();
        while (Aux != NULL){
            cout << Aux->data << "(" << padres.front() << ") ";
            padres.pop();
            dir.pop();

            if(Aux->left !=NULL){
                Q.push(Aux->left);
                padres.push(Aux->data);
                dir.push('<');
            }
            if(Aux->right !=NULL){
                Q.push(Aux->right);
                padres.push(Aux->data);
                dir.push('>');
            }

            Q.pop();
            Aux = Q.front();
        }
        Q.pop();
        cout<<endl;
    }
}

void BST::SubstituteToMin(Node *&aptAux, Node *&aptNode){
    if(aptAux->left != NULL)
        SubstituteToMin(aptAux->left, aptNode);
    else{
        aptNode->data = aptAux->data;
        aptNode = aptAux;
        aptAux = aptAux->right;
    }
}

void BST::DeleteNode(int &value, Node *&currentNode){
    if (currentNode == NULL)
    {
        cout<<"El arbol esta vacio"<<endl<<endl;
    }
    else{
        if (value < currentNode->data)
            DeleteNode(value,currentNode->left);
        else if (value > currentNode->data)
            DeleteNode(value,currentNode->right);
        else{
            Node *apAux = currentNode;

            if (apAux->right == NULL)
                currentNode = apAux->left;
            if (apAux->left == NULL)
                currentNode = apAux->right;
            if (apAux->left != NULL && apAux->right !=NULL)
                SubstituteToMin(currentNode->right, apAux);

            cout << "\nLlave del valor a eliminar: "<<value <<endl;
            cout << "El elemento fue eliminado con: "<< apAux->data<<endl;
            delete apAux;
        }
    }
}

void BST::visit(int op){
    if (op == 1)
        PreOrder();
    else if (op == 2)
        InOrder();
    else if (op == 3)
        PostOrder();
    else if (op == 4)
        BFT();
    else
        cout << "error" <<endl;
    cout<<endl;
}


int BST::height(){
    int acum = 0;
    if (Root == NULL){
        return 0;
    }
    queue<Node*> Q;
    Q.push(Root);

    Node *Aux;
    while (!Q.empty()){
        Q.push(NULL);

        Aux = Q.front();
        while (Aux != NULL){

            if (Aux->left != NULL)
                Q.push(Aux->left);
            if (Aux->right != NULL)
                Q.push(Aux->right);
            Q.pop();
            Aux = Q.front();
        }
        acum += 1;
        Q.pop();
    }
    return acum;
}

void BST::DeleteBST(Node *&currentNode){
    if(!currentNode)
        return;
    DeleteBST(currentNode->left);
    DeleteBST(currentNode->right);
    delete currentNode;
}

int main(){
    system("cls");

    BST A;

    vector<int> v = {37,70,22,13,5,13,42,19,52,14};
    for(int i: v){
        A.Insert(i);
    }
    A.visit(1);
    A.visit(2);
    A.visit(3);
    A.visit(4);
    
    cout << A.height() << endl;
    A.ancestors(19);
    cout<<A.whatLevelIm(1)<<endl;

    int a = 16;
    A.DeleteNode(a);
    cout << A.height() << endl;
    A.ancestors(51);
    cout<<A.whatLevelIm(22)<<endl;


    a=13;
    A.DeleteNode(a);
    cout << A.height() << endl;
    A.ancestors(14);
    cout<<A.whatLevelIm(14)<<endl;


    cout << A.height() << endl;

    a=47;
    A.DeleteNode(a);
    cout << A.height() << endl;
    A.ancestors(5);
    cout<<A.whatLevelIm(19)<<endl;

    return 0;
}