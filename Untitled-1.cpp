#include <iostream>
#include <fstream>
#include <map>
#include <windows.h>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <thread> // For sleep functionality
#include <chrono> // For time-based delays
using namespace std;

// Utility function for better formatting
void printLine()
{
    cout << "--------------------------------------------------\n";
}

// Struct to store rental history
struct RentalHistory
{
    string carName;
    int days;
    double totalCost;
};

// Car class extended with more details
//Encapsulation Data and functionality are grouped within classes
class Car
{
public:
    string name;
    double price_per_day;
    int quantity;
    string fuelType;
    string transmission;
    int seatingCapacity;
    int timesRented;

    Car(string n = "", double p = 0.0, int q = 0, string fuel = "", string trans = "", int seating = 0)
        : name(n), price_per_day(p), quantity(q), fuelType(fuel), transmission(trans), seatingCapacity(seating), timesRented(0) {}
};

// Showroom class manages all car details
//Inheritance While inheritance is not explicitly implemented, the structure is suitable for adding it
class Showroom
{
private:
    map<string, Car> cars; // Storing cars by name for quick access

public:
    Showroom()
    {
        // Example cars in the showroom for testing
        cars["Sedan"] = Car("Sedan", 50, 5, "Petrol", "Automatic", 5);
        cars["SUV"] = Car("SUV", 80, 3, "Diesel", "Manual", 7);
        cars["Hatchback"] = Car("Hatchback", 40, 7, "Petrol", "Automatic", 5);
    }

    // Display cars with detailed information
    void displayCars()
    {
        printLine();
        cout << "Available Cars in Showroom:\n";
        for (auto &car : cars)
        {
            cout << "Car: " << car.second.name << ", Price/Day: $" << car.second.price_per_day
                 << ", Quantity: " << car.second.quantity << ", Fuel Type: " << car.second.fuelType
                 << ", Transmission: " << car.second.transmission << ", Seating Capacity: " << car.second.seatingCapacity
                 << ", Times Rented: " << car.second.timesRented << endl;
        }
        printLine();
    }

    // Admin: Add a new car to the showroom
    void addCar(string name, double price, int quantity, string fuel, string transmission, int seating)
    {
        cars[name] = Car(name, price, quantity, fuel, transmission, seating);
        cout << "Car added successfully!\n";
    }

    // Admin: Edit an existing car's details
    void editCar(string name, double price, int quantity, string fuel, string transmission, int seating)
    {
        if (cars.find(name) != cars.end())
        {
            cars[name].price_per_day = price;
            cars[name].quantity = quantity;
            cars[name].fuelType = fuel;
            cars[name].transmission = transmission;
            cars[name].seatingCapacity = seating;
            cout << "Car details updated!\n";
        }
        else
        {
            throw runtime_error("Car not found in showroom!");
        }
    }

    // Admin: Remove a car from the showroom
    //Polymorphism Function overloading is indirectly used in constructors 
    void removeCar(string name)
    {
        if (cars.find(name) != cars.end())
        {
            cars.erase(name);
            cout << "Car removed from showroom!\n";
        }
        else
        {
            throw runtime_error("Car not found in showroom!");
        }
    }

    // User: Rent a car and reduce the quantity, increase rental count
    Car rentCar(string name)
    {
        if (cars.find(name) != cars.end() && cars[name].quantity > 0)
        {
            cars[name].quantity--;
            cars[name].timesRented++;
            return cars[name];
        }
        else
        {
            throw runtime_error("Car not available or out of stock!");
        }
    }

    // User: Return a rented car
    void returnCar(string name)
    {
        if (cars.find(name) != cars.end())
        {
            cars[name].quantity++;
        }
        else
        {
            throw runtime_error("Car does not exist in showroom!");
        }
    }

    // Display cars rented most frequently
    void displayMostRentedCars()
    {
        printLine();
        cout << "Most Rented Cars:\n";
        for (auto &car : cars)
        {
            if (car.second.timesRented > 0)
            {
                cout << "Car: " << car.second.name << ", Times Rented: " << car.second.timesRented << endl;
            }
        }
        printLine();
    }
};

