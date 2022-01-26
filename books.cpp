//This is the implementation file for main.cpp

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>
#include "books.h"

using namespace std;

//global var
#define MAX_BOOKS 20
#define MAX_CART 5
#define MAX_QUEUE 5


/**********CLASS BOOK**********/

//default constructor
Book::Book(){
    id = 0;
    isbn = 0;
    quantity = 0;
    price = 0;
    discount = 0;
    author = "";
    title = "";
}

//constructor with book's attribute
Book::Book(int id, long long int isbn, int quantity, float price, int discount, string author, string title){
    this->id = id;
    this->isbn = isbn;
    this->quantity = quantity;
    this->price = price;
    this->discount = discount;
    this->author = author;
    this->title = title;
}

//constructor for suggest book attributes
Book::Book(string title, string author){
    this->title = title;
    this->author = author;
}

//for single line book data
void Book::bookDetails(){
    cout << left << "[" << setw(2) << id << "] " 
    << setw(30) << title 
    << setw(10) << quantity 
    << setw(10) << fixed << showpoint << setprecision(2) << price 
    << setw(10) << noshowpoint << discount;   
}

//for multi line book data
void Book::bookInfo(){
    cout << "Title        : " << title << endl;
    cout << "Author       : " << author << endl;
    cout << "ISBN         : " << isbn << endl;
    cout << "Price        : RM " << showpoint << setprecision(2) << price << endl;
    cout << "Discount     : " << noshowpoint << discount << "%" << endl;
}

//mutator
void Book::setQuantity(int quantity){
    this->quantity = quantity;
}

//copy book attribute from book reference
void Book::copyData(Book* right){
    this->id = right->id;
    this->isbn = right->isbn;
    this->quantity = right->quantity;
    this->price = right->price;
    this->discount = right->discount;
    this->author = right->author;
    this->title = right->title;
}



/**********CLASS LISTBOOK**********/

//default constructor
QueueBook::QueueBook() {
    frontBook = -1;
    rearBook = -1;
}

// Check if the queue is full
bool QueueBook::isFull() {
    //if nevwer dequeue
    if (frontBook == 0 && rearBook == MAX_QUEUE - 1)
        return true;

    //if have dequeue before
    if (frontBook == rearBook + 1)
        return true;

    return false;
}

// Check if the queue is empty
bool QueueBook::isEmpty() {
    if (frontBook == -1) 
        return true;
    else             
        return false;
}

// Adding an book to queue
void QueueBook::enQueue(Book newBook) {
    if (isFull()) {
        cout << "Queue is full"<<endl;
    } else {
        if (frontBook == -1) frontBook = 0;
        rearBook = (rearBook + 1) % MAX_QUEUE;
        suggestedBook[rearBook] = newBook;
    }
}

// Removing a book
Book QueueBook::deQueue() {
    Book newBook;
    if (isEmpty()) {
        cout << "Queue is empty" << endl;
    } else {
        newBook = suggestedBook[frontBook];
        if (frontBook == rearBook) {
            frontBook = -1;
            rearBook = -1;
        }
        else {
            frontBook = (frontBook + 1) % MAX_QUEUE;
        }
        return (newBook);
    }
}

//return the front of queue without dequeue
Book QueueBook::peek() {
    return suggestedBook[frontBook];
}



/**********CLASS PAYMENTSYSTEM**********/

//return true if payment enough
bool PaymentSystem::verifyPayment(){
    if (userPay >= price) 
        return true;
    else
        return false;
}

//set payment and price to 0
void PaymentSystem::reset(){
    userPay = 0;
    price = 0;
}

//return updated payment made from user
float PaymentSystem::updatePayment(float addPay){
    return userPay+=addPay;
}

//return updated price to calculate total price
float PaymentSystem::updatePrice(float addPrice){
    return price+=addPrice;
}

//return additional payment because payment not enough
float PaymentSystem::calcAddPayment(){
    return price - userPay;
}

