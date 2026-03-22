#include<iostream>
#include<cstring>
using namespace std;

class User {
private:
    char* name;
    const int idUser;
    float* PayHistory;
    int noPayments;

    static int noUsers;

public:

    void freeMemory() {
        if (this->name != nullptr) {
            delete[] this->name;
            this->name = nullptr;
        }
        if (this->PayHistory != nullptr) {
            delete[] this->PayHistory;
            this->PayHistory = nullptr;
        }
    }

//constr fara parametrii
    User() : idUser(noUsers++){
        this->name = nullptr;
        this->PayHistory = nullptr;
        this->noPayments = 0;
    }
//constr cu parametrii
    User(const char* name, const float* history, int count ) : idUser(++noUsers) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);

        this->noPayments = count;
        if (history != nullptr && count > 0 ) {
            this->PayHistory = new float[count];
            for (int i = 0; i < count; i++) {
                this->PayHistory[i] = history[i];
            }
        }
        else {
            this->PayHistory = nullptr;
            this->noPayments = 0;
        }

    }

    User(const User& other ) : idUser(++noUsers) { //copy constr

        this->noPayments = other.noPayments;
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);

        if (other.noPayments > 0 && other. PayHistory != nullptr) {
            this->PayHistory = new float[other.noPayments];
            for (int i = 0; i < other.noPayments; i++) {
                this->PayHistory[i] = other. PayHistory[i];
            }
        }
        else {
            this->PayHistory = nullptr;
        }

    }

    User& operator=(const User& other ) {
        if (this == &other) {
            return *this;
        }
        freeMemory();
        this->noPayments = other.noPayments;

        if (other.name != nullptr) {
            this->name = new char[strlen(other.name) + 1];
            strcpy(this->name, other.name);
        }
            if (other.noPayments > 0 && other. PayHistory != nullptr) {
                this->PayHistory = new float[other.noPayments];
                for (int i = 0; i < other.noPayments; i++) {
                    this->PayHistory[i] = other. PayHistory[i];
                }
            }
            else {
                this->PayHistory = nullptr;
            }

            return *this;

    }

    bool VIPstat() const {
        if ( this->noPayments == 0 || this->PayHistory == nullptr ) {
            cout << " Client is not VIP";
            return false;
        }

        double sum = 0;
        for ( int i = 0; i < this->noPayments; i++ ) {
            sum += this->PayHistory[i];
        }

        double average = sum / this->noPayments;

        if ( average >= 150.0) {
            cout << " Client is VIP";
            return true;
        }
        else {
            cout << " Client is not VIP";
            return false;
        }
    }


//destructor
    ~User() {
        freeMemory();
    }


//supraincarcarea operatorilor

    friend ostream& operator<<(ostream& out, const User& user) {
        out << "ID:"<<user.idUser<<endl;
        out << "Name:"<<user.name<<endl;
        out << "Number of Payments:"<<user.noPayments<<endl;
        out << "History of Payments:";
        if ( user.PayHistory != nullptr && user.noPayments > 0 ) {
            for (int i = 0; i < user.noPayments; i++) {
                out << user.PayHistory[i]<<"RON"<<endl;
            }
        } else {
            out << "NO PAYMENTS!"<<endl;
        }
        out << endl;
        return out;
    }

    friend istream& operator>>(istream& in, User& user) {
        cout << "What is the person's name : ";
        char buff[256];
        in >> ws;
        in.getline(buff,256);
        user.freeMemory();
        user.name = new char[strlen(buff) + 1];
        strcpy(user.name,buff);

        cout << "What is the person's number of Payments : ";
        in >> user.noPayments;

        if (user.noPayments > 0 ) {
            user.PayHistory = new float[user.noPayments];

            cout << "What is the person's History of Payments : ";
            for (int i = 0; i < user.noPayments; i++) {
                in >> user.PayHistory[i];
            }
        }
        else {
            user.PayHistory = nullptr;
        }

        return in;

    }

};

int User::noUsers = 0;


//A DOUAAAA CLASAAA

class Product {
private:
    char* name;
    char category;
    double price;
    bool isShared;

    void freeMemory() {
        if (this->name != nullptr) {
            delete[] this->name;
            this->name = nullptr;
        }
    }

public:

    Product() {
        this->name = nullptr;
        this->category = 'N';
        this->price = 0.0;
        this->isShared = false;
    }