// Admin functionalities
//Access Specifiers private and public specifiers control access to class attributes and methods.

void adminMenu(Showroom &showroom)
{
    int choice;
    string name, fuel, transmission;
    double price;
    int quantity, seating;
    while (true)
    {
        cout << "\nAdmin Menu:\n";
        cout << "1. View available cars\n";
        cout << "2. Add a car\n";
        cout << "3. Edit a car\n";
        cout << "4. Remove a car\n";
        cout << "5. View most rented cars\n";
        cout << "6. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;
        try
        {
            if (choice == 1)
            {
                showroom.displayCars();
            }
            else if (choice == 2)
            {
                cout << "Enter car details:\n";
                cout << "Name: ";
                cin >> name;

                cout << "Price per day: ";
                cin >> price;

                cout << "Quantity: ";
                cin >> quantity;

                cout << "Fuel Type: ";
                cin >> fuel;

                cout << "Transmission: ";
                cin >> transmission;

                cout << "Seating Capacity: ";
                cin >> seating;

                showroom.addCar(name, price, quantity, fuel, transmission, seating);
            }
            else if (choice == 3)
            {
                cout << "Enter the name of the car you want to edit: ";
                cin >> name;

                cout << "Enter new price per day: ";
                cin >> price;

                cout << "Enter new quantity: ";
                cin >> quantity;

                cout << "Enter new fuel type: ";
                cin >> fuel;

                cout << "Enter new transmission: ";
                cin >> transmission;

                cout << "Enter new seating capacity: ";
                cin >> seating;

                showroom.editCar(name, price, quantity, fuel, transmission, seating);
            }
            else if (choice == 4)
            {
                cout << "Enter the name of the car you want to remove: ";
                cin >> name;

                showroom.removeCar(name);
            }
            else if (choice == 5)
            {
                showroom.displayMostRentedCars();
            }
            else if (choice == 6)
            {
                break; // Logout
            }
            else
            {
                cout << "Invalid choice. Please try again.\n";
            }
        }
        catch (exception &e)
        {
            cout << "Error: " << e.what() << endl;
        }
    }
}

class person
{
private:
    string id1;
    string kind;

public:
    person() : id1(""), kind("") {}
};
// User class with rental history and login functionality
class User
{
private:
    string userID;
    string password;
    int role;
    int what; // 1 for User, 2 for Admin
    vector<RentalHistory> rentalHistory;

public:
    User(string id = "", string pass = "") : userID(id), password(pass), role(1), what(0) {}

    void setID(string id)
    {
        userID = id;
    }

    void setPass(string pass)
    {
        password = pass;
    }

    string getID()
    {
        return userID;
    }

    string getPass()
    {
        return password;
    }

    void setRole(int r)
    {
        role = r;
    }

    int getRole()
    {
        return role;
    }

    void addRental(string carName, int days, double totalCost)
    {
        rentalHistory.push_back({carName, days, totalCost});
    }

    void Select()
    {
        cout << "Are you a?" << endl;
        cout << "User" << endl;
        cout << "Admin" << endl;

        cout << "Press 1 for the User" << endl;
        cout << "Press 2 for the Admin" << endl;
        cin >> what;
    }

