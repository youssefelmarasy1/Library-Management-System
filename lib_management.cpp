#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Book {
    public:
        string title;
        string author;
        string isbn;
        
    
    // Creating a constructor
    /* We initialize the member variable using this way because of the parameter names shadow
       member variable names.
       The convention used is member_variable(parameter_name) */ 

    Book(const string& title, const string& author, const string &isbn) : 
    title(title), author(author), isbn(isbn) {}

    // After the constructor is created, we now have the book instance's parameters passed 

    
    // This method uses the const qualifier because it will access the object but not modify it
    void displayDetails() const;

    void checkOut();
    void checkIn();

};

class Member {
    // All methods defined
    public:
        int memberID;
        string name;

        // Creating a constructor
        Member(int member_ID, const string& Name) : memberID(member_ID), name(Name) {};

        // vector that stores instances of the books borrowed by the meber
        vector <string> booksBorrowed;

    void displayDetails() const;
};

class Transaction {
    // All methods defined
    public:
        int transID;
        string bookISBN;
        int memberID;
        string date;
        bool checkedOut;

    Transaction(int trans_ID, int member_ID, const string& book_ISBN, bool checked_Out):
    transID(trans_ID), memberID(member_ID), bookISBN(book_ISBN), checkedOut(checked_Out) {};

    
    void displayDetails() const;
};

class Library{
    // All methods defined
    // vectors that store instances of each class
    public:
        vector <Book> books;
        vector <Member> members;
        vector <Transaction> transactions;
        int transactionCounter;
    
    // Creating the constructor
    Library() : transactionCounter(1) {};

    void addBook(const Book& book);
    void addMember(const Member& member);
    void displayBooks() const;
    void displayMembers() const;
    void displayTransactions() const;
    void checkOutBook(int memberId, const string& bookIsbn);
    void checkInBook(int memberId, const string& bookIsbn);
};

void Book::displayDetails() const {
    cout << "Title: " << title << "\nAuthor: " << author << "\nISBN: " << isbn << endl;

};

void Book::checkIn() {
    cout << "Book checked in: " << title << endl;
};

void Book::checkOut() {
    cout << "Book checked out: " << title << endl;
};

void Member::displayDetails() const {
    cout << "Member Detials: " << endl;
    cout << "Member ID: " << memberID << "\nName: " << name << endl;
};

void Transaction::displayDetails() const {
        cout << "Transaction ID: " << transID << "\nMember ID: " << memberID
            << "\nBook ISBN: " << bookISBN << "\nChecked Out: " << (checkedOut ? "Yes" : "No") << endl;
};

void Library::addBook(const Book& book) {
    books.push_back(book);
    cout << "Book successfully added to the library system" <<  endl;
};

void Library::addMember(const Member& member){
    members.push_back(member);
    cout << "Member successfully added to the library" << endl;
};

void Library::displayBooks() const {
    cout << "Books in the library system: \n";
    // loop to iterate over each element of the "books" vector,. which is the book object itself
    // auto is used for automatic type deduction
    for (const auto& book: books) {
        book.displayDetails();
        cout << "----------------------------\n";
    }
};

void Library::displayMembers() const {
    cout << "Members in the library system: \n";
    // loop to iterate over each element of the "books" vector,. which is the book object itself
    // auto is used for automatic type deduction
    for (const auto& member: members) {
        member.displayDetails();
        cout << "----------------------------\n";
    }
};

void Library::displayTransactions() const {
        std::cout << "Transactions in the library:\n";
        for (const auto& transaction : transactions) {
            transaction.displayDetails();
            std::cout << "------------------------\n";
        }
};

 void Library::checkOutBook(int memberId, const std::string& bookIsbn) {
        // Implementing the check-out logic and updating the transactions vector
        Transaction transaction(transactionCounter++, memberId, bookIsbn, true);
        transactions.push_back(transaction);
        cout << "Book checked out successfully." << endl;
};

void Library::checkInBook(int memberId, const std::string& bookIsbn) {
        // Implementing the check-in logic and updating the transactions vector
        Transaction transaction(transactionCounter++, memberId, bookIsbn, false);
        transactions.push_back(transaction);
        cout << "Book checked in successfully." << endl;
};

Book getBookFromUser(){
    string title, author, ISBN;
    cout << "Enter book title: ";
    getline(cin, title);

     cout << "Enter author name: ";
    getline(cin, author);

    cout << "Enter ISBN: ";
    getline(cin, ISBN);

    return Book(title, author, ISBN);
    
};

Member getMemberFromUser() {
    int memberID;
    string name;

    cout << "Enter member ID: ";
    cin >> memberID;
    cin.ignore();

    cout << "Enter member name: ";
    getline(cin, name);

    return Member(memberID, name);
};

void displayMenu() {
    cout << "\nLibrary Management System Menu:\n";
    cout << "1. Add Book\n";
    cout << "2. Add Member\n";
    cout << "3. Display Books\n";
    cout << "4. Display Members\n";
    cout << "5. Check Out Book\n";
    cout << "6. Check In Book\n";
    cout << "7. Exit\n";

};

int main () {
    Library library;
    int choice;
    int memberId;  // Declare memberId outside the switch case
    string bookIsbn;  // Declare bookIsbn outside the switch case

    do {
        
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
         case 1:
                library.addBook(getBookFromUser());
                break;
            case 2:
                library.addMember(getMemberFromUser());
                break;
            case 3:
                library.displayBooks();
                break;
            case 4:
                library.displayMembers();
                break;
            case 5:
                
                cout << "Enter member ID: ";
                cin >> memberId;
                cin.ignore(); 

                cout << "Enter book ISBN: ";
                cin >> bookIsbn;
                cin.ignore(); 

                library.checkOutBook(memberId, bookIsbn);
                break;

            case 6:
                cout << "Enter member ID: ";
                cin >> memberId;
                cin.ignore(); 

                cout << "Enter book ISBN: ";
                cin >> bookIsbn;
                cin.ignore(); 

                library.checkInBook(memberId, bookIsbn);
                break;
            case 7:
                cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        };
    } while(choice != 7);

};