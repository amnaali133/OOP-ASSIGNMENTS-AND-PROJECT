#include <iostream>
#include <vector>
#include <string>
using namespace std;
//BASE CLASS 
class LibraryResource {
protected:
    int resourceID;
    string title;
    string author;
    bool isAvailable;
    string type; 

public:
    LibraryResource(int id = 0, string t = "", string a = "", string ty = "") {
        this->resourceID = id;   
        this->title = t;
        this->author = a;
        this->type = ty;
        this->isAvailable = true;
    }

    int getID() { 
        return resourceID;
    }
    bool getAvailability() {
        return isAvailable; 
    }

    void setAvailability(bool isAvailable) {
        this->isAvailable = isAvailable;
    }

    void displayDetails() {
        cout << "ID: " << resourceID
            << ", Title: " << title
            << ", Author: " << author
            << ", Type: " << type
            << ", Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
    int calculateLateFee(int daysLate) {
        if (type == "Book") return daysLate * 5;
        else if (type == "Magazine") return daysLate * 3;
        else if (type == "DVD") return daysLate * 10;
        return 0;
    }
};

// derived classes
class Book : public LibraryResource {
    string ISBN;
    int pageCount;

public:
    Book(int id, string t, string a, string isbn, int pages)
        : LibraryResource(id, t, a, "Book") {
        ISBN = isbn;
        pageCount = pages;
    }
};

class Magazine : public LibraryResource {
    int issueNumber;

public:
    Magazine(int id, string t, string a, int issue)
        : LibraryResource(id, t, a, "Magazine") {
        issueNumber = issue;
    }
};

class DVD : public LibraryResource {
    int duration;

public:
    DVD(int id, string t, string a, int dur)
        : LibraryResource(id, t, a, "DVD") {
        duration = dur;
    }
};

//member class
class LibraryMember {
    int memberID;
    string name;
    vector<LibraryResource> borrowedItems;

public:
    LibraryMember(int id = 0, string n = "") {
        memberID = id;
        name = n;
    }

    int getID() { 
        return memberID;
    }

    void borrowResource(LibraryResource res) {
        if (!res.getAvailability()) {
            cout << "Resource already borrowed!\n";
            return;
        }

        res.setAvailability(false);
        borrowedItems.push_back(res);
        cout << "Borrowed successfully!\n";
    }

    void returnResource(int id) {
        for (int i = 0; i < borrowedItems.size(); i++) {
            if (borrowedItems[i].getID() == id) {
                borrowedItems.erase(borrowedItems.begin() + i);
                cout << "Returned successfully!\n";
                return;
            }
        }
        cout << "Resource not found!\n";
    }

    void displayBorrowedItems() {
        if (borrowedItems.empty()) {
    
            cout << "No items borrowed.\n";
            return;
        }

        for (int i = 0; i < borrowedItems.size(); i++) {
            borrowedItems[i].displayDetails();
        }
    }

    int calculateTotalLateFee(int daysLate) {
        int total = 0;
        for (int i = 0; i < borrowedItems.size(); i++) {
            total += borrowedItems[i].calculateLateFee(daysLate);
        }
        return total;
    }

    friend void adminView(vector<LibraryResource>&, vector<LibraryMember>&);
};

//friend function
void adminView(vector<LibraryResource>& resources, vector<LibraryMember>& members) {
    cout << "\n===== ADMIN VIEW =====\n";

    cout << "\nAll Resources:\n";
    for (int i = 0; i < resources.size(); i++) {
        resources[i].displayDetails();
    }

    cout << "\nAll Members:\n";
    for (int i = 0; i < members.size(); i++) {
        cout << "Member ID: " << members[i].memberID
            << ", Name: " << members[i].name << endl;

        members[i].displayBorrowedItems();
    }
}

int main() {
    vector<LibraryResource> resources;
    vector<LibraryMember> members;

    int choice;

    do {
        cout << " MENU\n";
        cout << "1. Add Resource\n";
        cout << "2. Add Member\n";
        cout << "3. Borrow Resource\n";
        cout << "4. Return Resource\n";
        cout << "5. Display Resources\n";
        cout << "6. Display Member Items\n";
        cout << "7. Calculate Late Fee\n";
        cout << "8. Admin View\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int typeChoice;
            cout << "1.Book 2.Magazine 3.DVD: ";
            cin >> typeChoice;

            int id;
            string title, author;

            cout << "Enter ID: ";
            cin >> id;
            cin.ignore(); 

            cout << "Enter Title: ";
            getline(cin, title);

            cout << "Enter Author: ";
            getline(cin, author);

            if (typeChoice == 1) {
                string isbn;
                int pages;

                cout << "Enter ISBN: ";
                getline(cin, isbn);

                cout << "Enter Page Count: ";
                cin >> pages;

                Book b(id, title, author, isbn, pages);
                resources.push_back(b);
            }
            else if (typeChoice == 2) {
                int issue;
                cout << "Enter Issue Number: ";
                cin >> issue;

                Magazine m(id, title, author, issue);
                resources.push_back(m);
            }
            else {
                int duration;
                cout << "Enter Duration: ";
                cin >> duration;

                DVD d(id, title, author, duration);
                resources.push_back(d);
            }
        }

        else if (choice == 2) {
            int id;
            string name;

            cout << "Enter Member ID: ";
            cin >> id;
            cin.ignore(); 

            cout << "Enter Name: ";
            getline(cin, name);

            members.push_back(LibraryMember(id, name));
        }

        else if (choice == 3) {
            int mid, rid;
            cout << "Enter Member ID and Resource ID: ";
            cin >> mid >> rid;

            for (int i = 0; i < members.size(); i++) {
                if (members[i].getID() == mid) {
                    for (int j = 0; j < resources.size(); j++) {
                        if (resources[j].getID() == rid) {
                            members[i].borrowResource(resources[j]);
                        }
                    }
                }
            }
        }

        else if (choice == 4) {
            int mid, rid;
            cout << "Enter Member ID and Resource ID: ";
            cin >> mid >> rid;

            for (int i = 0; i < members.size(); i++) {
                if (members[i].getID() == mid) {
                    members[i].returnResource(rid);
                }
            }
        }

        else if (choice == 5) {
            for (int i = 0; i < resources.size(); i++) {
                resources[i].displayDetails();
            }
        }

        else if (choice == 6) {
            int id;
            cout << "Enter Member ID: ";
            cin >> id;

            for (int i = 0; i < members.size(); i++) {
                if (members[i].getID() == id) {
                    members[i].displayBorrowedItems();
                }
            }
        }

        else if (choice == 7) {
            int id, days;
            cout << "Enter Member ID and Days Late: ";
            cin >> id >> days;

            for (int i = 0; i < members.size(); i++) {
                if (members[i].getID() == id) {
                    cout << "Total Fee: "
                        << members[i].calculateTotalLateFee(days)
                        << endl;
                }
            }
        }

        else if (choice == 8) {
            adminView(resources, members);
        }

    } while (choice != 9);

    return 0;
}