    void registration()
    {
        system("cls");
        string id, pass;
        Select();
        if (what == 1)
        { // Registering as a User in a User data file
        //File Handling Used to store and retrieve user and admin login data
        start:
            cout << "Please enter your id: ";
            cin >> id;
            setID(id);

            cout << "Please enter the password: ";
            cin >> pass;

            if (pass.length() < 8)
            {
                cout << "please enter at least 8 character in your password." << endl;
                goto start;
            }

            else
            {
                setPass(pass);
            }

            ofstream outfile("E:/Car/UserData.txt", ios::app);

            if (!outfile)
            {
                cout << "Error: the file cannot be opened." << endl;
            }

            else
            {
                outfile << "user" << "\t" << getID() << "\t" << getPass() << endl;
                cout << "\t User Registered Successfully" << endl;
            }

            outfile.close();
            cout << "Returning to the main window";
            for (int i = 0; i < 3; i++)
            {
                cout << ".";
                Sleep(800);
            }
            Sleep(3000);
        }

        if (what == 2)
        { // Registering as a User in a User data file
        start1:
            cout << "Please enter your id: ";
            cin >> id;
            setID(id);

            cout << "Please enter the password: ";
            cin >> pass;

            if (pass.length() < 8)
            {
                cout << "please enter at least 8 character in your password." << endl;
                goto start;
            }

            else
            {
                setPass(pass);
            }

            ofstream outfile("E:/Car/AdminData.txt", ios::app);

            if (!outfile)
            {
                cout << "Error: the file cannot be opened." << endl;
            }

            else
            {
                outfile << "admin" << "\t" << getID() << "\t" << getPass() << endl;
                cout << "\t User Registered Successfully" << endl;
            }

            outfile.close();
            cout << "Returning to the main window";
            for (int i = 0; i < 3; i++)
            {
                cout << ".";
                Sleep(800);
            }
            Sleep(3000);
        }
    }

    int Login()
    {

        system("cls");
        string id, pass, role;

        cout << "Please enter your ID: ";
        cin >> id;

        cout << "Are you a user or admin: ";
        cin >> role;

        cout << "Please enter your Password: ";
        cin >> pass;

        if (role == "user")
        {
            ifstream infile("E:/Car/UserData.txt");
            if (!infile)
            {
                cout << "Error:cannot open the file!" << endl;
            }

            else
            {
                string line;
                bool found;

                while (getline(infile, line))
                {
                    stringstream ss;

                    ss << line;
                    string isUorA, UserID, UserPass;
                    char delimiter;
                    ss >> isUorA >> UserID >> UserPass;

                    if (id == UserID && pass == UserPass)
                    {
                        found = true;
                        cout << "Please wait";
                        for (int i = 0; i < 3; i++)
                        {
                            cout << ".";
                            Sleep(800);
                        }
                        system("cls");
                        cout << "Welcome to this Page" << endl;
                        // Showroom showroom1;
                        // User user;
                        // userMenu(user, showroom1);
                        return 1;
                    }
                }

                if (!found)
                {
                    cout << "Error: Incorrect details have been entered" << endl;
                }
            }
        }

        if (role == "admin")
        {
            ifstream infile("E:/Car/AdminData.txt");
            if (!infile)
            {
                cout << "Error:cannot open the file!" << endl;
            }

            else
            {
                string line;
                bool found;

                while (getline(infile, line))
                {
                    stringstream ss;

                    ss << line;
                    string isUorA, UserID, UserPass;
                    char delimiter;
                    ss >> isUorA >> UserID >> UserPass;

                    if (id == UserID && pass == UserPass)
                    {
                        found = true;
                        cout << "Please wait";
                        for (int i = 0; i < 3; i++)
                        {
                            cout << ".";
                            Sleep(800);
                        }
                        system("cls");
                        cout << "Welcome to this Page" << endl;
                        // Showroom showroom;
                        // adminMenu(showroom);
                        return 2;
                    }
                }

                if (!found)
                {
                    cout << "Error: Incorrect details have been entered" << endl;
                }
            }
        }
        return -1;
    }

    // Display user's rental history
    void displayRentalHistory()
    {
        if (rentalHistory.empty())
        {
            cout << "No rental history available.\n";
        }
        else
        {
            printLine();
            cout << "Rental History for " << userID << ":\n";
            for (auto &rental : rentalHistory)
            {
                cout << "Car: " << rental.carName << ", Days: " << rental.days << ", Total Cost: $" << rental.totalCost << endl;
            }
            printLine();
        }
    }
};

