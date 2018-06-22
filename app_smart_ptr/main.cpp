#include <QCoreApplication>
#include <iostream>
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/scoped_array.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include <vector>
#include <string>

using namespace std;
using namespace boost;
using namespace boost::filesystem;

class testB;

class testA
{
public:
    testA()
    {
        cout << "testA new" << endl;
    }
    ~ testA()
    {
        cout << "testA delete" << endl;
    }

    void testFun(shared_ptr<testA> testA_ptr)
    {
        cout << "count is: " << testA_ptr.get() << endl;
    }

    void testFun0()
    {
        cout << "this is testFun0" << endl;
    }

    void testFun1()
    {
        cout << "this is testFun1" << endl;
    }

    void testFun2()
    {
        cout << "this is testFun2" << endl;
    }

    shared_ptr<testB> testB;
};

class testB
{
public:
    testB()
    {
        cout << "testB new" << endl;
    }
    ~ testB()
    {
        cout << "testB delete" << endl;
    }

    void testFun(shared_ptr<testB> testB_ptr)
    {
        cout << "count is: " << testB_ptr.use_count() << endl;
    }

    weak_ptr<testA> testA;
};


void funA()
{
//    //vector in shared_ptr
//    vector<testA *> testAVector1;

//    vector<testA *> * testAVector = &testAVector1;
//    shared_array<vector<testA *> > testA_ptr(testAVector);

//    testA * test1 = new testA();
//    testA * test2 = new testA();
//    testA * test3 = new testA();

//    testAVector1.push_back(test1);
//    testAVector1.push_back(test2);
//    testAVector1.push_back(test3);

//    vector<testA*>::iterator iter;
//    for (iter = testAVector->begin(); iter != testAVector->end(); iter++)
//    {
//        (*iter)->testFun0();
//    }
//    //vector in shared_ptr no smart


    //shared_ptr in vector
    vector<shared_ptr<testA> > testAVector;

    shared_ptr<testA> testA_ptr1(new testA());
    shared_ptr<testA> testA_ptr2(new testA());
    shared_ptr<testA> testA_ptr3(new testA());

    testAVector.push_back(testA_ptr1);
    testAVector.push_back(testA_ptr2);
    testAVector.push_back(testA_ptr3);

    testAVector[0].get()->testFun0();
    testAVector[1].get()->testFun1();
    testAVector[2].get()->testFun2();
    //shared_ptr in vector is smart


//    //shared_array
//    shared_array<testA> testA_array_ptr(new testA[3]);
//    testA_array_ptr[0].testFun0();
//    testA_array_ptr[1].testFun1();
//    testA_array_ptr[2].testFun2();

//    //scoped_array
//    scoped_array<testA> testA_array_ptr(new testA[3]);
//    testA_array_ptr[0].testFun0();
//    testA_array_ptr[1].testFun1();
//    testA_array_ptr[2].testFun2();


//    testA_array_ptr[1] = test1;

//    scoped_ptr<testA> testA_ptr(new testA());

//    testA_ptr.get()->testFun1();



//    testA * test = new testA();

//    shared_ptr<testA> testA_ptr(new testA());

//    shared_ptr<testB> testB_ptr(new testB());

//    testA_ptr.get()->testB = testB_ptr;

//    testB_ptr.get()->testA = testA_ptr;

//    weak_ptr<testA> test1 = testA_ptr;
//    cout << test1.use_count();

//    testA_ptr.get()->testFun(testA_ptr);

//    cout << testA_ptr.use_count() << endl;
//    testA_ptr.get()->testFun(testA_ptr1);

//    cout << &testA_ptr << endl;
//    cout << &testA_ptr1 <<endl;

//    cout << testA_ptr << endl;
//    cout << testA_ptr1 <<endl;

//    cout << testA_ptr.get() << endl;
//    cout << testA_ptr1.get() <<endl;

//    if (&testA_ptr == &testA_ptr1)
//        cout << "=======" <<endl;

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    funA();

    return a.exec();
}

