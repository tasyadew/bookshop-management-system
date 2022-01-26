//This is the implementation file for main.cpp

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>
#include "users.h"

using namespace std;


/**********CLASS USER**********/

//default constructor
User::User(){
    type = 0;
    age = 0;
    username = "";
    password = "";
    email = "";
    phone = "";
    name = "";
}

//constructor with user's attributes
User::User(int type, string username, string password, int age, string email, string phone, string name){
    this->type = type;
    this->username = username;
    this->password = password;
    this->age = age;
    this->email = email;
    this->phone = phone;
    this->name = name;
}

//return true if username, password and type are all same
bool User::verify(string username, string password, int type){
    return (this->username == username && this->password == password && this->type == type);
}

//display user detail
void User::userDetails(){
    cout<< setw(20) << username
        << setw(18) << email
        << setw(14) << phone
        << name;
}



/**********CLASS LISTUSER**********/

//initialized the first user node
void ListUser::insertUser_head(int type, string username, string password, int age, string email, string phone, string name){
    headUser = new User(type, username, password, age, email, phone, name); //create a node
    headUser->next = NULL;
}

//linked list insert at the end
void ListUser::insertUser_end(int type, string username, string password, int age, string email, string phone, string name){
    User* currentUser = headUser;
    while(currentUser->next != NULL){
        currentUser = currentUser->next;
    }

    User* tempUser = new User(type, username, password, age, email, phone, name);
    tempUser->next = NULL;
    currentUser->next = tempUser;
}

//Return the total user in the linked list
int ListUser::getLength(){
    User* currentUser = headUser;
    int numUser = 0;
    while(currentUser != NULL){
        numUser++;
        currentUser = currentUser->next;
    }
    return numUser;
}

//return user data at the choosen position
User* ListUser::getUser(int position){
    User* currentUser = headUser;
    for(int i = 0; i < position; i++){
        currentUser = currentUser->next;
    }
    return currentUser;
}

//searching user to be deleted by their username
void ListUser::deleteUser(string username){
    User* currentUser = headUser;
    User* prevUser = NULL;

    //loop if current user is not null and not found same username
    while(currentUser && currentUser->username != username){
        prevUser = currentUser;
        currentUser = currentUser->next;
    }

    //if current user is not null (found same username)
    if(currentUser){
        if(prevUser){   //if prev user not null 
            prevUser->next = currentUser->next;
            delete currentUser;
        }
        else{ //current user is the headUser
            headUser = currentUser->next;
            delete currentUser;
        }
        cout<< "The user has been deleted from user database!" << endl << endl;
    }else{ 
        //if current user is null (no matching username)
        cout<< "ERROR! No matching username. Cannot delete the user" << endl << endl;
    }

}



/**********CLASS REGISTRATION**********/

///remove whitespace at front of string when getline
string Registration::formatTitle(string inputStr){
    int i = 0;
    while (inputStr[i] == ' ')
        i++;
    
    string  outputStr = inputStr.substr(i);
    return outputStr;
}

//read from users.txt file
void Registration::importUsers(){
    fstream infileUsers("users.txt", ios::in);
    
    //checking if file can correctly open
    if(infileUsers.fail()){
        cout << "ERROR: Cannot open file users.txt " << endl;
    }else{
        //to skip header in text file
        string skipLine;
        infileUsers.seekg(0, ios::beg); //Go to the first line
        getline(infileUsers, skipLine); //Skips the first line

        //to insert the first user as head user
        int type, age;
        string username, password, email, phone, name;
        
        infileUsers >> type;
        infileUsers >> username;
        infileUsers >> password;
        infileUsers >> age;
        infileUsers >> email;
        infileUsers >> phone;
        getline(infileUsers, name);
        name = formatTitle(name);   
        listUser.insertUser_head(type, username, password, age, email, phone, name);

        //to insert the user after user head is declared
        while (!infileUsers.eof()){
            infileUsers >> type;
            infileUsers >> username;
            infileUsers >> password;
            infileUsers >> age;
            infileUsers >> email;
            infileUsers >> phone;
            getline(infileUsers, name);
            name = formatTitle(name);
            
            listUser.insertUser_end(type, username, password, age, email, phone, name);
        }
    }
}

//write to users.txt file
void Registration::exportUsers(){
    fstream outfileUsers("users.txt", ios::out);
    
    //checking if file can correctly open
    if(outfileUsers.fail()){
        cout << "ERROR: Cannot open file users.txt" << endl;
    }
    
    outfileUsers << "Type Username            Password       Age     Email             Phone         Name";
    for (int i=0; i < listUser.getLength(); i++){
        User* currentUser = listUser.getUser(i);
        outfileUsers<< left << endl
                    << setw(5) << currentUser->type
                    << setw(20) << currentUser->username
                    << setw(15) << currentUser->password
                    << setw(8) << currentUser->age
                    << setw(18) << currentUser->email
                    << setw(14) << currentUser->phone
                    << currentUser->name;
    }
}

