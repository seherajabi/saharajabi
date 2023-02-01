
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <fstream>
using namespace std;
struct Person
{
    string username;
    string password;
    string firstName;
    string lastName;
    string brth;
};

struct Book
{
    string title;
    string shelfNumber;
    string authors;
    string edition;
    string publisher;
    string publisherDate;
    string ISBN;
    string length;
    string subject;
    string status;
};

struct Borrow
{
    string username;
    string ISBN;
};

Person createNewUser()
{
    Person p;
    cout << "input username:";

    getline(cin >> ws, p.username);

    cout << "input password:";
    getline(cin >> ws, p.password);

    cout << "input firstname:";
    getline(cin >> ws, p.firstName);

    cout << "input lastname:";
    getline(cin >> ws, p.lastName);

    cout << "input birthday:";
    getline(cin >> ws, p.brth);
    return p;
}
bool existsUser(vector<Person> listUser, string user)
{
    for (int i = 0; i < listUser.size(); i++)
    {
        if (listUser[i].username == user)
            return true;
    }
    return false;
}
void insertUser(vector<Person> &listUser)
{
    Person user = createNewUser();
    if (existsUser(listUser, user.username) == false)
        listUser.push_back(user);
}
void readFileUser(vector<Person> &listUser)
{
    ifstream file("users.txt");
    Person p;
    while (file >> p.username >> p.password >> p.firstName >> p.lastName >> p.brth)
    {
        listUser.push_back(p);
    }
}
void writeFileUser(vector<Person> &listUser)
{
    ofstream file("users.txt");
    for (int i = 0; i < listUser.size(); i++)
    {
        file << listUser[i].username << " " << listUser[i].password << " " << listUser[i].firstName
             << " " << listUser[i].lastName << " " << listUser[i].brth << endl;
    }
}
void readFileBorrow(vector<Borrow> &listBorrow)
{
    ifstream file("borrow.txt");
    Borrow p;
    while (file >> p.username >> p.ISBN)
    {
        listBorrow.push_back(p);
    }
}
void writeFileBorrow(vector<Borrow> &listBorrow)
{
    ofstream file("borrow.txt");
    for (int i = 0; i < listBorrow.size(); i++)
    {
        file << listBorrow[i].username << " " << listBorrow[i].ISBN << endl;
    }
}
int countUserBorrow(vector<Borrow> &listBorrow, string username)
{
    int sum = 0;
    for (int i = 0; i < listBorrow.size(); i++)
    {
        if (listBorrow[i].username == username)
            sum++;
    }
    return sum;
}
int deleteUserBorrow(vector<Borrow> &listBorrow, Borrow b)
{
    for (int i = 0; i < listBorrow.size(); i++)
    {
        if (listBorrow[i].username == b.username && listBorrow[i].ISBN == b.ISBN)
            listBorrow.erase(listBorrow.begin() + i);
    }
}
int showUserBorrow(vector<Borrow> &listBorrow, string username)
{
    for (int i = 0; i < listBorrow.size(); i++)
    {
        if (listBorrow[i].username == username)
            cout << username << " " << listBorrow[i].ISBN << endl;
    }
}
Person *login(vector<Person> listUser, string username, string password)
{
    for (int i = 0; i < listUser.size(); i++)
    {
        if (listUser[i].username == username && listUser[i].password == password)
            return &listUser[i];
    }
    return NULL;
}
void printInfoBook(Book book)
{
    cout<<"--------------------------------Information--------------------------------\n";
    cout << "title : " << book.title <<endl;
    cout << "shelfNumber : " << book.shelfNumber <<endl;
    cout << "authors : " << book.authors <<endl;
    cout << "edition : " << book.edition <<endl;
    cout << "publisher : " << book.publisher <<endl;
    cout << "publisherDate : " << book.publisherDate <<endl;
    cout << "ISBN : " << book.ISBN <<endl;
    cout << "length : " << book.length <<endl;
    cout << "subject : " << book.subject << endl;
}
void printAllBook(vector<Book> listBook)
{
    for (int i = 0; i < listBook.size(); i++)
    {
        printInfoBook(listBook[i]);
    }

}
void searchBookByTitle(vector<Book> listBook, string title)
{
    for (int i = 0; i < listBook.size(); i++)
    {
        if (listBook[i].title == title)
            printInfoBook(listBook[i]);
    }
}
void searchBookByAuthor(vector<Book> &listBook, string author)
{
    for (int i = 0; i < listBook.size(); i++)
    {
        if (listBook[i].authors == author)
            printInfoBook(listBook[i]);
    }
}
void searchBookByPublisher(vector<Book> &listBook, string publisher)
{
    for (int i = 0; i < listBook.size(); i++)
    {
        if (listBook[i].publisher == publisher)
            printInfoBook(listBook[i]);
    }
}
void searchBookByPublisherYear(vector<Book> &listBook, string publisherYear)
{
    for (int i = 0; i < listBook.size(); i++)
    {
        if (listBook[i].publisherDate == publisherYear)
            printInfoBook(listBook[i]);
    }
}
Book *getBookByISBN(vector<Book> &listBook, string isbn)
{
    for (int i = 0; i < listBook.size(); i++)
    {
        if (listBook[i].ISBN == isbn)
            return &listBook[i];
    }
    return NULL;
}
void readFileBook(vector<Book> &listBook)
{
    ifstream file("book.txt");
    Book b;
    while (file >> b.title >> b.shelfNumber >> b.authors >>b.edition>> b.publisher >> b.publisherDate >> b.ISBN >> b.length >> b.subject>> b.status)
    {
        listBook.push_back(b);
    }
}
void writeFileBook(vector<Book> &listBook)
{
    ofstream file("book.txt");
    for (int i = 0; i < listBook.size(); i++)
    {
        file << listBook[i].title << " " << listBook[i].shelfNumber << " " << listBook[i].authors
             << " " << listBook[i].edition<< " " << listBook[i].publisher << " " << listBook[i].ISBN<< " " << listBook[i].length
             << " " << listBook[i].subject<< " " << listBook[i].status << endl;
    }
}
void userMenu(vector<Person> &listUser, vector<Book> &listBook, vector<Borrow> &listBorrow)
{
    string username, password;
    cout << "input username:";
    getline(cin >> ws, username);
    cout << "input password:";
    getline(cin >> ws, password);
    Person *loggined = login(listUser, username, password);
    int select;
    if (loggined != NULL)
    {
        while (true)
        {
            cout << "1-search book by title" << endl;
            cout << "2-search book by author" << endl;
            cout << "3-search book by publisher" << endl;
            cout << "4-search book by publisher year" << endl;
            cout << "5-Borrowing books" << endl;
            cout << "6-return the book" << endl;
            cout << "7-show borrow" << endl;
            cout << "8-show allBook" << endl;
            cout << "0-exit" << endl;

            cin >> select;
            if (select == 1)
            {
                string title;
                cout << "input title:";
                getline(cin >> ws, title);
                searchBookByTitle(listBook, title);
            }
            if (select == 2)
            {
                string Author;
                cout << "input Author:";
                getline(cin >> ws, Author);
                searchBookByAuthor(listBook, Author);
            }
            if (select == 3)
            {
                string Publisher;
                cout << "input Publisher:";
                getline(cin >> ws, Publisher);
                searchBookByPublisher(listBook, Publisher);
            }
            if (select == 4)
            {
                string PublisherYear;
                cout << "input PublisherYear:";
                getline(cin >> ws, PublisherYear);
                searchBookByPublisherYear(listBook, PublisherYear);
            }
            if (select == 5)
            {
                if (countUserBorrow(listBorrow,username) < 2)
                {
                    cout << "input ISBN:";
                    string isbn;
                    getline(cin >> ws, isbn);
                    Book *selectedBook = getBookByISBN(listBook, isbn);
                    if (selectedBook != NULL)
                    {
                        if (selectedBook->status == "free")
                        {
                            selectedBook->status = "loan";
                            Borrow b;
                            b.username =username;
                            b.ISBN = isbn;
                            listBorrow.push_back(b);
                            writeFileBook(listBook);
                            writeFileBorrow(listBorrow);
                        }
                        else
                        {
                            cout << "ERROR:This book is on loan" << endl;
                        }
                    }
                    else
                    {
                        cout << "ERROR:You have borrowed two books" << endl;
                    }
                }

            }
            if (select == 6)
                {
                    cout << "input ISBN:";
                    string isbn;
                    getline(cin >> ws, isbn);
                    Book *selectedBook = getBookByISBN(listBook, isbn);
                    if (selectedBook != NULL)
                    {
                        if (selectedBook->status == "loan")
                        {
                            selectedBook->status = "free";
                            Borrow b;
                            b.username =username;
                            b.ISBN = isbn;
                            deleteUserBorrow(listBorrow, b);
                            writeFileBook(listBook);
                            writeFileBorrow(listBorrow);
                        }
                        else
                        {
                            cout << "ERROR:This book is on free" << endl;
                        }
                    }
                    else
                    {
                        cout << "ERROR:This book not found" << endl;
                    }
                }
                if (select == 7)
                {
                    showUserBorrow(listBorrow,username);
                }
                if (select == 8)
                {
                    printAllBook(listBook);
                }
                if (select == 0)
                {
                    break;
                }
        }
    }
    else
        cout << " username or password is wrong" << endl;
}
int main()
{
    vector<Person> listUser;
    vector<Book> listBook;
    vector<Borrow> listBorrow;
    readFileBook(listBook);
    readFileUser(listUser);
    readFileBorrow(listBorrow);
    int select;
    while (true)
    {
        cout << "1-login" << endl;
        cout << "2-register" << endl;
        cout << "3-exit" << endl;
        cin >> select;
        if (select == 1)
        {
            userMenu(listUser, listBook,listBorrow);
        }
        if (select == 2)
        {
            insertUser(listUser);
            writeFileUser(listUser);
        }
        if (select == 3)
        break;
    }

    return 0;
}