    Product( const char* name, char category, double price, bool isShared ) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->category = category;
        this->price = price;
        this->isShared = isShared;
    }

    Product( const Product& other ) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->category = other.category;
        this->price = other.price;
        this->isShared = other.isShared;

    }

    Product& operator=(const Product& other ) {
        if (this == &other) {
            return *this;
        }
        freeMemory();

        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->category = other.category;
        this->price = other.price;
        this->isShared = other.isShared;

        return *this;
    }

    //destructor

    ~Product() {
        freeMemory();
    }

    //setters si getters

    double getPrice() {
        return this->price;
    }

    void setPrice(double newPrice) {
        if (newPrice >= 0)
            this->price = newPrice;
    }

    bool getIsShared() const {
        return this->isShared;
    }

    void setIsShared(bool statusShared) {
        this->isShared = statusShared;
    }

    const char* getName() const {
        return this->name;
    }

    char getCategory() const {
        return this->category;
    }


    double SplitThePrice( int noOfPeople ) const {
        if (noOfPeople <= 0) {
            return 0.0;
        }

        if ( this->isShared == true) {
            return this->price / noOfPeople;
        }
        else {
            return this->price;
        }
    }

    double getPriceInCurrency( const char* currency ) const {
        if ( currency == nullptr ) {
            return this->price;
        }

        if ( strcmp( currency, "USD" ) == 0 ) {
            return this->price / 4.60;
        }
        else if ( strcmp( currency, "EUR" ) == 0 ) {
            return this->price / 4.97;
        }
        else if ( strcmp( currency, "GBP" ) == 0 ) {
            return this->price / 5.80;
        }

        return this->price;
    }


    friend ostream& operator<<(ostream& out, const Product& product) {
        out<<"Product Name:"<<product.name<<endl;
        out<<"Product Category:"<<product.category<<endl;
        out<<"Product Price:"<<product.price<<" Ron\n"<<endl;
        out<<"Product IsShared:"<<product.isShared<<endl;

        return out;
    }

    friend istream& operator>>(istream& in, Product& product) {
        cout << "What is the product name : ";
        char buff[256];
        in >> ws;
        in.getline(buff,256);

        product.freeMemory();
        product.name = new char[strlen(buff) + 1];
        strcpy(product.name,buff);

        cout << "Enter category (F stands for food, D stand for Drink) : ";
        in >> product.category;

        cout << "Enter price : ";
        in >> product.price;

        cout << "Is it shared? (1 for yes, 0 for no) :";
        in >> product.isShared;

        return in;
    }
};

class Bill {

    private:
        long billId;
        Product* itemsOrdered;
        int noItems;
        double tip;

        void freeMemory() {
            if (this->itemsOrdered != nullptr) {
                delete[] this->itemsOrdered;
                this->itemsOrdered = nullptr;
            }
        }

    public:
        Bill() {
            this->itemsOrdered = nullptr;
            this->noItems = 0;
            this->tip = 0.0;
            this->billId = 0;
        }

        Bill(long id, const Product* items, int count, double tip) {
            this->billId = id;
            this->noItems = count;
            this->tip = tip;

            if ( items != nullptr && count > 0 ) {
                this->itemsOrdered = new Product[count];
                for ( int i = 0; i < count; i++ ) {
                    this->itemsOrdered[i] = items[i];
                }
            }
            else {
                this->itemsOrdered = nullptr;
            }
        }

        Bill(const Bill& other) {
            this->billId = other.billId;
            this->noItems = other.noItems;
            this->tip = other.tip;

            if ( other.itemsOrdered != nullptr && other.noItems > 0 ) {
                this->itemsOrdered = new Product[other.noItems];
                for ( int i = 0; i < other.noItems; i++ ) {
                    this->itemsOrdered[i] = other.itemsOrdered[i];
                }
            }
            else {
                this->itemsOrdered = nullptr;
            }
        }

        Bill& operator=(const Bill& other) {
            if (this == &other) {
                return *this;
            }

            freeMemory();

            this->billId = other.billId;
            this->noItems = other.noItems;
            this->tip = other.tip;

            if ( other.itemsOrdered != nullptr && other.noItems > 0 ) {
                this->itemsOrdered = new Product[other.noItems];
                for ( int i = 0; i < other.noItems; i++ ) {
                    this->itemsOrdered[i] = other.itemsOrdered[i];
                }
            }
            else {
                this->itemsOrdered = nullptr;
            }

            return *this;
        }

