#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include <sstream>
#include"lib.h"
using namespace std;
void Book_Management::new_book(){
    string title, author, genre,  availability;
    int number_books;
    int total_books=29;
    int id=1;
    fstream output;
    cout << "please enter the number of new books: " << endl;
    cin >> number_books;
    cin.ignore(); // ignore after i use cin twice for number and string 
    output.open("book.txt", ios::app|ios::out);
    int i = 0;
    while (i < number_books) {
        cout << "enter title: " << endl;
        getline(cin, title);
        cout << "enter author: " << endl;
        getline(cin, author);
        cout << "enter genre: " << endl;
        getline(cin, genre);
        cout << "enter availability: " << endl;
        getline(cin, availability);
        output << id <<"\t"<< title << "\t" << author << "\t" << genre << "\t" << availability <<endl;
        i++;
        total_books++;
        id++;
    }
    cout << "New books added: " << number_books << endl;
    cout << "Total books in inventory: " << total_books << endl; 
}

void Book_Management::book_details() {
    string new_title, new_author, new_availability, new_genre;
    int option;
    string search_id; 

    fstream file;
    file.open("book.txt", ios::in | ios::out);

    if(file.is_open()) {
        cout << "Enter the ID of the book you want to update: ";
        cin >> search_id;
        cin.ignore();

        vector<string> lines; // vector size chande dynamically <data type>name vector
        //vector<int> y={752,7}
        //vector<int> y(5,7);
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }

        bool found = false;
        for (size_t i = 0; i < lines.size(); ++i) {
            string& old_line = lines[i];
            // Split the line to extract ID
            stringstream ss(old_line);
            string id_str;
            getline(ss, id_str, ' '); // Assuming ID is separated by a space
            if (id_str == search_id) { // found the book with the given ID
                found = true;
                cout << "What do you want to update?\n";
                cout << "1. Title\n2. Author\n3. Availability\n4. Genre\n";
                cin >> option;
                cin.ignore();

                switch(option) {
                    case 1:
                        cout << "Enter new title: ";
                        getline(cin, new_title);
                        old_line = search_id + " " + new_title + old_line.substr(old_line.find(" "));
                        break;
                    case 2:
                        cout << "Enter new author: ";
                        getline(cin, new_author);
                        old_line = old_line.substr(0, old_line.find("Author:") + 7) + new_author + " " + old_line.substr(old_line.find("Genre:"));
                        break;
                    case 3:
                        cout << "Enter new availability: ";
                        getline(cin, new_availability);
                        old_line = old_line.substr(0, old_line.find("Availability:") + 13) + new_availability + " " + old_line.substr(old_line.find("Genre:"));
                        break;
                    case 4:
                        cout << "Enter new genre: ";
                        getline(cin, new_genre);
                        old_line = old_line.substr(0, old_line.find("Genre:") + 6) + new_genre;
                        break;
                    default:
                        cout << "Invalid option\n";
                }
            }
        }

        if (!found) {
            cout << "Book not found\n";
        } else {
            file.close();
            file.open("book.txt", ios::out);
for (vector<string>::const_iterator it = lines.begin(); it != lines.end(); ++it) {// to read only const_iterator
    const string& updated_line = *it;
    file << updated_line << endl;
}
            cout << "Update successful\n";
        }
    } else {
        cout << "Unable to open file\n";
    }
    file.close();
}
void Book_Management::search_book() {
    int find_id;
    fstream file;
    file.open("book.txt", ios::in);

    cout << "Enter the ID you want to search for: ";
    cin >> find_id;

    if (file.is_open()) {
        string line;
        bool found = false;

        while (getline(file, line)) {
            stringstream ss(line);
            int id;
            string title, author, genre, availability;
            ss >> id >> title >> author >> genre >> availability;

            if (id == find_id) {
                cout << "Book found!\n";
                cout << "ID: " << id << endl;
                cout << "Title: " << title << endl;
                cout << "Author: " << author << endl;
                cout << "Genre: " << genre << endl;
                cout << "Availability: " << availability << endl;
                found = true;
                break; // No need to continue searching
            }
        }

        if (!found) {
            cout << "Book not found\n";
        }
    } else {
        cout << "Unable to open file\n";
    }
    file.close();
}


