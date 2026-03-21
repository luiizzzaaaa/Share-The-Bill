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
        in.getline(buff,256);
        user.freeMemory();
        user.name = new char[strlen(buff) + 1];
        strcpy(user.name,buff);

        cout << "What is the person's number of Payments : ";
        in >> user.noPayments;

        if (user.noPayments > 0 ) {
            user.PayHistory = new float[user.noPayments];
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
                for ( int i = 1; i <= noItems; i++ ) {
                    this->itemsOrdered[i].setPrice(this->itemsOrdered[i].getPrice() * 0.80);
                }
            }
            else if (chance <= 45) {
                cout << "You wan 10% discount";
                for (int i = 1; i <= noItems; i++ ) {
                    this->itemsOrdered[i].setPrice(this->itemsOrdered[i].getPrice() * 0.80);
                }
            }
            else {
                cout << " You didn't win any discount";
            }

        }

        double CalculateTotal() const {
            double sum = 0.0;
            for ( int i = 0; i <= noItems; i++ ) {
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







int main() {


    return 0;
}