#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <cstdlib>
using namespace std;

class Book {
private:
    int id;
    string title;
    string author;
    bool available;

public:
    Book() : id(0), title(""), author(""), available(true) {}

    Book(int bookId, string bookTitle, string bookAuthor, bool isAvailable = true)
        : id(bookId), title(bookTitle), author(bookAuthor), available(isAvailable) {}

    int getId() const { return id; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool isAvailable() const { return available; }

    void issue() { available = false; }
    void giveBack() { available = true; }

    void display() const {
        cout << left << setw(8) << id << setw(32) << title << setw(24) << author
             << (available ? "Available" : "Issued") << endl;
    }
};

class Library {
private:
    vector<Book> books;
    string fileName;

    int findIndex(int id) const {
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].getId() == id) return (int)i;
        }
        return -1;
    }

    void printHeader() const {
        cout << left << setw(8) << "ID" << setw(32) << "Title" << setw(24)
             << "Author" << "Status" << endl;
        cout << string(72, '-') << endl;
    }

    void loadFromFile() {
        ifstream in(fileName.c_str());
        if (!in.is_open()) {
            cout << "File not found. Starting with an empty library." << endl;
            return;
        }
        string line;
        while (getline(in, line)) {
            stringstream ss(line);
            string idText, title, author, status;
            getline(ss, idText, '|');
            getline(ss, title, '|');
            getline(ss, author, '|');
            getline(ss, status, '|');
            if (idText.empty() || title.empty() || author.empty() ||
                (status != "0" && status != "1"))
                continue;
            try {
                int id = stoi(idText);
                if (id > 0 && findIndex(id) == -1)
                    books.push_back(Book(id, title, author, status == "1"));
            } catch (const exception&) {
            }
        }
        cout << books.size() << " book(s) loaded from file." << endl;
    }

    void saveToFile() const {
        ofstream out(fileName.c_str());
        if (!out.is_open())
            throw runtime_error("Could not write to the file.");
        for (size_t i = 0; i < books.size(); i++) {
            out << books[i].getId() << '|' << books[i].getTitle() << '|'
                << books[i].getAuthor() << '|' << (books[i].isAvailable() ? 1 : 0)
                << '\n';
        }
    }

public:
    Library(string file) : fileName(file) { loadFromFile(); }

    void addBook(int id, string title, string author) {
        if (findIndex(id) != -1)
            throw runtime_error("A book with ID " + to_string(id) +
                                " already exists. IDs must be unique.");
        books.push_back(Book(id, title, author, true));
        saveToFile();
        cout << "Book added successfully." << endl;
    }

    void displayAll() const {
        if (books.empty()) {
            cout << "No books in the library." << endl;
            return;
        }
        printHeader();
        for (size_t i = 0; i < books.size(); i++) books[i].display();
        cout << "Total books: " << books.size() << endl;
    }

    void searchById(int id) const {
        int index = findIndex(id);
        if (index == -1) {
            cout << "No book found with ID " << id << "." << endl;
            return;
        }
        printHeader();
        books[index].display();
    }

    void searchByTitle(string keyword) const {
        transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);
        bool found = false;
        for (size_t i = 0; i < books.size(); i++) {
            string title = books[i].getTitle();
            transform(title.begin(), title.end(), title.begin(), ::tolower);
            if (title.find(keyword) != string::npos) {
                if (!found) printHeader();
                books[i].display();
                found = true;
            }
        }
        if (!found) cout << "No book found with that title." << endl;
    }

    void issueBook(int id) {
        int index = findIndex(id);
        if (index == -1)
            throw runtime_error("No book found with ID " + to_string(id) + ".");
        if (!books[index].isAvailable())
            throw runtime_error("Book '" + books[index].getTitle() +
                                "' is already issued.");
        books[index].issue();
        saveToFile();
        cout << "Book '" << books[index].getTitle() << "' issued successfully."
             << endl;
    }

    void returnBook(int id) {
        int index = findIndex(id);
        if (index == -1)
            throw runtime_error("No book found with ID " + to_string(id) + ".");
        if (books[index].isAvailable())
            throw runtime_error("Book '" + books[index].getTitle() +
                                "' was not issued, so it cannot be returned.");
        books[index].giveBack();
        saveToFile();
        cout << "Book '" << books[index].getTitle()
             << "' returned successfully. It is now available." << endl;
    }
};

int readId(const string& prompt) {
    string line;
    cout << prompt;
    if (!getline(cin, line)) {
        cout << endl << "Input ended. Exiting." << endl;
        exit(0);
    }
    try {
        size_t pos;
        int value = stoi(line, &pos);
        if (pos != line.size() || value <= 0) return -1;
        return value;
    } catch (const exception&) {
        return -1;
    }
}

bool readText(const string& prompt, string& text) {
    cout << prompt;
    if (!getline(cin, text)) {
        cout << endl << "Input ended. Exiting." << endl;
        exit(0);
    }
    if (text.find_first_not_of(" \t\r") == string::npos) {
        cout << "Error: this field cannot be empty." << endl;
        return false;
    }
    if (text.find('|') != string::npos) {
        cout << "Error: the character '|' is not allowed." << endl;
        return false;
    }
    return true;
}

void showMenu() {
    cout << endl
         << "===== LIBRARY BOOK MANAGEMENT SYSTEM =====" << endl
         << "1. Add a book" << endl
         << "2. Display all books" << endl
         << "3. Search a book by ID" << endl
         << "4. Search a book by title" << endl
         << "5. Issue a book" << endl
         << "6. Return a book" << endl
         << "7. Exit" << endl;
}

int main() {
    Library library("books.txt");
    int choice = 0;

    do {
        showMenu();
        choice = readId("Enter your choice (1-7): ");
        if (choice < 1 || choice > 7) {
            cout << "Invalid choice. Please enter a number from 1 to 7." << endl;
            choice = 0;
            continue;
        }

        try {
            int id;
            string title, author;
            if (choice == 1) {
                id = readId("Enter book ID (positive number): ");
                if (id == -1) {
                    cout << "Error: ID must be a positive whole number." << endl;
                    continue;
                }
                if (!readText("Enter title: ", title)) continue;
                if (!readText("Enter author: ", author)) continue;
                library.addBook(id, title, author);
            } else if (choice == 2) {
                library.displayAll();
            } else if (choice == 3) {
                id = readId("Enter book ID: ");
                if (id == -1)
                    cout << "Error: ID must be a positive whole number." << endl;
                else
                    library.searchById(id);
            } else if (choice == 4) {
                if (readText("Enter title (or part of it): ", title))
                    library.searchByTitle(title);
            } else if (choice == 5) {
                id = readId("Enter ID of the book to issue: ");
                if (id == -1)
                    cout << "Error: ID must be a positive whole number." << endl;
                else
                    library.issueBook(id);
            } else if (choice == 6) {
                id = readId("Enter ID of the book to return: ");
                if (id == -1)
                    cout << "Error: ID must be a positive whole number." << endl;
                else
                    library.returnBook(id);
            } else {
                cout << "Thank you. Goodbye!" << endl;
            }
        } catch (const runtime_error& e) {
            cout << "Error: " << e.what() << endl;
        }
    } while (choice != 7);

    return 0;
}