// Bill calculation function
//Abstraction Complex functionalitie
double calculateBill(Car car, int days)
{
    double baseCost = car.price_per_day * days;
    double discount = 0;

    if (days >= 7)
    {
        discount = baseCost * 0.10; // 10% discount for a week or more
    }

    double tax = baseCost * 0.18; // 18% tax
    double finalCost = baseCost - discount + tax;

    cout << "Base Cost: $" << baseCost << endl;
    if (discount > 0)
    {
        cout << "Discount: -$" << discount << endl;
    }
    cout << "Tax (18%): +$" << tax << endl;
    cout << "Final Cost: $" << finalCost << endl;

    return finalCost;
}

void userMenu(User &user, Showroom &showroom)
{
    int choice;
    string carName;
    int days;
    double totalCost;
    while (true)
    {
        cout << "\nUser Menu:\n";
        cout << "1. View available cars\n";
        cout << "2. Rent a car\n";
        cout << "3. Return a car\n";
        cout << "4. View rental history\n";
        cout << "5. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;
        try
        {
            if (choice == 1)
            {
                showroom.displayCars();
            }
            else if (choice == 2)
            {
                cout << "Enter the name of the car you want to rent: ";
                cin >> carName;

                cout << "Enter the number of days you want to rent it for: ";
                cin >> days;

                Car rentedCar = showroom.rentCar(carName);
                totalCost = calculateBill(rentedCar, days);
                user.addRental(carName, days, totalCost);

                cout << "Car rented successfully. Total cost: $" << totalCost << endl;
            }
            else if (choice == 3)
            {
                cout << "Enter the name of the car you want to return: ";
                cin >> carName;

                showroom.returnCar(carName);

                cout << "Car returned successfully!\n";
            }
            else if (choice == 4)
            {
                user.displayRentalHistory();
            }
            else if (choice == 5)
            {
                break; // Logout
            }
            else
            {
                cout << "Invalid choice. Please try again.\n";
            }
        }
        catch (exception &e)
        {
            cout << "Error: " << e.what() << endl;
        }
    }
}

// Login system for both users and admins
void loginSystem(User &user, Showroom &showroom)
{
    // User user;
    string id, pass;
    int choice, role;

    bool exit = false;
    cout << "Welcome to the Car Rental System\n";
    printLine();
    while (!exit)
    {                  // this loop will work until the user selects the exit btton and turns the value of the exit to true which !true => flase thus while loop will stop
        system("cls"); // this line will help you hide the previous output and only display the current output on the screen
        int val;       // we will give the user 3 option to REGISTER, LOGIN , EXIT

        cout << "\tWelcome To Registration & Login Form" << endl;
        cout << "\t************************************" << endl;
        cout << "\t1.Register." << endl;
        cout << "\t2.Login." << endl;
        cout << "\t3.Exit." << endl;
        cout << "\tEnter Choice: ";
        cin >> val;

        if (val == 1)
        {
            user.registration();
        }

        else if (val == 2)
        {
            int tag = user.Login();

            if (tag == 1)
            {
                userMenu(user, showroom);
            }
            if (tag == 2)
            {
                adminMenu(showroom);
            }
        }

        else if (val == 3)
        {
            system("cls");
            exit = true;
            cout << "\tBye Bye!!" << endl;
            Sleep(3000);
        }
        Sleep(3000);
    }
    cout << "Login:\n";
    cout << "Enter User ID: ";
    cin >> id;
    cout << "Enter Password: ";
    cin >> pass;

    // Simple login system (in practice, this should check against a database)
    user.setID(id);
    user.setPass(pass);

    if (id == "admin" && pass == "adminpass")
    {
        role = 2; // Admin
        user.setRole(role);
        cout << "Welcome Admin!\n";
        adminMenu(showroom);
    }
    else
    {
        role = 1; // Normal user
        user.setRole(role);
        cout << "Welcome User!\n";
        userMenu(user, showroom);
    }
}

// Main function
int main()
{
    Showroom showroom;
    User user;

    // Login system to differentiate between user and admin
    loginSystem(user, showroom);

    return 0;
}
