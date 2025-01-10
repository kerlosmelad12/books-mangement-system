#include<iostream>
#include<string>
#include<fstream>
#include <sstream>
using namespace std;
class customer_Management{
	private:
		string Name;
		string Email;
		string Membership;
		int id;
		int Age;
	public:
		int total_customer;
		void new_customer();
		void update_customer_information();
		void remove_customers();	
	
};
class Book_Management{
	private:
		int books_number;
		string title, author, genre,  availability;
		int total_books=29;
	public:
       void new_book();
       void book_details();
       void remove_books();
       void search_book();
       
};
class Transaction_Management{
	public:
		void due_dates();
		
	
};