//return balance
float PaymentSystem::calcBalance(){
    return userPay - price;
}

//Accessors
float PaymentSystem::getUserPay(){return userPay;}
float PaymentSystem::getPrice()  {return price;}



/**********CLASS CART**********/

//initialized cart with 0 book
void Cart::emptyCart(){
    top = -1;
}

//insert Book in cart to top of stack
void Cart::push(Book book){
    //check if cart is full
    if(isFull()){
        cout << "Sorry, cannot add more books! Please checkout first or remove recently added books in cart." << endl;
    }

    //push book into cart
    else{
        top++;
        cartBook[top] = book;
    }
}

//delete book from top of stack
void Cart::pop(){
    //book in cart is not empty
    if (!isEmpty())
        top--;
    else
        cout<< "Cart empty!" << endl;
}

//return the Book data at top position
Book Cart::bookAtTop(){
    return cartBook[top];
}

//return the Book data at "i" position
Book Cart::bookAt(int i){
    return cartBook[i];
}

//check if cart is full
bool Cart::isFull(){
    return (top == MAX_CART-1);
}

//check if cart is empty
bool Cart::isEmpty(){
    return (top == -1);
}

//return size of cart
int Cart::size(){
    return top;
}



/**********CLASS STOCK MANAGEMENT**********/

//remove whitespace at front of string when getline
string StockManagement::formatTitle(string inputStr){
    int i = 0;
    while (inputStr[i] == ' ')
        i++;
    
    string  outputStr = inputStr.substr(i);
    return outputStr;
}

//read from books.txt file
void StockManagement::importBooks(){
    fstream infileBooks("books.txt", ios::in);
    
    //checking if file can correctly open
    if(infileBooks.fail()){
        cout << "ERROR: Cannot open file books.txt" << endl;
    }else{
        //to skip header in text file
        string skipLine;
        infileBooks.seekg(0, ios::beg); //Go to the first line
        getline(infileBooks, skipLine); //Skips the first line
        
        int id, quantity, discount;
        long long int isbn;
        string title, author;
        float price;
        bookIndex = 0;
        while (!infileBooks.eof() && bookIndex<MAX_BOOKS){
            infileBooks >> id;
            infileBooks >> isbn;
            infileBooks >> quantity;
            infileBooks >> price;
            infileBooks >> discount;
            infileBooks >> author;
            getline(infileBooks, title);
            title = formatTitle(title);
            
            listBook[bookIndex] = new Book(id, isbn, quantity, price, discount, author, title);
            bookIndex++;
        }
    }
}

//write to books.txt file
void StockManagement::exportBooks(){
    fstream outfileBooks("books.txt", ios::out);
    
    outfileBooks << "ID  ISBN           Quantity  Price   Discount  Author              Title";
    for (int i=0; i < bookIndex; i++){
        outfileBooks<< left << endl
                    << setw(4) << listBook[i]->id
                    << setw(15) << listBook[i]->isbn
                    << setw(10) << listBook[i]->quantity
                    << setprecision(2) << showpoint << fixed << setw(8) << listBook[i]->price
                    << setw(10) << listBook[i]->discount
                    << setw(20) << listBook[i]->author
                    << listBook[i]->title;
    }
}

//single line display
void StockManagement::displayBooks(){
    //header
    cout<< left << setw(5) << "ID"
        << setw(30) << "Title"
        << setw(10) << "Quantity"
        << setw(10) << "Price(RM)"
        << setw(10) << "Discount" << endl;
    for (int i = 0; i < bookIndex; i++){
        listBook[i]->bookDetails();
        cout << endl;
    }
}

//multi line display
void StockManagement::displayBookInfo(int i){
    cout<< "Book Info:" << endl;
    listBook[i]->bookInfo();
    cout<< endl;
}

