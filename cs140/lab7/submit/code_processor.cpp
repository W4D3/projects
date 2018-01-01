#include "code_processor.h"
#include <set>
#include <deque>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
using namespace std;

/*
   code_processor.cpp
   Mitchell Wade
   April 9, 2014

   This lab is the back end server of a rewards type program. It resembles
   mycokerewards and allows a user to add different users which keeps track
   of their points. The user can add points via phones and can have different
   phonenumbers as well. All of the prizes that can be redeemed from the amount
   of users points. If the user calls write the state of the program will be
   saved into a file in case of a system error.

*/

/* DJB Hash Function */
unsigned int djb_hash(string &s)
{
    int i;
    unsigned int h;
    
    h = 5381;
    
    for (i = 0; i < s.size(); i++) {
        h = (h << 5) + h + s[i];
    }
    
    return h;
}

int Code_Processor::New_Prize(string id, string description, int points, int quantity) {

    Prize *ptr; /* Pointer to a prize */
    
    /* Check for improper values */
    if ((quantity <= 0) || (points <= 0)) {
        return -1;
    }

    /* Check if the id is already in the map Prizes*/
    if (Prizes.find(id) != Prizes.end()) return -1;

    /* Create a new instance of the Prize class and set a ptr to it */
    ptr = new Prize();

    /* Put values in class using pointers */
    ptr->id=id;
    ptr->description=description;
    ptr->points=points;
    ptr->quantity = quantity;

    /* Insert the values the pointers point to into the Prizes map */
    Prizes.insert(make_pair(id,ptr));
    
    return 0;
}

int Code_Processor::New_User(string username, string realname, int starting_points) {

    User *ptr; /* Pointer to a User */

    /* Check for improper values */
    if (starting_points < 0) return -1;

    /* Check if the id is already in the map Names*/
    if (Names.find(username) != Names.end()) return -1;
    
    /* Create a new instance of the User class and set a ptr to it */
    ptr = new User();

    /* Put values in class using pointers */
    ptr->username=username;
    ptr->realname=realname;
    ptr->points=starting_points;

    /* Insert the values the pointers point to into the Names map */
    Names.insert(make_pair(username,ptr));

    return 0;
}

int Code_Processor::Delete_User(string username) {

    User *ptr;
    map <string, User *>::iterator mit;
    map <string, User *>::iterator pit;
    set <string>::iterator sit;

    /* Find the username if it exists */
    mit = Names.find(username);
    if (mit == Names.end()) {
        return -1;
    } else {
        
        ptr = mit->second;

        for (sit = ptr->phone_numbers.begin(); sit != ptr->phone_numbers.end(); sit++) {
            Phones.erase(*sit);
        }

        /* Dellocate memory */
        delete Names.find(username)->second;

        /* Erase the username */
        Names.erase(username);
    }

    return 0;
}

int Code_Processor::Add_Phone(string username, string phone) {

    User *ptr;  /* Pointer to a User */
    map <string, User *>::iterator uit;
    
    /* Check if the username is not in the map Names */
    if (Names.find(username) == Names.end()) return -1;

    /* Check if the phone is already in the map Phones */
    if (Phones.find(phone) != Phones.end()) return -1;

    /* Put the phonenumber in the set using pointers */
    uit = Names.find(username);
    uit->second->phone_numbers.insert(phone);

    /* Put the phonenumber in the map using insert/pointers */
    Phones.insert(make_pair(phone,uit->second));

    return 0;
}

int Code_Processor::Remove_Phone(string username, string phone) {

    /* Check if the username is not in the map Names */
    if (Names.find(username) == Names.end()) return -1;
    
    /* Check if the phonenumber is not in the map Phones */
    if (Phones.find(phone) == Phones.end()) return -1;

    /* Check if the phonenumber is not attributed to the correct person */
    if (Phones[phone]->username != username) return -1;

    /* Erase the phone number from map Phones*/
    Phones.erase(phone);

    /*Erase the phone number from the set */
    Names[username]->phone_numbers.erase(phone);

    return 0;
}

string Code_Processor::Show_Phones(string username) {
    
    User *ptr;
    set<string>::iterator sit;
    map <string, User *>::iterator nit;
    string s;

    /* Access map User */
    nit = Names.find(username);

    /* Check to see if the user doesn't exist */
    if (nit == Names.end()) return "BAD USER";
    
    ptr = nit->second;

    /* Print out all of the phonenumbers */
    for (sit = ptr->phone_numbers.begin(); sit != ptr->phone_numbers.end(); sit++){
        s += *sit + "\n";
    }

    return s;
}