//user cannot have the same username & length must be between 3-15
bool Registration::validUsername(string& username){
    //username legth constraint
    if(username.length() < 3 || username.length() > 15){
        cout<< "Invalid username! Username length must be between 3 to 15 characters" << endl
            << "Please enter your username again." << endl
            << endl;
        return false;
    }

    //no similar username
    for(int i = 0; i < listUser.getLength(); i++){
        User* currentUser = listUser.getUser(i);
        if(username == currentUser->username){
        cout<< "Invalid username! The username is already taken." << endl
            << "Please enter your username again." << endl
            << endl;
        return false;                    
        }
    }
    return true;
}

//add new user and put at the end of linked list
void Registration::newUser(int type){
    bool verified = false;
    int age;
    string username, password, email, phone, name;

    cout<< "Please enter your account details" << endl;

    //username input
    do{
        cout<< "Username : ";
        cin >> username;
        verified = validUsername(username);
    }while(!verified);
    
    //Password input
    verified = false;
    do{
        cout<< "Password : ";
        cin >> password;
        if(password.length() <= 12){
            verified = true;
        }else{
            cout<< "Invalid password! Password length must not exceed 12 characters" << endl
                << "Please enter your password again" << endl
                << endl;
        }
    }while(!verified);

    //email input
    verified = false;
    do{
        cout<< "Email    : ";
        cin >> email;
        if(email.length() <= 15){
            verified = true;
        }else{
            cout<< "Invalid email! Email length must not exceed 15 characters" << endl
                << "Please enter your email again" << endl
                << endl;
        }
    }while(!verified);

    //phone number input
    verified = false;
    do{
        cout<< "Phone No : ";
        cin >> phone;
        if(phone.length() <= 10){
            verified = true;
        }else{
            cout<< "Invalid phone number! Phone number length must not exceed 10 digits" << endl
                << "Please enter your phone number again" << endl
                << endl;
        }
    }while(!verified);

    //full name input
    cout<< "Full Name: ";
    cin.ignore();
    getline(cin,name);

    //age input
    verified = false;
    do{
        cout<< "Age      : ";
        cin >> age;
        if(cin.good() && age >= 1 && age <= 99){
            verified = true;
        }else{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<< "Invalid age! Age must be an a number between 1 to 99" << endl
                << "Please enter your age again" << endl
                << endl;
        }
    }while(!verified);

    cout<< endl
        << "Account successfully created!" << endl;

    listUser.insertUser_end(type, username, password, age, email, phone, name);
    exportUsers();
}

//delete the selected user from the linked list
void Registration::removeUser(){
    string input_username;
    cout<< "Enter the username of the user to be removed from the user database :";
    cin >> input_username;

    listUser.deleteUser(input_username);
    exportUsers();
}

//return true if type, username and password of user are all same
//by using sequential search
bool Registration::foundUserAcc(int type, string username, string password){
    bool found = false;
    
    if (type == 0){
        for (int i=0; i<listUser.getLength(); i++){
            if (listUser.getUser(i)->verify(username, password, type)){
                found = true;
            }
        }
    } else if (type == 1){
        for (int i=0; i<listUser.getLength(); i++){
            if (listUser.getUser(i)->verify(username, password, type)){
                found = true;
            }
        }
    }
    return found;
}

//verify user login
void Registration::verifyUser(int &subchoice, int type){
    string username, password;
    for (int i=0; i<3; i++){
        cout<< "Please enter username and password" << endl
            << "Username: ";
        cin >> username;
        cout<< "Password: ";
        cin >> password;
        cout<< endl;
        
        if (foundUserAcc(type, username, password)){
            subchoice = 0;
            i = 3;
            cout<< "Logged in successfully!" << endl;
        } else {
            if (i<2){
                cout<< "Wrong username or password! (Attempts remaining: " << 2-i << ")" << endl;
            } else {
                cout<< "Wrong username or password! Please try again later!" << endl;
            }
        }
    }
}

//display linked list user
void Registration::displayUserInfo(){
    //header
    cout<< left << string(70, '=') << endl
        << setw(20) << "Username"
        << setw(18) << "Email"
        << setw(14) << "Phone"
        << "Name" << endl
        << string(70, '=') << endl
        << "CUSTOMER INFO" << endl << endl;

    for (int i = 0; i < listUser.getLength(); i++){
        if(listUser.getUser(i)->type == 0){
            listUser.getUser(i)->userDetails();
            cout << endl;
        }
    }
    
    cout<< string(70, '=') << endl
        << "STAFF INFO" << endl << endl;
    for (int i = 0; i < listUser.getLength(); i++){
        if(listUser.getUser(i)->type == 1){
            listUser.getUser(i)->userDetails();
            cout << endl;
        }
    }
    cout<< string(70, '=') << endl;            
}