#include <iostream>

#include "binarySearch.hxx"
#include "bSearch.hxx"

using namespace std;

int main()
{

    btree x;

    int choice, num;

    node *temp;

    while (1)

    {

        cout<<"-----------------"<<"\n";

        cout<<"Operations on BST"<<"\n";

        cout<<"-----------------"<<"\n";

        cout<<"1.Insert Element "<<"\n";

        cout<<"2.Delete Element "<<"\n";

        cout<<"3.Inorder Traversal"<<"\n";

        cout<<"4.Preorder Traversal"<<"\n";

        cout<<"5.Postorder Traversal"<<"\n";

        cout<<"6.Display"<<"\n";

        cout<<"7.Quit"<<"\n";

        cout<<"Enter your choice : ";

        cin>>choice;

        switch(choice)

        {

        case 1:
            temp = new node;
            cout<<"Enter the number to be inserted : ";
            cin>>temp->key_value;
            x.insert(x.root, temp);

        case 2:
            if (x.root == NULL)
            {
                cout<<"Tree is empty, nothing to delete\n";
                continue;
            }
            cout<<"Enter the number to be deleted : ";
            cin>>num;
            x.del(num);
            break;

        case 3:
            cout<<"Inorder Traversal of BST:\n";
            x.inorder(x.root);
            cout<<"\n";
            break;

    case 4:
            cout<<"Preorder Traversal of BST:\n";
            x.preorder(x.root);
            cout<<"\n";
            break;

        case 5:
            cout<<"Postorder Traversal of BST:\n";
            x.postorder(x.root);
            cout<<"\n";
            break;

        case 6:
            cout<< "Display BST:\n";
            x.display(x.root,1);
            cout << "\n";
            break;

        case 7:
            exit(1);

        default:
            cout<<"Wrong choice\n";
        }

    }

    return 0;
}