int Code_Processor::Enter_Code(string username, string code) {

    set<string>::iterator sit;
    map<string, User *>::iterator nit;
    User *ptr;
    unsigned int check;

    /* Check to see if the user doesn't exist */
    nit = Names.find(username);
    if (nit == Names.end()) return -1;

    /* Check to see if the code has been entered */
    sit = Codes.find(code);
    if (sit != Codes.end()) return -1;

    /* Access map Used */
    ptr = nit->second;

    /* Add points and code to map Codes */
    check = djb_hash(code);
    if ((check%17) == 0){
        ptr->points += 10;
        Codes.insert(code);
        return 10;
    } else if ((check%13) == 0){
        ptr->points += 3;
        Codes.insert(code);
        return 3;
    }

    return 0;
}

int Code_Processor::Text_Code(string phone, string code) {

    set<string>::iterator sit;
    map<string, User *>::iterator nit;
    User *ptr;
    unsigned int check;

    /* Check to see if the user doesn't exist */
    nit = Phones.find(phone);
    if (nit == Phones.end()){
        return -1;
    }

    ptr = nit->second;

    /* Check to see if the code has been entered */
    sit = Codes.find(code);
    if (sit != Codes.end()){
        return -1;
    }

    ptr = nit->second;

    /* Add points and code to map Codes */
    check = djb_hash(code);
    if((check%17) == 0) {
        ptr->points += 10;
        Codes.insert(code);
        return 10;
    } else if ((check%13) == 0) {
        ptr->points += 3;
        Codes.insert(code);
        return 3;
    }

    return 0;
}

int Code_Processor::Mark_Code_Used(string code) {

    set<string>::iterator sit;
    unsigned int check;

    check = djb_hash(code);

    /* Check if code is valid */
    if ((check%17) != 0 && (check%13) != 0) return -1;

    /* Check if code is already entered */
    sit = Codes.find(code);
    if (sit != Codes.end()) return -1;

    /* Add the code to map Codes */
    Codes.insert(code);

    return 0;
}

int Code_Processor::Balance(string username) {
    
    map <string, User *>::iterator nit;
    User *ptr;
 
    /* Check to see if the user doesn't exist */
    nit = Names.find(username);
    if (nit == Names.end()) {
        return -1;
    }

    /* Access map User */
    ptr = nit->second;

    /* Return the balance of points */
    return ptr->points;
}

int Code_Processor::Redeem_Prize(string username, string prize) {

    map <string, User *>::iterator nit;
    map <string, Prize *>::iterator pit;
    User *ptr;
    Prize *ptrPrize;

    /* Check to see if the user doesn't exist */
    nit = Names.find(username);
    if (nit == Names.end()) return -1;

    /* Check to see if the prize doesn't exists */
    pit = Prizes.find(prize);
    if (pit == Prizes.end()) return -1;

    /* Check to see if the user doesn't have enough points */
    ptr = nit->second;
    ptrPrize = pit->second;
    if (ptr->points < ptrPrize->points) return -1;

    /* Reedem the prize */
    ptr->points -= ptrPrize->points;
    ptrPrize->quantity -= 1;

    if (ptrPrize->quantity == 0){
        delete ptrPrize;
        Prizes.erase(prize);
    }

    return 0;
}

Code_Processor::~Code_Processor() {

    map<string, User *>::iterator mit;
    map<string, Prize *>::iterator pit;

    for (mit = Names.begin(); mit != Names.end(); mit++) {
        delete mit->second;
    }

    for (pit =Prizes.begin(); pit != Prizes.end(); pit++) {
        delete pit->second;
    }

}

int Code_Processor::Write(const char *file) {

    ofstream f;                             /* Output File */
    map <string, Prize *>::iterator nit;    /* Prizes Iterator */
    map <string, User *>::iterator uit;     /* Names Iterator */
    set <string>::iterator cit;             /* Codes Iterator */

    /* Open the file */
    f.open(file);

    /* Check to see if the file failed to open */
    if(f.fail()) return -1;

    /* Write t  file all entries in the Prizes map */
    for (nit = Prizes.begin(); nit != Prizes.end(); nit++) {
        f << "PRIZE " << nit->first << " " << nit->second->points << " " 
            << nit->second->quantity << " " << nit->second->description <<endl;
    }

    /* Write to file all entries in the Names map */
    for (uit = Names.begin(); uit != Names.end(); uit++) {
        f << "ADD_USER " << uit->first << " " << uit->second->points << " " 
            << uit->second->realname <<endl;
    }

    /* Write to file all entries in the Phones map */
    for (uit = Phones.begin(); uit != Phones.end(); uit++) {
        f << "ADD_PHONE " << uit->second->username << " " << uit->first <<endl;
    }

    /* Print out all entries in the Codes map */
    for (cit = Codes.begin(); cit != Codes.end(); cit++) {
        f << "MARK_USED " << *cit <<endl;
    }

    /* Close the file */
    f.close();

    return 0;
}
