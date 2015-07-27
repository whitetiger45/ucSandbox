#ifndef BSEARCH_HXX
#define BSEARCH_HXX

#include <iostream>

using namespace std;

struct node
{
  int key_value;
  node *left;
  node *right;
};

class btree
{
    public:

        btree()
        {
          root= nullptr;
        }

        ~btree()
        {
          destroy_tree();
        }


        void find(int item, node **par, node **loc)
        {
            node *ptr, *ptrsave;

            if (root == NULL)
            {
                *loc = NULL;
                *par = NULL;
                return;

            }

            if (item == root->key_value)
            {
                *loc = root;
                *par = NULL;
                return;
            }

            if(item < root->key_value)
                ptr = root->left;

            else
                ptr = root->right;

            ptrsave = root;

            while (ptr != NULL)
            {
                if (item == ptr->key_value)
                {
                    *loc = ptr;
                    *par = ptrsave;
                    return;
                }

                ptrsave = ptr;

                if(item < ptr->key_value)
                    ptr = ptr->left;

                else
                    ptr = ptr->right;
            }

            *loc = NULL;
            *par = ptrsave;
        }


        void insert(node *tree, node *newnode)
        {
            if (root == NULL)
            {
                root = new node;

                root->key_value = newnode->key_value;
                root->left = NULL;
                root->right = NULL;
                cout<<"Root Node is Added\n";
                return;
            }

            if (tree->key_value == newnode->key_value)
            {
                cout<<"Element already in the tree\n";
                return;
            }

            if (tree->key_value > newnode->key_value)
            {
                if (tree->left != NULL)
                {
                    insert(tree->left, newnode);
                }

                else
                {
                    tree->left = newnode;
                    (tree->left)->left = NULL;
                    (tree->left)->right = NULL;
                    cout<<"Node Added To Left\n";
                    return;
                }

            }
            else
            {
                if (tree->right != NULL)
                {
                    insert(tree->right, newnode);
                }

                else
                {
                    tree->right = newnode;
                    (tree->right)->left = NULL;
                    (tree->right)->right = NULL;
                    cout<<"Node Added To Right\n";
                    return;
                }
            }

        }

        void insert(int key)
        {
          if(root!=nullptr)
            insert(key, root);
          else
          {
            root=new node;
            root->key_value=key;
            root->left=nullptr;
            root->right=nullptr;
          }
        }

        void case_a(node *par, node *loc )
        {
            if (par == NULL)
            {
                root = NULL;
            }
            else
            {
                if (loc == par->left)

                    par->left = NULL;

                else
                    par->right = NULL;
            }

        }

        void case_b(node *par, node *loc)
        {
            node *child;

            if (loc->left != NULL)
                child = loc->left;

            else
                child = loc->right;

            if (par == NULL)
            {
                root = child;
            }

            else
            {
                if (loc == par->left)
                    par->left = child;

                else
                    par->right = child;
            }

        }

        void case_c(node *par, node *loc)
        {
            node *ptr, *ptrsave, *suc, *parsuc;

            ptrsave = loc;

            ptr = loc->right;

            while (ptr->left != NULL)
            {
                ptrsave = ptr;
                ptr = ptr->left;
            }

            suc = ptr;

            parsuc = ptrsave;

            if (suc->left == NULL && suc->right == NULL)
                case_a(parsuc, suc);

            else
                case_b(parsuc, suc);

            if (par == NULL)
            {
                root = suc;
            }
            else
            {
                if (loc == par->left)
                    par->left = suc;

                else
                    par->right = suc;
            }
            suc->left = loc->left;
            suc->right = loc->right;

        }

        void preorder(node *ptr)
        {
            if (root == NULL)
            {
                cout<< "Tree is empty\n";
                return;
            }

            if (ptr != NULL)
            {
                cout<<ptr->key_value<<"  ";
                preorder(ptr->left);
                preorder(ptr->right);
            }
        }

        void inorder(node *ptr)
        {
            if (root == NULL)
            {
                cout<<"Tree is empty"<< "\n";
                return;
            }

            if (ptr != NULL)
            {
                inorder(ptr->left);
                cout<< ptr->key_value << "  ";
                inorder(ptr->right);
            }
        }

        void postorder(node *ptr)
        {
            if (root == NULL)
            {
                cout<<"Tree is empty"<< "\n";
                return;
            }

            if (ptr != NULL)
            {
                postorder(ptr->left);
                postorder(ptr->right);
                cout << ptr->key_value <<"  ";
            }
        }

        void display(node *ptr, int level)
        {
            int i;

            if (ptr != NULL)
            {
                display(ptr->right, level+1);
                cout<< "\n";

                if (ptr == root)
                    cout<<"Root->:  ";
                else
                {
                    for (i = 0;i < level;i++)
                        cout<<"       ";
            }
                cout<<ptr->key_value;
                display(ptr->left, level+1);
            }
        }

        void del(int item)
        {
            node *parent, *location;
            if(root == nullptr)
            {
                cout<<"Tree empty"<<endl;
                return;
            }

            find(item, &parent, &location);

            if (location == NULL)
            {
                cout <<"Item not present in tree" << "\n";
                return;
            }

            if (location->left == NULL && location->right == NULL)
                case_a(parent, location);

            if (location->left != NULL && location->right == NULL)
                case_b(parent, location);

            if (location->left == NULL && location->right != NULL)
                case_b(parent, location);

            if (location->left != NULL && location->right != NULL)
                case_c(parent, location);

            free(location);

        }

        void destroy_tree()
        {
          destroy_tree(root);
        }

        node* search(int key)
        {
          return search(key, root);
        }

//    private:

        void destroy_tree(node *leaf)
        {
          if(leaf!=nullptr)
          {
            destroy_tree(leaf->left);
            destroy_tree(leaf->right);
            delete leaf;
          }
        }

        void insert(int key, node *leaf)
        {
          if(key< leaf->key_value)
          {
            if(leaf->left!=nullptr)
             insert(key, leaf->left);
            else
            {
              leaf->left=new node;
              leaf->left->key_value=key;
              leaf->left->left=nullptr;    //Sets the left child of the child node to nullptr
              leaf->left->right=nullptr;   //Sets the right child of the child node to nullptr
            }
          }
          else if(key>=leaf->key_value)
          {
            if(leaf->right!=nullptr)
              insert(key, leaf->right);
            else
            {
              leaf->right=new node;
              leaf->right->key_value=key;
              leaf->right->left=nullptr;  //Sets the left child of the child node to nullptr
              leaf->right->right=nullptr; //Sets the right child of the child node to nullptr
            }
          }
        }

        node* search(int key, node *leaf)
        {
          if(leaf!=nullptr)
          {
            if(key==leaf->key_value)
              return leaf;
            if(key<leaf->key_value)
              return search(key, leaf->left);
            else
              return search(key, leaf->right);
          }
          else return nullptr;
        }

        node *root;
};

#endif // BSEARCH_HXX
