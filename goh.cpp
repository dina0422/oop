#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

class SellerInfo{
private:
    string username, password;
public:
    void set_seller_info(string name, string pass){
        username = name;
        password = pass;
    }

    string get_username() const {
        return username;
    }

    string get_password() const {
        return password;
    }
};

class ShopItem{
private:
    int item_id, num_unit;
    float price;
    string item_name, company_name;
public:
    ShopItem(): item_id(0), num_unit(0), price(0), item_name(""), company_name("")
    {}

    void set_item_id(const int _itemID){
        item_id = _itemID;
    }

    void set_num_unit(const int _numUNIT){
        num_unit = _numUNIT;
    }

    void set_price(const float _price){
        price = _price;
    }

    void set_item_name(const string _itemNAME){
        item_name = _itemNAME;
    }

    void set_company_name(const string _companynNAME){
        company_name = _companynNAME;
    }

    int get_item_id() const{
        return item_id;
    }

    int get_num_unit() const{
        return num_unit;
    }

    float get_price() const{
        return price;
    }

    string get_item_name() const{
        return item_name;
    }

    string get_company_name() const{
        return company_name;
    }

    virtual string get_ItemType() const {
        return "No item type id define.";
    }

    virtual string get_ItemData() const {
        return "No description";
    }
    virtual void display_item(){
        cout << "No item to display!\n";
    }
};

class Book : public ShopItem{
private:
    string author_name;
public:
    Book(int _itemID, int _numUNIT, float _price, string _itemNAME, string _companyNAME, string _authorNAME): author_name(_authorNAME)
    {
        set_item_id(_itemID);
        set_num_unit(_numUNIT);
        set_price(_price);
        set_item_name(_itemNAME);
        set_company_name(_companyNAME);
    }

    void display_item(){
        cout << setw(10) << "Item: " << get_item_id() << " | " << setw(10) << author_name << endl;
    }

    string get_ItemType() const {
        return "Book";
    }

    string get_ItemData() const {
        return author_name;
    }
};

class Magazine : public ShopItem{
private:
    string date;
public:
    Magazine(int _itemID, int _numUNIT, float _price, string _itemNAME, string _companyNAME, string _date): date(_date)
    {
        set_item_id(_itemID);
        set_num_unit(_numUNIT);
        set_price(_price);
        set_item_name(_itemNAME);
        set_company_name(_companyNAME);
    }

    void display_item(){
        cout << setw(10) << "Item: " << get_item_id() << " | " << setw(10) << date << endl;
    }

    string get_ItemType() const {
        return "Magazine";
    }

    string get_ItemData() const {
        return date;
    }
};

class Movie : public ShopItem {
private:
    string actor_name;
public:
    Movie(int _itemID, int _numUNIT, float _price, string _itemNAME, string _companyNAME, string _actorNAME) : actor_name(_actorNAME) {
        set_item_id(_itemID);
        set_num_unit(_numUNIT);
        set_price(_price);
        set_item_name(_itemNAME);
        set_company_name(_companyNAME);
    }

    void display_item(){
        cout << "Item: " << get_item_id()  << setw(10) << " | " << actor_name << endl;
    }

    string get_ItemType() const {
        return "Movie";
    }

    string get_ItemData() const {
        return actor_name;
    }
};

bool check_validation(string username, string password, SellerInfo sellerInfo);
void load_shop_item(ShopItem *shopItem[], int &_itemCount);
void update_item(ShopItem *shopItem[], int _itemID);
void delete_item(ShopItem *shopItem[], int _itemID, int &itemCount);
void insert_item(ShopItem *shopItem[], int &_itemCount);
int findSmallestValue(ShopItem *shopItem[], int _itemCount);
void sortArrayByID(ShopItem *shopItem[], int _itemCount);
void saveItemList(ShopItem *shopItem[], int itemCount);

int main(){

    SellerInfo sellerInfo;
    ShopItem *shopItem[100];
    string user, pass;
    bool is_login = false;
    int currentItem = 0;

    ifstream data_seller("seller.txt");
    if(data_seller.fail()){
        cout << "Seller Account Doesn't Exists";
        exit(0);
    } else {
        string tmp_name, tmp_pass;
        while(!data_seller.eof()){
            getline(data_seller, tmp_name, ',');
            getline(data_seller, tmp_pass, '\n');
        }
        sellerInfo.set_seller_info(tmp_name, tmp_pass);
    }
    data_seller.close();

    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;
    is_login = check_validation(user, pass, sellerInfo);

    if(is_login == true){
        load_shop_item(shopItem, currentItem);
    } else {
        cout << "Failed";
        exit(0);
    }

    for(int i=0; i<currentItem; i++){
        shopItem[i]->display_item();
    }

    update_item(shopItem, 1);
    delete_item(shopItem, 2, currentItem);
    insert_item(shopItem, currentItem);
    sortArrayByID(shopItem, currentItem);
    saveItemList(shopItem, currentItem);
    for(int i=0; i<currentItem; i++){
        shopItem[i]->display_item();
    }


    delete [] *shopItem;
    return 0;
}