//Accessors
int StockManagement::getBookIndex()        {return bookIndex;}
string StockManagement::getBookTitle(int i){return listBook[i]->title;}
int StockManagement::getBookQuantity(int i){return listBook[i]->quantity;} 
int StockManagement::getBookDiscount(int i){return listBook[i]->discount;}

//return true if cart is empty
bool StockManagement::isCartEmpty(){
    return cart.isEmpty();
}

//display cart
void StockManagement::displayCart(){
    //header
    cout<< "List of book(s) in your cart" << endl
        << left << setw(5) << "ID"
        << setw(30) << "Title"
        << setw(10) << "Quantity"
        << setw(10) << "Price(RM)"
        << setw(10) << "Discount" << endl;
    
    //display book details in cart
    for (int i = 0; i <= cart.size(); i++){
        cart.bookAt(i).bookDetails();
        cout << endl;
    }

    //display most recently added book
    cout<< endl 
        << "Most recently added book: " << cart.bookAtTop().quantity 
        << " copies of \"" << cart.bookAtTop().title << "\"" << endl
        << endl;
}

//add book to cart by push into cart stack
void StockManagement::addToCart(int i){
    //exit if book out of stock
    if (listBook[i]->quantity == 0){
        cout<< "Sorry! The chosen book is out of stock!" << endl;
    }
    else{
        cout<< "Enter quantity: ";
        cin >> quantity;
        
        //verify quantity
        while(quantity > listBook[i]->quantity){
            cout<< endl 
                << "Sorry! Not enough stock. Please enter quantity less or equal to " << listBook[i]->quantity << endl
                << "Enter quantity: ";
            cin >> quantity;
            cout<< endl;
        }
        
        //push book into cart
        Book temp;
        temp.copyData(listBook[i]);
        temp.setQuantity(quantity);
        cart.push(temp);
        listBook[i]->quantity -= quantity;
        
        if(!cart.isFull()){
            cout << "A total of " << quantity << " copies of \"" << listBook[i]->title << "\" has been added to your cart!\n";
        }
    }
}

//clear book in cart and clear payment
void StockManagement::resetCart(){
    for (int i=0; i <= cart.size(); i++){
        for (int j=0; j < bookIndex; j++){
            if (cart.bookAt(i).id == listBook[j]->id){
                listBook[j]->quantity += cart.bookAt(i).quantity;
            }
        }
    }
    cart.emptyCart();
    ps.reset();
}

//purchase books that is in cart
void StockManagement::checkout(){
    //calculate total payment need to be made
    float total = 0;
    for (int i = 0; i <= cart.size(); i++){
        //total price without discount
        //newTotal = price x quantity
        total += cart.bookAt(i).price * cart.bookAt(i).quantity;

        //total price with discount
        //newTotal = price x quantity x (1-discount/100)
        float newTotal = cart.bookAt(i).price * cart.bookAt(i).quantity * (1.0-(cart.bookAt(i).discount/100.0));
        ps.updatePrice(newTotal);
    }
    
    //display payment need to be made
    cout<< endl
        << "Total price of books       : RM" << total << endl
        << "Total price after discount : RM" << ps.getPrice() << endl
        << endl;
    
    //verify if payment made is enough or not
    float payment = 0;
    while (!ps.verifyPayment()){
        cout<< "Please enter payment of RM" << ps.calcAddPayment() << endl
            << "Payment : RM";
        cin >> payment;
        
        ps.updatePayment(payment);
        //payment not enough
        if (!ps.verifyPayment()){
            cout<< endl
                << "Payment not enough! ";
        } else {
            //payment enough
            cout<< endl
                << "The balance is RM" << ps.calcBalance() << endl;
            exportReport();
            cart.emptyCart();
            ps.reset();
        }
    }
}

