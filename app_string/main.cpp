#include <QCoreApplication>
#include <iostream>
#include <stdio.h>

using namespace std;

class myString
{
public:
    myString(char * str = NULL)
    {
        if (str == NULL)
        {
            m_data = new (char[1]);
            m_data = "\0";
        }
        else {
            m_data = new (char[strlen(str) + 1]);
            strcpy(m_data, str);
        }

        cout << "default funtion" << endl;
    }

    myString (const myString & other)
    {
        m_data = new (char[strlen(other.m_data) + 1]);
        strcpy(m_data, other.m_data);
        cout << "copy funtion" << endl;
    }

    myString &operator =(const myString & other)
    {
        if(this == &other)
        {
            return *this;
        }
        else
        {
//            delete [] m_data; //wei shen qing nei cun

            m_data = new char[strlen(other.m_data) + 1];
            strcpy(m_data, other.m_data);

            cout << "voluation funtion" << endl;
            return *this;
        }


    }


    ~myString()
    {
        delete[] m_data;
    }

    char * getData(){return m_data;}

private:
    char * m_data;
};


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    myString str1 = "adsdsad";

    myString str2 = str1;

    myString str3;

    str3 = str1;

    cout << str1.getData() << endl;
    cout << str2.getData() << endl;
    cout << str3.getData() << endl;

    return a.exec();
}