        ~Bill() {
            freeMemory();
        }

        void HappyHourDrinks() {
            bool used = false;
            for ( int i = 0; i < noItems; i++ ) {
                if ( this->itemsOrdered[i].getCategory() == 'D') {
                    double oldPrice = this->itemsOrdered[i].getPrice();
                    this->itemsOrdered[i].setPrice(oldPrice * 0.80);
                    used = true;
                }
            }

            if (used == true) {
                cout << "Happy Hour is activated for the drinks!";
            }
            else {
                cout << "No drinks on the bill";
            }
        }


        void DiscountRoulette() {
            if ( this->noItems == 0 ) {
                cout << "Order something";
            }

            cout << "Press ENTER for the spin wheel ";
            cin.ignore();
            cin.get();

            srand(time(0)); // initializarea generatorului de numere random
            int chance = rand() % 100 + 1;

            if ( chance <= 15 ) {
                cout << "You won 20% discount";
                for ( int i = 0; i < noItems; i++ ) {
                    this->itemsOrdered[i].setPrice(this->itemsOrdered[i].getPrice() * 0.80);
                }
            }
            else if (chance <= 45) {
                cout << "You wan 10% discount";
                for (int i = 0; i < noItems; i++ ) {
                    this->itemsOrdered[i].setPrice(this->itemsOrdered[i].getPrice() * 0.80);
                }
            }
            else {
                cout << " You didn't win any discount";
            }

        }


        Bill operator+( const Bill& other) const {
            Bill mergeBill;

            mergeBill.billId = this->billId + other.billId;
            mergeBill.noItems = this->noItems + other.noItems;
            mergeBill.tip = this->tip + other.tip;

            if ( mergeBill.noItems > 0 ) {
                mergeBill.itemsOrdered = new Product[mergeBill.noItems];


                int currentIndex = 0;

                for ( int i = 0; i < this->noItems; i++ ) {
                    mergeBill.itemsOrdered[currentIndex] = this->itemsOrdered[i];
                    currentIndex++;
                }

                for ( int i = 0; i < other.noItems; i++ ) {
                    mergeBill.itemsOrdered[currentIndex] = other.itemsOrdered[i];
                    currentIndex++;
                }

            }

            cout << " Succes" << endl;
            return mergeBill;

        }




        double CalculateTotal() const {
            double sum = 0.0;
            for ( int i = 0; i < noItems; i++ ) {
                sum += this->itemsOrdered[i].getPrice();
            }

            double total = sum + ( sum * (this->tip/100.0));
            return total;
        }





        friend ostream& operator<<(ostream& out, const Bill& b) {
            out << "\n Receipt id #" << b.billId<<endl;
            if ( b.itemsOrdered != nullptr && b.noItems > 0) {
                for ( int i = 0; i < b.noItems; i++ ) {
                    out << b.itemsOrdered[i] << endl;
                }
            }
            else {
                out << "No items on the bill";
            }
            out << "Tip: " << b.tip <<"%"<< endl;
            out << " TOTAL:" << b.CalculateTotal() << "RON"<<endl;

            return out;
        }

        friend istream& operator>>(istream& in, Bill& b) {
            cout << "Create a new Bill" << endl;
            cout << " Bill Id: #";
            in >> b.billId;

            cout << " How many items ?";
            in >> b.noItems;

            b.freeMemory();

            if ( b.noItems > 0 ) {
                b.itemsOrdered = new Product[b.noItems];
                for ( int i = 0; i < b.noItems; i++ ) {
                    cout << "\n Product " <<i+1 << ":";
                    in >> b.itemsOrdered[i];
                }
            }
            else {
                b.itemsOrdered = nullptr;
            }

            cout << " Tip percentage: ";
            in >> b.tip;

            return in;
        }

    };


class Restaurant {

private:
    char* name;
    char rating;
    bool isOpen;
    Bill* billHistory;
    int noBills;

    void freeMemory() {
        if ( this->name != nullptr ) {
            delete[] this->name;
            this->name = nullptr;
        }
        if (this-> billHistory != nullptr ) {
            delete[] this->billHistory;
            this->billHistory = nullptr;
        }
    }

public:
    Restaurant() {
        this->name = nullptr;
        this->rating = 'N';
        this->isOpen = false;
        this->billHistory = nullptr;
        this->noBills = 0;
    }

