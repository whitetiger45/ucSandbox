//#ifndef BINARYSEARCH_HXX
//#define BINARYSEARCH_HXX
////Data Structures & Algorithms in C++ 2nd Edition
////Goodrich * Ramassia * Mount
////Page 433

//#include <exception>
//#include <iostream>
//#include <string>

//#include "entry.hxx"

//template<typename E>
//class SearchTree//a binary search tree
//{
//public:
//    class Entry;//entry class
//    typedef typename E::Key K; //a key
//    typedef typename E::Value V; //a value
//    class Iterator; //an iterator/position

//    SearchTree()//constructor
//        : T()
//        , n(0)
//    {
//        T.addRoot();
//        T.expandExternal(T.root()); //create the super root pg. 435
//    }

//    int size() const
//    {
//        return n;
//    }

//    bool empty() const
//    {
//        if(n == 0)
//            return true;

//        return false;
//    }

//    Iterator find(K const & k)//find entry with key k pg. 436
//    {
//        TPos v = finder(k, root());//search from virtual root

//        if(v.isInternal())
//        {
//            return Iterator(v);//found it
//        }
//        else
//        {
//           return end();//didn't find it
//        }
//    }

//    Iterator insert(K const & k, V const & x)//insert(k, x) pg. 436
//    {
//        TPos v = inserter(k, x);

//        return Iterator(v);
//    }

//    void erase(K const & k)//remove key k entry pg. 437
//    {
//        TPos v = finder(k, root());//search from virtual root

//        if(v.isExternal())
//        {
//            try
//            {
//                throw false;
//            }
//            catch (bool)
//            {
//                std::cout << "Erase of nonexistent!";
//            }
//        }
//        eraser(v);//remove it
//    }

//    void erase(Iterator const & p)//erase entry at p pg. 437
//    {
//        eraser(p.v);
//    }

//    Iterator begin()//iterator to first entry pg. 435
//    {
//        TPos v = root();//start at virtual root
//        while(v.isInternal())//find leftmost node
//        {
//            v = v.left();
//        }
//        return Iterator(v.parent());
//    }

//    Iterator end()//iterator to end entry pg. 435
//    {
//        return Iterator(T.root());//return the super root
//    }

//protected:
//    typedef SearchTree<E> BinaryTree;//linked binary tree
//    typedef typename SearchTree::Position TPos;//position in the tree

//    TPos root() const//get virtual root
//    {
//        return T.root().left();//left child of super root pg. 435
//    }

//    TPos finder(K const & k, TPos const & v)//find utility pg. 436
//    {
//        if(v.isEternal())
//        {
//            return v;//key not found
//        }

//        if(k < v->key())
//        {
//            return finder(k, v.left());//search left subtree
//        }

//        else if(v->key() < k)
//        {
//            return finder(k, v.right());//search right subtree
//        }

//        else
//        {
//            return v;//found it here
//        }
//    }

//    TPos inserter(K const & k, V const & x)//insert utility pg. 436
//    {
//        TPos v = finder(k, root());//search from virtual root

//        while(v.isInternal())//key already exists?
//        {
//            v = finder(k, v.right());//look further
//        }

//        T.expandExternal(v);//add new internal node

//        v->setKey(k);//set entry key
//        v->setValue(x);//set entry value

//        n++;//one more entry

//        return v;//return insert position
//    }

//    TPos eraser(TPos & v)//erase/remove utility pg. 437
//    {
//        TPos w;

//        if(v.left().isExternal())
//        {
//            w = v.left;//remove from left
//        }
//        else if(v.right.isExternal)
//        {
//            w = v.right();//remove from right
//        }
//        else//both internal?
//        {
//            w = v.right();//go to right subtree

//            do
//            {
//                w = w.left();//get leftmost node
//            }while(w.isInternal());

//            TPos u = w.parent();
//            v->setKey(u->key());//copy w's parent to v
//            v->setValue(u->value());//copy w's parent to v
//        }
//        n--;//one less entry

//        return T.removeAboveExternal(w);//remove w and parent
//    }

//    TPos restructure(TPos const & v); //restructure
//        //throw(BoundaryViolation);

//private:
//    BinaryTree T; // the binary tree
//    int n;//number of entries

//public:
//    class Iterator
//    {
//    private:
//        TPos v;

//    public:
//        Iterator(TPos const & vv)
//            : v(vv)
//        {
//        }

//        E const & operator*() const//get entry (read only)
//        {
//            return *v;
//        }

//        E & operator*() // get entry(read/write)
//        {
//            return *v;
//        }

//        bool operator ==(Iterator const & p) const//are iterators equal
//        {
//            return v == p.v;
//        }

//        Iterator& operator++()//in order successor
//        {
//            TPos w = v.right();
//            if(w.isInternal())//have right subtree?
//            {
//                do//move down left chain
//                {
//                    v = w;
//                    w = w.left();
//                }while(w.isInternal());
//            }
//            else//get parent
//            {
//                w = v.parent();
//                while(v == w.right())//move up right chain
//                {
//                    v = w;
//                    w = w.parent();
//                }
//                v = w;//and first link to left pg. 434
//            }

//            return *this;
//        }

//        friend class SearchTreee; //give searchtree access

//    };
//};

//#endif // BINARYSEARCH_HXX