void Book_Management::remove_books() {
    int find_id;
    cout << "Enter the ID of the book you want to remove: ";
    cin >> find_id;

    fstream input, output;
    input.open("book.txt", ios::in);
    output.open("tempbook.txt", ios::out);

    if (!input || !output) {
        cout << "Error opening files\n";
        return;
    }

    string line;
    bool found = false;

    while (getline(input, line)) {
        stringstream ss(line);
        int id;
        string title, author, genre, availability;
        ss >> id >> title >> author >> genre >> availability;

        if (id == find_id) {
            found = true;
            continue; // Skip writing this line to output file
        }

        output << line << endl; // Write line to output file
    }

    input.close();
    output.close();

    if (!found) {
        cout << "Book with ID " << find_id << " not found\n";
        remove("tempbook.txt"); // Delete temporary file
    }

    // Remove the original file
    if (remove("book.txt") != 0) {
        cout << "Error deleting file\n";
       return;
    }

    // Rename temp file to original file name
    if (rename("tempbook.txt", "book.txt") != 0) {
        cout << "Error renaming file\n";
        return;
    }

    cout << "Book with ID " << find_id << " removed successfully\n";
}


void customer_Management::new_customer() {
    int numCustomers;
    cout << "Enter the number of new customers: ";
    cin >> numCustomers;

    ifstream lastIDFile("customer.txt");
    int lastID = 0;
    string line;

    while (getline(lastIDFile, line)) {
        if (!line.empty()) {
            stringstream ss(line);
            ss >> lastID;
        }
    }
    lastIDFile.close();

    for (int i = 0; i < numCustomers; ++i) {
        string fName, lName, Email, Membership;
        int Age;

        cout << "Please Enter Your first name: ";
        cin >> fName;
        cout << "Enter Your last name: ";
        cin >> lName;
        cout << "Email: ";
        cin >> Email;
        cout << "Membership: ";
        cin >> Membership;
        cout << "Age: ";
        cin >> Age;
        
        lastID++;

        ofstream outFile("customer.txt", ios::app);

        if (!outFile.is_open()) {
            cout << "Error opening file." << endl;
            return;
        }
        outFile << lastID << ". " << "Name: " << fName << " " << lName << ", "
                << "Email: " << Email << ", " << "Membership: " << Membership << ", " << "Age: " << Age << endl;

        outFile.close();

        cout << "New customer added successfully." << endl;
        cout << "The Total Of customers is : " << lastID << endl ;
        cout << "                     THANK YOU FOR GOINING HAVE A NICE DAY (;" <<endl;
    }
}
void customer_Management::update_customer_information() {
    int searchID;
    cout << "Enter the ID of the customer to modify: ";
    cin >> searchID;

    ifstream inFile("customer.txt");
    ofstream tempFile("temp.txt");

    if (!inFile.is_open() || !tempFile.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        stringstream ss(line);
        int id;
        ss >> id;

        if (id == searchID) {
            found = true;

            // Extract current customer information
            string fName, lName, Email, Membership;
            int Age;

            ss.ignore(1000, ':'); // Ignore "Name: " text
            ss >> fName >> lName;

            ss.ignore(1000, ':'); // Ignore "Email: " text
            ss >> Email;

            ss.ignore(1000, ':'); // Ignore "Membership: " text
            ss >> Membership;

            ss.ignore(1000, ':'); // Ignore "Age: " text
            ss >> Age;

            // Display current information
            cout << "Current Information:" << endl;
            cout << "1. Name: " << fName << " " << lName << endl;
            cout << "2. Email: " << Email << endl;
            cout << "3. Membership: " << Membership << endl;
            cout << "4. Age: " << Age << endl;

            // Menu for modification
            cout << "Select which information to modify (1-4), 0 to skip: ";
            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "Modify first name: ";
                    cin >> fName;
                    cout << "Modify last name: ";
                    cin >> lName;
                    break;
                case 2:
                    cout << "Modify Email: ";
                    cin >> Email;
                    break;
                case 3:
                    cout << "Modify Membership: ";
                    cin >> Membership;
                    break;
                case 4:
                    cout << "Modify Age: ";
                    cin >> Age;
                    break;
                default:
                    cout << "Skipping modification." << endl;
                    break;
            }

            // Write modified customer information to temp file
            tempFile << id << ". " << "Name: " << fName << " " << lName << ", "
                    << "Email: " << Email << ", " << "Membership: " << Membership << ", " << "Age: " << Age << endl;
        } else {
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    if (!found) {
        cout << "Customer with ID " << searchID << " not found." << endl;
        remove("temp.txt");
    } else {
        remove("customer.txt");
        rename("temp.txt", "customer.txt");
        cout << "Customer information modified successfully." << endl;
    }
}
void customer_Management::remove_customers() {
    int searchID;
    cout << "Enter the ID of the customer: ";
    cin >> searchID;

    ifstream inFile("customer.txt");
    ofstream tempFile("temp.txt");

    if (!inFile.is_open() || !tempFile.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        stringstream ss(line);
        int id;
        ss >> id;

        if (id == searchID) {
            found = true;

            string fName, lName, Email, Membership;
            int Age;

            ss.ignore(1000, ':');
            ss >> fName >> lName;

            ss.ignore(1000, ':');
            ss >> Email;

            ss.ignore(1000, ':');
            ss >> Membership;

            ss.ignore(1000, ':');
            ss >> Age;

            cout << "Current Information:" << endl;
            cout << "Name: " << fName << " " << lName << endl;
            cout << "Email: " << Email << endl;
            cout << "Membership: " << Membership << endl;
            cout << "Age: " << Age << endl;

            cout << "Select action for membership status:" << endl;
            cout << "1. Activate Membership" << endl;
            cout << "2. Deactivate Membership" << endl;
            int choice;
            cout << "Enter choice: ";
            cin >> choice;

            if (choice == 1) {
                Membership = "Active";
                cout << "Membership activated successfully." << endl;
            } else if (choice == 2) {
                Membership = "Inactive";
                cout << "Membership deactivated successfully." << endl;
            } else {
                cout << "Invalid choice. Membership status remains unchanged." << endl;
            }

            tempFile << id << ". " << "Name: " << fName << " " << lName << ", "
                    << "Email: " << Email << ", " << "Membership: " << Membership << ", " << "Age: " << Age << endl;
        } else {
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    if (!found) {
        cout << "Customer with ID " << searchID << " not found." << endl;
        remove("temp.txt");
    } else {
        remove("customer.txt");
        rename("temp.txt", "customer.txt");
    }
}

void findOverduePayment() {
    ifstream invoiceFile("phatora.txt");
    int id;
    string date;
    
    if (!invoiceFile) {
        cerr << "Error: Unable to open invoice file." << endl;
    
    }

    double overdueAmount = 0.0;
    string line;
    while (getline(invoiceFile, line)) {
        stringstream ss(line);
        int invoiceId;
        string invoiceDate;
        double amount;
        ss >> invoiceId >> invoiceDate >> amount;

        if (invoiceId == id && invoiceDate == date) {
            // Found a matching invoice
            overdueAmount = amount;
            cout << "ID: " << id << ", Date: " << date << " - Overdue payment found: $" << overdueAmount << endl;
            
            break;
        }
        else {
        cout << "No overdue payment found for ID " << id << " on date " << date << endl;
    }
    }

    invoiceFile.close();
  
}





	