    Restaurant ( const char* name, char rating, bool isOpen, const Bill* history, int count ) {
        if (name!= nullptr) {
            this->name = new char[strlen(name)+1];
            strcpy(this->name, name);
        }
        else {
            this->name = nullptr;
        }
        this->rating = rating;
        this->isOpen = isOpen;
        this->noBills = count;

        if (history != nullptr && count >0) {
            this->billHistory = new Bill[count];
            for ( int i = 0; i < count; i++ ) {
                this->billHistory[i] = history[i];
            }
        }
        else {
            this->billHistory = nullptr;
        }
    }

    Restaurant(const Restaurant& other) {
        this-> rating = other.rating;
        this->isOpen = other.isOpen;
        this->noBills = other.noBills;

        if (other.name != nullptr) {
            this->name = new char[strlen(other.name)+1];
            strcpy(this->name, other.name);

        }
        else {
            this->name = nullptr;
        }

        if (other.billHistory != nullptr && other.noBills > 0) {
            this->billHistory = new Bill[other.noBills];
            for ( int i = 0; i < other.noBills; i++ ) {
                this->billHistory[i] = other.billHistory[i];
            }
        }
        else {
            this->billHistory = nullptr;
        }
    }


    Restaurant& operator= (const Restaurant& other) {
        if (this == &other) {
            return *this;
        }

        freeMemory();

        this->rating = other.rating;
        this->isOpen = other.isOpen;
        this->noBills = other.noBills;

        if (other.name != nullptr) {
            this->name = new char[strlen(other.name)+1];
            strcpy(this->name, other.name);
        }
        else {
            this->name = nullptr;
        }

        if (other.billHistory != nullptr && other.noBills > 0) {
            this->billHistory = new Bill[other.noBills];
            for ( int i = 0; i < other.noBills; i++ ) {
                this->billHistory[i] = other.billHistory[i];
            }
        }
        else {
            this->billHistory = nullptr;
        }

        return *this;
    }

    ~Restaurant() {
        freeMemory();
    }

    void FinancialReport() const {
        cout << " Financial Report:" << endl;

        if (this->noBills == 0 || this->billHistory == nullptr) {
            cout << "No bills in the records"<<endl;
            return;
        }

        double total = 0;
        for ( int i = 0; i < this->noBills; i++ ) {
            double billTotal = this->billHistory[i].CalculateTotal();
            total += billTotal;
            cout << " The bill no."<< i + 1 << "brought:" << billTotal <<"Ron"<< endl;
        }

        cout << "Total Revenue :" << total << endl;
    }

    friend ostream& operator<< (ostream& out, const Restaurant& r) {
        out << "Info: "<<endl;
        out << "name: " << r.name << endl;
        out << "rating: " << r.rating << endl;
        out << "Status: " << r.isOpen << endl;
        out << "Total Bills: " << r.noBills << endl;

        return out;
    }

    friend istream& operator>> (istream& in, Restaurant& r) {
        cout << "Info for new restaurant: "<<endl;
        cout << "Restaurant name:" << endl;
        char buff[256];
        in >> ws;
        in.getline(buff,256);

        r.freeMemory();
        r.name = new char[strlen(buff)+1];
        strcpy(r.name, buff);

        cout << "Rating (A, B, C) :";
        in >> r.rating;

        cout << " Is it still open? ( 1 for yes, 0 for no)"<< endl;
        in >> r.isOpen;

        r.billHistory = nullptr;
        r.noBills = 0;

        return in;

    }


};


class Menu {

private:
    User** users;
    int noUsers;

    Product** products;
    int noProducts;

    Bill** bills;
    int noBills;

    Restaurant* restaurant;

    void printUser() const {
        if ( noUsers == 0) {
            cout << " No users registered \n";
            return;
        }
        for ( int i = 0; i < noUsers; i++ ) {
            cout << i << ". " << *users[i] << endl;
        }
    }

    void printProduct() const {
        if ( noProducts == 0) {
            cout << " No products registered \n";
            return;
        }

        for ( int i = 0; i < noProducts; i++ ) {
            cout << i << ". " << *products[i] << endl;
        }
    }

    void printBill() const {
        if ( noBills == 0) {
            cout << " No bills registered \n";
            return;
        }

        for ( int i = 0; i < noBills; i++ ) {
            cout << i << ". " << *bills[i] << endl;
        }
    }

