#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

class Book {
private:
    int id;
    string title;
    string author;
    bool isBorrowed;

public:
    Book(int bookID, string bookTitle, string bookAuthor)
        : id(bookID), title(bookTitle), author(bookAuthor), isBorrowed(false) {}

    int getID() const { return id; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool getStatus() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayBook() const {
        cout << setw(5) << id << " | " << setw(20) << title << " | " 
             << setw(15) << author << " | " 
             << (isBorrowed ? "Borrowed" : "Available") << endl;
    }

    void saveToFile(ofstream& outFile) const {
        outFile << id << "," << title << "," << author << "," << isBorrowed << endl;
    }

    static Book loadFromFile(const string& data) {
        int bookID, borrowed;
        string bookTitle, bookAuthor;
        size_t pos1 = data.find(',');
        size_t pos2 = data.find(',', pos1 + 1);
        size_t pos3 = data.find(',', pos2 + 1);

        bookID = stoi(data.substr(0, pos1));
        bookTitle = data.substr(pos1 + 1, pos2 - pos1 - 1);
        bookAuthor = data.substr(pos2 + 1, pos3 - pos2 - 1);
        borrowed = stoi(data.substr(pos3 + 1));

        Book book(bookID, bookTitle, bookAuthor);
        if (borrowed) book.borrowBook();
        return book;
    }
};

class Library {
private:
    vector<Book> books;

public:
    void addBook(int id, string title, string author) {
        books.emplace_back(id, title, author);
        cout << "Book added successfully!\n";
    }

    void displayBooks() const {
        cout << "ID    | Title                | Author          | Status\n";
        cout << "-----------------------------------------------------------\n";
        for (const auto& book : books) {
            book.displayBook();
        }
    }

    void searchBook(int id) const {
        for (const auto& book : books) {
            if (book.getID() == id) {
                book.displayBook();
                return;
            }
        }
        cout << "Book not found!\n";
    }

    void borrowBook(int id) {
        for (auto& book : books) {
            if (book.getID() == id) {
                if (book.getStatus()) {
                    cout << "Book is already borrowed!\n";
                } else {
                    book.borrowBook();
                    cout << "Book borrowed successfully!\n";
                }
                return;
            }
        }
        cout << "Book not found!\n";
    }

    void returnBook(int id) {
        for (auto& book : books) {
            if (book.getID() == id) {
                if (!book.getStatus()) {
                    cout << "Book is already available!\n";
                } else {
                    book.returnBook();
                    cout << "Book returned successfully!\n";
                }
                return;
            }
        }
        cout << "Book not found!\n";
    }

    void saveLibraryToFile(const string& filename) const {
        ofstream outFile(filename);
        for (const auto& book : books) {
            book.saveToFile(outFile);
        }
        outFile.close();
        cout << "Library data saved successfully!\n";
    }

    void loadLibraryFromFile(const string& filename) {
        ifstream inFile(filename);
        string line;
        while (getline(inFile, line)) {
            books.push_back(Book::loadFromFile(line));
        }
        inFile.close();
        cout << "Library data loaded successfully!\n";
    }
};

int main() {
    Library library;
    int choice;

    library.loadLibraryFromFile("library_data.txt");

    do {
        cout << "\n--- Library Management System ---\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book\n";
        cout << "4. Borrow Book\n";
        cout << "5. Return Book\n";
        cout << "6. Save Library\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int id;
            string title, author;
            cout << "Enter Book ID: ";
            cin >> id;
            cin.ignore(); 
            cout << "Enter Book Title: ";
            getline(cin, title);
            cout << "Enter Book Author: ";
            getline(cin, author);
            library.addBook(id, title, author);
            break;
        }
        case 2:
            library.displayBooks();
            break;
        case 3: {
            int id;
            cout << "Enter Book ID to search: ";
            cin >> id;
            library.searchBook(id);
            break;
        }
        case 4: {
            int id;
            cout << "Enter Book ID to borrow: ";
            cin >> id;
            library.borrowBook(id);
            break;
        }
        case 5: {
            int id;
            cout << "Enter Book ID to return: ";
            cin >> id;
            library.returnBook(id);
            break;
        }
        case 6:
            library.saveLibraryToFile("library_data.txt");
            break;
        case 7:
            library.saveLibraryToFile("library_data.txt");
            cout << "Exiting... Goodbye!\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