bool check_validation(string username, string password, SellerInfo sellerInfo){
    string tmp_username = sellerInfo.get_username();
    string tmp_password = sellerInfo.get_password();
    bool validity;

    if(username == tmp_username && password == tmp_password){
        validity = true;
    } else {
        validity = false;
    }
    return validity;
}

void load_shop_item(ShopItem *shopItem[], int &_itemCount){
    ifstream itemList("item.txt");
    int count = 0;

    if(itemList.fail()){
       cout << "Error opening item list.";
    } else {
        while(!itemList.eof()){
            string _itemID, _itemTYPE, _itemNAME, _itemPRICE, _itemUNIT, _companyNAME, _itemDATA;
            getline(itemList, _itemID, ',');
            getline(itemList, _itemTYPE, ',');
            getline(itemList, _itemNAME, ',');
            getline(itemList, _itemPRICE, ',');
            getline(itemList, _itemUNIT, ',');
            getline(itemList, _companyNAME, ',');
            getline(itemList, _itemDATA, '\n');

            if(_itemTYPE == "Book"){
                Book *b = new Book(stoi(_itemID), stoi(_itemUNIT), stof(_itemPRICE), _itemNAME, _companyNAME,
                                   _itemDATA);
                shopItem[count] = b;
            } else if(_itemTYPE == "Magazine") {
                Magazine *mg = new Magazine(stoi(_itemID), stoi(_itemUNIT), stof(_itemPRICE), _itemNAME, _companyNAME,
                                            _itemDATA);
                shopItem[count] = mg;
            } else if(_itemTYPE == "Movie") {
                Movie *mv = new Movie(stoi(_itemID), stoi(_itemUNIT), stof(_itemPRICE), _itemNAME, _companyNAME,
                                      _itemDATA);
                shopItem[count]  = mv;
            }
            count++;
        }
    }
    _itemCount = count;
}

void update_item(ShopItem *shopItem[], int _itemID){
    int choice, _itemUNIT;
    string _itemNAME, _companyNAME, _itemDATA;
    float _itemPRICE;

    cout << "1. Book\n2. Magazine\n3.Movie\n";
    cout << "Select what type of the item: ";
    cin >> choice;
    cout << "Enter new item name        : ";
    cin.ignore();
    getline(cin, _itemNAME, '\n');
    cout << "Enter new price            : RM";
    cin >> _itemPRICE;
    cout << "Enter new item unit(s)     : ";
    cin >> _itemUNIT;
    cout << "Enter new company name     : ";
    cin.ignore();
    getline(cin, _companyNAME, '\n');

    switch (choice) {
        case 1: {
            cout << "Enter new author name      : ";
            getline(cin, _itemDATA, '\n');
            Book *b = new Book(_itemID, _itemUNIT, _itemPRICE, _itemNAME, _companyNAME, _itemDATA);
            shopItem[_itemID-1] = b;
            break;
        }
        case 2: {
            cout << "Enter new publication date : ";
            getline(cin, _itemDATA, '\n');
            Magazine *m = new Magazine(_itemID, _itemUNIT, _itemPRICE, _itemNAME, _companyNAME, _itemDATA);
            shopItem[_itemID-1] = m;
            break;
        }
        case 3: {
            cout << "Enter new actor name       : ";
            getline(cin, _itemDATA, '\n');
            Movie *mv = new Movie(_itemID, _itemUNIT, _itemPRICE, _itemNAME, _companyNAME, _itemDATA);
            shopItem[_itemID-1] = mv;
            break;
        }
    }
}