    int pickUser() const {
        if ( noUsers == 0) {
            cout << " No users registered \n";
            return -1;
        }

        printUser();
        cout << "Pick user index or pick <<-1>> to cancel: ";
        int index;
        cin >> index;

        if ( index == -1 ) return -1;
        if ( index < 0 || index >= noUsers ) return -1;

        return index;
    }


    int pickProduct() const {
        if ( noProducts == 0) {
            cout << " No products available \n";
            return -1;
        }
        printProduct();
        cout << " Pick a product's index or pick <<-1>> to cancel: ";
        int index;
        cin >> index;
        if ( index < 0 || index >= noProducts ) return -1;
        return index;

    }


    int pickBill() const {
        if ( noBills == 0) {
            cout << " No bills registered \n";
            return -1;
        }

        printBill();
        cout << " Pick a bill's index or pick <<-1>> to cancel: ";
        int index;
        cin >> index;
        if ( index < 0 || index >= noBills ) return -1;
        return index;
    }

public:

    Menu() {

        users = nullptr;
        noUsers = 0;
        products = nullptr;
        noProducts = 0;
        bills = nullptr;
        noBills = 0;
        restaurant = new Restaurant();
    }

    ~Menu() {
        // eliberarea memoriei pt fiecare obiect in parte
        for ( int i = 0; i < noUsers; i++ ) delete users[i];
        delete[] users;

        for ( int i = 0; i < noProducts; i++ ) delete products[i];
        delete[] products;

        for ( int i = 0; i < noBills; i++ ) delete bills[i];
        delete[] bills;

        delete restaurant;

    }


    void usersMenu() {

        while ( true ) {
            cout << " Users Menu:" << endl;
            cout << "0 - Back"<<endl;
            cout << "1 - Create User"<<endl;
            cout << "2 - List Users" << endl;
            cout << "3 - Edit User" << endl;
            cout << "4 - Remove User" << endl;
            cout << "5 - Check VIP status" << endl;
            cout << "Option:" ;

            int option;
            cin >> option;

            switch (option) {
                case 0:
                    return;
                case 1: {
                    User* u = new User();
                    cin >> *u;
                    User** temp = new User*[noUsers + 1];
                    for ( int i = 0; i < noUsers; i++ ) temp[i] = users[i];
                    temp[noUsers] = u;
                    delete[] users;
                    users = temp;
                    noUsers++;
                    cout << " Users created" << endl;
                    break;
                }
                case 2: {
                    printUser();
                    break;
                }
                case 3: {
                    int index = pickUser();
                    if ( index == -1 ) break;
                    cin >> *users[index];
                    cout << " User updated"<< endl;
                    break;
                    }
                case 4: {
                    int index = pickUser();
                    if (index == -1) break;
                    delete users[index];
                    for ( int i = 0; i < noUsers - 1; i++ ) users[i] = users[i + 1];
                    noUsers--;
                    cout << " User removed" << endl;
                    break;

                }
                case 5: {
                    int index = pickUser();
                    if ( index == -1 ) break;
                    users[index] -> VIPstat();
                    cout << endl;
                    break;
                }
                default : cout << " Invalid option"<<endl;

                }

            }
        }

    void productsMenu() {
        while (true) {
            cout << " Product Menu:" << endl;
            cout << "0 - Back"<<endl;
            cout << "1 - Create Product" << endl;
            cout << "2 - List Product" << endl;
            cout << "3 - Edit Product" << endl;
            cout << "4 - Remove Product" << endl;
            cout << "5 - Convert price"<< endl;
            cout << "Option:" ;

            int option;
            cin >> option;

            switch (option) {
                case 0:
                    return;
                case 1: {
                    Product* product = new Product();
                    cin >> *product;
                    Product** temp = new Product*[noProducts + 1];
                    for ( int i = 0; i < noProducts; i++ ) temp[i] = products[i];
                    temp[noProducts] = product;
                    delete[] products;
                    products = temp;
                    noProducts++;
                    cout << " Product created" << endl;
                    break;
                    }
                case 2: {
                    printProduct();
                    break;
                }
                case 3: {
                    int index = pickProduct();
                    if ( index == -1 ) break;
                    cin >> *products[index];
                    cout << " Product updated" << endl;
                    break;
                }
                case 4: {
                    int index = pickProduct();
                    if ( index == -1) break;
                    delete products[index];
                    for ( int i = 0; i < noProducts - 1; i++ ) products[i] = products[i + 1];
                    noProducts--;
                    cout << " Product removed" << endl;
                    break;
                }
                case 5: {
                    int index = pickProduct();
                    if ( index == -1 ) break;
                    cout << " Price in EUR: " << products[index]->getPriceInCurrency("EUR") << " EUR" <<endl;
                    break;
                }
                default : cout << " Invalid option"<<endl;
            }
        }
    }