//remove recently added book
void StockManagement::removeBook(){
    //display output
    cout<< endl
        << "Removed " << cart.bookAtTop().quantity 
        << " copies of \"" << cart.bookAtTop().title << "\" from your cart" << endl
        << endl;

    //restock quantity of book from cart
    for (int j=0; j < bookIndex; j++){
        if (cart.bookAtTop().id == listBook[j]->id){
            listBook[j]->quantity += cart.bookAtTop().quantity;
        }
    }
    
    //remove book
    cart.pop();
}

//read from report.txt if exist, else create report.txt
void StockManagement::importReport(){
    //checking if file can correctly open
    fstream checkReport("report.txt");
    if(!checkReport){
        //File not found, creating new one
        fstream createReport("report.txt", ios::app);
        createReport<< "No  Title                         Quantity  SoldPrice   TotalSales" << endl
                    << "GrandTotal: 0.00    ";
    }
    
    fstream report("report.txt");
    report.seekg(-8L, report.end);
    
    report >> totalSales;
}

//write to report.txt
void StockManagement::exportReport(){
    fstream report("report.txt");
    report.seekg(-22L, report.end); //Replaces GrandTotal
    
    report  << endl <<  string(64, '-');
    
    for (int i=0; i < cart.size(); i++){
        float soldPrice = cart.bookAt(i).price * cart.bookAt(i).quantity * (1.0-(cart.bookAt(i).discount/100.0));
        totalSales += soldPrice;
        report  << left << endl
                << setw(4) << i+1
                << setw(30) << cart.bookAt(i).title
                << setw(10) << cart.bookAt(i).quantity
                << setprecision(2) << showpoint << fixed 
                << setw(12) << soldPrice
                << totalSales;
    }
    report  << endl
            << "GrandTotal: RM" << setprecision(2) << showpoint << fixed << setw(8) << left << totalSales;
}

//read from report.txt to display output of report
void StockManagement::displayReport(){
    fstream report("report.txt", ios::in);
    string line = "";
    while (!report.eof()){
        getline(report, line);
        cout << line << endl;
    }
    cout << endl;
}

//using insertion sort to sort by book price (if true = ascending, else descending)
void StockManagement::sortByPrice(bool ascending){
    Book* temp = new Book;
    int pass, insertIndex;
    for(pass = 1; pass < bookIndex; pass++){
        temp->copyData(listBook[pass]);
        insertIndex = pass;
        
        if (ascending){
            while((insertIndex > 0) && (listBook[insertIndex-1]->price > temp->price)){
                listBook[insertIndex]->copyData(listBook[insertIndex-1]);
                insertIndex--;
            }
        } else {
            while((insertIndex > 0) && (listBook[insertIndex-1]->price < temp->price)){
                listBook[insertIndex]->copyData(listBook[insertIndex-1]);
                insertIndex--;
            }
        }

        listBook[insertIndex]->copyData(temp);
    }
}

//using insertion sort to sort by book title (ascending)
void StockManagement::sortByTitle(){
    Book* temp = new Book;
    int pass, insertIndex;
    for(pass = 1; pass < bookIndex; pass++){
        temp->copyData(listBook[pass]);
        insertIndex = pass;
        while((insertIndex > 0) && (listBook[insertIndex-1]->title > temp->title)){
            listBook[insertIndex]->copyData(listBook[insertIndex-1]);
            insertIndex--;
        }
        listBook[insertIndex]->copyData(temp);
    }
}

//using insertion sort to sort by book id (ascending)
void StockManagement::sortByID(){
    Book* temp = new Book;
    int pass, insertIndex;
    for(pass = 1; pass < bookIndex; pass++){
        temp->copyData(listBook[pass]);
        insertIndex = pass;
        while((insertIndex > 0) && (listBook[insertIndex-1]->id > temp->id)){
            listBook[insertIndex]->copyData(listBook[insertIndex-1]);
            insertIndex--;
        }
        listBook[insertIndex]->copyData(temp);
    }
}