void delete_item(ShopItem *shopItem[], int _itemID, int &_itemCount){
    char choice;
    int count;

    cout << "Are you sure to delete this item? [Y = YES or Any key to cancel]";
    cin >> choice;

    if(choice == 'Y'){
        for(int i = 0; i < _itemCount; i++){
            if(shopItem[i]->get_item_id() == _itemID){
                for(int j = i; j<(_itemCount - 1); j++){
                    shopItem[j] = shopItem[j+1];
                    shopItem[j+1] = new ShopItem();
                }
                //Check if the array already delete and shift up by 1 or no deletion were made because Item ID not found.
                count++;
            }
        }

        if(count != 0) {
            _itemCount--;
            cout << "Item ID: " << _itemID << " deletion completed\n";
        } else {
            cout << "Item ID: " << _itemID << " was not found so no deletion were made.\n";
        }
    } else {
        cout << "No deletion were made.\n";
    }
}

void insert_item(ShopItem *shopItem[], int &_itemCount){
    string _type, _itemNAME, _companyNAME, _itemDATA;
    float _itemPRICE;
    int _itemUNIT, _itemID;

    cout << "Please insert new details for this item!\n";
    cout << "What type of the new item [B = Book, M = Magazine, MV = Movie]\n";
    cout << "Type: ";
    cin.ignore();
    getline(cin, _type, '\n');
    while(_type == "B" & _type == "M" & _type == "MV"){
        if(_type != "B" & _type != "M" & _type != "MV"){
            cout << "\nYour enter wrong type. Please try again.\n";
            cout << "Type: ";
            getline(cin, _type, '\n');
        }
    }
    cout << "Enter item name       :";
    getline(cin, _itemNAME, '\n');
    cout << "Enter price           : ";
    cin >> _itemPRICE;
    cout << "Enter item unit       : ";
    cin >> _itemUNIT;
    cout << "Enter company name    : ";
    cin.ignore();
    getline(cin, _companyNAME, '\n');

    _itemID = findSmallestValue(shopItem, _itemCount);
    _itemCount++;

    if(_type == "B"){
        cout << "Enter author name     : ";
        getline(cin, _itemDATA, '\n');
        Book *b = new Book(_itemID, _itemUNIT, _itemPRICE, _itemNAME, _companyNAME, _itemDATA);
        shopItem[_itemCount-1] = b;
    } else if(_type == "M"){
        cout << "Enter publication date: ";
        getline(cin, _itemDATA, '\n');
        Magazine *m = new Magazine(_itemID, _itemUNIT, _itemPRICE, _itemNAME, _companyNAME, _itemDATA);
        shopItem[_itemCount-1] = m;
    } else if(_type == "MV"){
        cout << "Enter new actor name  : ";
        getline(cin, _itemDATA, '\n');
        Movie *mv = new Movie(_itemID, _itemUNIT, _itemPRICE, _itemNAME, _companyNAME, _itemDATA);
        shopItem[_itemCount-1] = mv;
    }
}

void swapArray(int &a, int &b){
    int tmp = a;
    a = b;
    b = tmp;
}

int findSmallestValue(ShopItem *shopItem[], int _itemCount){
    int max, index;
    int _tmpArray[_itemCount];

    for(int i = 0; i < _itemCount; i++){
        _tmpArray[i] = shopItem[i]->get_item_id();
    }

    for(max = _itemCount - 1; max > 0; max--){
        for(index = 0; index < max; index++){
            if(_tmpArray[index] > _tmpArray[index + 1]){
                swap(_tmpArray[index], _tmpArray[index + 1]);
            }
        }
    }

    for(int i = 0; i < _itemCount; i++){
        if(_tmpArray[i] != i +1 ){
            return i + 1;
        }
    }
    return _itemCount + 1;
}

void sortArrayByID(ShopItem *shopItem[], int _itemCount){
    int minIndex, minValue;

    for(int i = 0; i < (_itemCount - 1); i++){
        minIndex = i;
        minValue = shopItem[i]->get_item_id();
        for(int j = i + 1; j < _itemCount; j++){
            if(shopItem[j]->get_item_id() < minValue){
                minValue = shopItem[j]->get_item_id();
                minIndex = j;
            }
        }
        swap(shopItem[minIndex], shopItem[i]);
    }
}

void saveItemList(ShopItem *shopItem[], int itemCount){
    ofstream itemFile;
    itemFile.open("item.txt");
    for(int i = 0; i < itemCount; i++){
       itemFile << shopItem[i]->get_item_id() << "," << shopItem[i]->get_ItemType() << "," << shopItem[i]->get_item_name()
       << "," << shopItem[i]->get_price() << "," << shopItem[i]->get_num_unit() << "," << shopItem[i]->get_company_name()
       << "," << shopItem[i]->get_ItemData() << endl;
    }
    itemFile.close();
}