    void billsMenu() {
        while (true) {
            cout << " Bill Menu:" << endl;
            cout << "0 - Back"<<endl;
            cout << "1 - Create Bill" << endl;
            cout << "2 - List Bill" << endl;
            cout << "3 - Apply Happy Hour for drinks" << endl;
            cout << "4 - Play discount roulette" << endl;
            cout << "5 - combine two bills" << endl;
            cout << "Option:" ;

            int option;
            cin >> option;

            switch (option) {
                case 0:
                    return;
                case 1: {
                    Bill* bill = new Bill();
                    cin >> *bill;
                    Bill** temp = new Bill*[noBills + 1];
                    for ( int i = 0; i < noBills; i++ ) temp[i] = bills[i];
                    temp[noBills] = bill;
                    delete[] bills;
                    bills = temp;
                    noBills++;
                    cout << " Bill created" << endl;
                    break;
                }
                case 2: {
                    printBill();
                    break;
                }
                case 3: {
                    int index = pickBill();
                    if ( index == -1 ) break;
                    bills[index] -> HappyHourDrinks();
                    cout << endl;
                    break;
                }
                case 4: {
                    int index = pickBill();
                    if ( index == -1) break;
                    bills[index] -> DiscountRoulette();
                    cout << endl;
                    break;
                }
                case 5: {
                    cout << " Select First bill: "<<endl;
                    int idx1 = pickBill();
                    if ( idx1 == -1 ) break;
                    cout << " Select second bill: "<<endl;
                    int idx2 = pickBill();
                    if ( idx2 == -1 || idx1 == idx2 ) {
                        cout << "Invalid second bill" << endl;
                        break;
                    }

                    Bill* mergeBill = new Bill(*bills[idx1] + *bills[idx2]);

                    Bill** temp = new Bill*[noBills + 1];
                    for ( int i = 0; i < noBills; i++ ) temp[i] = bills[i];
                    temp[noBills] = mergeBill;

                    delete[] bills;
                    bills = temp;
                    noBills++;

                    cout << " Bills merged successfully" << endl;
                    break;

                }

                default : cout << " Invalid option"<<endl;
            }
        }
    }


    void restaurantMenu() {
        while (true) {
            cout << " Restaurant Menu:" << endl;
            cout << "0 - Back" << endl;
            cout << "1 - Setup / Edit restaurant Details" << endl;
            cout << "2 - View Restaurant Details"<<endl;
            cout << "3 - Generate Financial Report"<<endl;
            cout << "Options: ";

            int option;
            cin >> option;

            switch (option) {
                case 0:
                    return;
                case 1: {
                    cin >> *restaurant;
                    cout << " Restaurant setup complete"<< endl;
                    break;

                }
                case 2 : {
                    cout << *restaurant;
                    break;
                }
                case 3 : {
                    if (noBills == 0 ) {
                        cout << " No bills" << endl;
                        break;
                    }

                    Bill* tempA = new Bill[noBills];
                    for ( int i = 0; i < noBills; i++ ) tempA[i] = *(bills[i]);

                    Restaurant tempRest( "Synced Data", 'A', true, tempA, noBills );

                    tempRest.FinancialReport();
                    delete[] tempA;

                    break;
                }
            }
        }
    }




    void run() {

        while (true) {
            cout << " MAIN MENU :" << endl;
            cout << "0 - Exit" << endl;
            cout << "1 - Manage Users" << endl;
            cout << "2 - Manage Products" << endl;
            cout << "3 - Manage Bills" << endl;
            cout << "4 - Restaurant Setting" << endl;
            cout << " Pick an option: ";

            int option;
            cin >> option;

            switch (option) {
                case 0:
                    cout << " Exiting.."<< endl;
                    return;
                case 1:
                    usersMenu();
                    break;
                case 2 :
                    productsMenu();
                    break;
                case 3 :
                    billsMenu();
                    break;
                case 4 :
                    restaurantMenu();
                default :
                    cout << " Invalid option"<<endl;
                    break;



            }
        }
    }


};




int main() {

    Menu appMenu;
    appMenu.run();


    return 0;
}