//using insertion sort to sort by book isbn (ascending)
void StockManagement::sortByISBN(){
    Book* temp = new Book;
    int pass, insertIndex;
    for(pass = 1; pass < bookIndex; pass++){
        temp->copyData(listBook[pass]);
        insertIndex = pass;
        while((insertIndex > 0) && (listBook[insertIndex-1]->isbn > temp->isbn)){
            listBook[insertIndex]->copyData(listBook[insertIndex-1]);
            insertIndex--;
        }
        listBook[insertIndex]->copyData(temp);
    }
}

//using sequential search to search matching book id
int StockManagement::findPosByID(int bookId){
    int pos = -1;
    for (int i=0; i<bookIndex; i++){
        if (listBook[i]->id == bookId){
            pos = i;
            i = bookIndex;
        }
    }
    return pos;
}

//using binary search to search matching book isbn
int StockManagement::findPosByISBN(long long int bookISBN, int first, int last){
    int middle = (first+last)/2;
    int pos = -1;
    
    if (listBook[middle]->isbn == bookISBN){
        pos = middle;
    } else {
        if (middle == first){
            if (listBook[last]->isbn == bookISBN) pos = last;
            else                                  pos = -1; //Not Found
        }
        else if (listBook[middle]->isbn > bookISBN){
            pos = findPosByISBN(bookISBN, first, middle);
        } else {
            pos = findPosByISBN(bookISBN, middle, last);
        }
    }
    return pos;
}  

//update quantity of selected book
void StockManagement::updateQuantity(int i, int newQ){
    listBook[i]->setQuantity(newQ);
}

//update discount of selected book
void StockManagement::updateDiscount(int i, int newD){
    listBook[i]->discount = newD;
}

//add book suggestion to the queue
void StockManagement::addSuggestedBook(){
    if(q.isFull()){
        cout<< "Sorry! We have a lot of suggested books to be reviewed." << endl
            << "Please try again later!" << endl;
    }else{
        string title, author;
        cout<< endl
            << "====================SUGGEST A BOOK====================" << endl
            << "Thank you for your interest in suggesting a book" << endl
            << "to be added in this BookShop App" << endl
            << "Please enter the book title and author of the book" << endl
            << "that you are interested to buy from this app" << endl
            << "======================================================" << endl
            << endl
            << "Enter Book's Title   : ";
        cin.ignore();
        getline(cin, title);
        cout<< "Enter Book's Author  : ";
        cin >> author;

        Book temp(title, author);
        q.enQueue(temp);

        cout<< "We have received your suggested book! Please wait for our staff to review first." <<endl;
    }
}

//remove the first book suggested in the queue
void StockManagement::reviewSuggestedBook(){
    if(q.isEmpty()){
        cout<< "No suggested book to be review!" << endl;
    }else{
        bool validChar = false;
        char input;
        cout<< "====================SUGGESTED BOOKS===================" << endl
            << "Please review the following book if it is" << endl
            << "appropiate to be added to the bookshop system" << endl
            << endl
            << "To approve the suggested book, enter [Y]" << endl
            << "To reject  the suggested book, enter [N]" << endl
            << "======================================================" << endl
            << endl
            << "Suggested Book : " << q.peek().title << " by " << q.peek().author << endl
            << endl
            << "Is this suggested book appropiate to be added? : ";
            cin >> input;

        validChar = (input == 'Y' || input =='y' || input =='n' || input =='N');
        while(!cin.good() || !validChar){
            cout<< endl
                << "Invalid input! Enter [Y] to approve or [N] to reject" << endl
                << "Is this suggested book appropiate to be added? : ";
            cin >> input;
            validChar = (input == 'Y' || input =='y' || input =='n' || input =='N');
        }

        q.deQueue();

        if(input == 'y' || input == 'Y'){
            cout<< "The book is accepted" << endl;
        }

        if(input == 'n' || input == 'N'){
            cout<< "The book is rejected" << endl;
        }
    }
}