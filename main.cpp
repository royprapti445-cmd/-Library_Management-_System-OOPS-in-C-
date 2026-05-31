#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

// Base Class
class Person {
protected:
    int id;
    string name;

public:
    Person(int i = 0, string n = "") {
        id = i;
        name = n;
    }

    virtual void display() {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
    }
};

// Book Class
class Book {
public:
    int bookID;
    string bookName;
    string author;
    int quantity;

    Book() {}

    Book(int id, string bn, string au, int q) {
        bookID = id;
        bookName = bn;
        author = au;
        quantity = q;
    }

    void displayBook() {
        cout << "\nBook ID: " << bookID;
        cout << "\nBook Name: " << bookName;
        cout << "\nAuthor: " << author;
        cout << "\nQuantity: " << quantity << endl;
    }
};

// User Class
class User : public Person {
public:
    User(int id = 0, string name = "") : Person(id, name) {}

    void display() {
        cout << "\nUser ID: " << id;
        cout << "\nUser Name: " << name << endl;
    }
};

// Library Class
class Library {
private:
    vector<Book> books;

public:
    Library() {
        loadBooks();
    }

    void saveBooks() {
        ofstream file("books.txt");

        for (int i = 0; i < books.size(); i++) {
            file << books[i].bookID << ","
                 << books[i].bookName << ","
                 << books[i].author << ","
                 << books[i].quantity << endl;
        }

        file.close();
    }

    void loadBooks() {
        books.clear();

        ifstream file("books.txt");

        if (!file)
            return;

        Book b;
        string temp;

        while (getline(file, temp, ',')) {
            b.bookID = atoi(temp.c_str());

            getline(file, b.bookName, ',');
            getline(file, b.author, ',');
            getline(file, temp);

            b.quantity = atoi(temp.c_str());

            books.push_back(b);
        }

        file.close();
    }

    void addBook() {
        int id, qty;
        string name, author;

        cout << "\nEnter Book ID: ";
        cin >> id;

        for (int i = 0; i < books.size(); i++) {
            if (books[i].bookID == id) {
                cout << "Duplicate Book ID!\n";
                return;
            }
        }

        cin.ignore();

        cout << "Enter Book Name: ";
        getline(cin, name);

        cout << "Enter Author Name: ";
        getline(cin, author);

        cout << "Enter Quantity: ";
        cin >> qty;

        books.push_back(Book(id, name, author, qty));

        saveBooks();

        cout << "\nBook Added Successfully!\n";
    }

    void viewBooks() {
        if (books.empty()) {
            cout << "\nNo Books Available!\n";
            return;
        }

        for (int i = 0; i < books.size(); i++) {
            books[i].displayBook();
        }
    }

    void removeBook() {
        int id;

        cout << "\nEnter Book ID to Remove: ";
        cin >> id;

        for (int i = 0; i < books.size(); i++) {
            if (books[i].bookID == id) {
                books.erase(books.begin() + i);

                saveBooks();

                cout << "Book Removed Successfully!\n";
                return;
            }
        }

        cout << "Invalid Book ID!\n";
    }

    void updateBook() {
        int id;

        cout << "\nEnter Book ID to Update: ";
        cin >> id;

        for (int i = 0; i < books.size(); i++) {
            if (books[i].bookID == id) {

                cin.ignore();

                cout << "Enter New Book Name: ";
                getline(cin, books[i].bookName);

                cout << "Enter New Author Name: ";
                getline(cin, books[i].author);

                cout << "Enter New Quantity: ";
                cin >> books[i].quantity;

                saveBooks();

                cout << "Book Updated Successfully!\n";
                return;
            }
        }

        cout << "Book Not Found!\n";
    }

    void searchBook() {
        int id;

        cout << "\nEnter Book ID: ";
        cin >> id;

        for (int i = 0; i < books.size(); i++) {
            if (books[i].bookID == id) {
                books[i].displayBook();
                return;
            }
        }

        cout << "Book Not Found!\n";
    }

    void issueBook() {
        int id;

        cout << "\nEnter Book ID to Issue: ";
        cin >> id;

        for (int i = 0; i < books.size(); i++) {

            if (books[i].bookID == id) {

                if (books[i].quantity > 0) {
                    books[i].quantity--;

                    saveBooks();

                    cout << "Book Issued Successfully!\n";
                } else {
                    cout << "Book Not Available!\n";
                }

                return;
            }
        }

        cout << "Book Not Found!\n";
    }

    void returnBook() {
        int id;

        cout << "\nEnter Book ID to Return: ";
        cin >> id;

        for (int i = 0; i < books.size(); i++) {

            if (books[i].bookID == id) {

                books[i].quantity++;

                saveBooks();

                cout << "Book Returned Successfully!\n";

                return;
            }
        }

        cout << "Book Not Found!\n";
    }
};

int main() {

    Library lib;

    int choice;

    do {
        cout << "\n\n===== LIBRARY MANAGEMENT SYSTEM =====";
        cout << "\n1. Add Book";
        cout << "\n2. Remove Book";
        cout << "\n3. Update Book";
        cout << "\n4. View All Books";
        cout << "\n5. Search Book";
        cout << "\n6. Issue Book";
        cout << "\n7. Return Book";
        cout << "\n8. Exit";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            lib.addBook();
            break;

        case 2:
            lib.removeBook();
            break;

        case 3:
            lib.updateBook();
            break;

        case 4:
            lib.viewBooks();
            break;

        case 5:
            lib.searchBook();
            break;

        case 6:
            lib.issueBook();
            break;

        case 7:
            lib.returnBook();
            break;

        case 8:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 8);

    return 0;
}
