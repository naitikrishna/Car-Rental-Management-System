#include "Model.hpp"
#include <iostream>
#include <unordered_map>

using namespace std ;

// ─── CarDBM ───────────────────────────────────────────────────────────────────

CarDBM::CarDBM() {
    vector<string> data = readFromFile("./DB/car.csv", 7) ;
    if( data.size() == 1 ) return ;
    for(int i = 0 ; i < data.size() ; i+=7){
        Car* car = new Car(data[i], data[i+1], stoi(data[i+2])) ;
        car -> setRent(stof(data[i+3])) ;
        car -> setRentDate(data[i+4]) ;
        car -> setDueDate(data[i+5]) ;
        car -> setUser(data[i+6]) ;
        cars[data[i]] = car ;  // key = car_id
    }
}

CarDBM::~CarDBM() {
    vector<string> data ;
    for(auto& pair : cars) {
        Car* c = pair.second ;
        data.push_back(c -> getCarId()) ;
        data.push_back(c -> getModel()) ;
        data.push_back(to_string(c -> getCondition())) ;
        data.push_back(to_string(c -> getRent())) ;
        data.push_back(c -> showRentDate()) ;
        data.push_back(c -> showDueDate()) ;
        data.push_back(c -> getUser()) ;
    }
    writeToFile("./DB/car.csv", data, 7) ;
}

void CarDBM::UpdateCar(Car* car) {
    cars[car -> getCarId()] = car ;  // O(1) update
}

Car* CarDBM::SelectCar(string carid) {
    if(cars.count(carid))
        return cars[carid] ;  // O(1) lookup
    return NULL ;
}

vector<Car*> CarDBM::ListCars() {
    vector<Car*> list ;
    for(auto& pair : cars)
        list.push_back(pair.second) ;
    return list ;
}

void CarDBM::AddCar(Car* car) {
    if(cars.count(car -> getCarId())) {
        cout << "CarID already exists!" << endl ;
        return ;
    }
    cars[car -> getCarId()] = car ;  // O(1) insert
    cout << "Car added successfully!" << endl ;
}

void CarDBM::DeleteCar(string carid) {
    if(cars.count(carid)) {
        cars.erase(carid) ;  // O(1) delete
        cout << "Car deleted successfully!" << endl ;
        return ;
    }
    cout << "CarID does not exist!" << endl ;
}

void CarDBM::DeleteCarsUserID(string userid) {
    for(auto& pair : cars) {
        if(pair.second -> getUser() == userid) {
            pair.second -> setUser("") ;
            pair.second -> setRentDate("") ;
            pair.second -> setDueDate("") ;
        }
    }
}

// ─── CustomerDBM ──────────────────────────────────────────────────────────────

CustomerDBM::CustomerDBM() {
    vector<string> data = readFromFile("./DB/customer.csv", 6) ;
    if( data.size() == 1 ) return ;
    for(int i = 0 ; i < data.size() ; i+=6){
        Customer* customer = new Customer(data[i], data[i+1], data[i+2], stof(data[i+3]), stod(data[i+4])) ;
        customer -> setNumberOfCarsRented(stoi(data[i+5])) ;
        customers[data[i]] = customer ;  // key = userid
    }
}

CustomerDBM::~CustomerDBM() {
    vector<string> data ;
    for(auto& pair : customers) {
        Customer* c = pair.second ;
        data.push_back(c -> getUserId()) ;
        data.push_back(c -> getPassword()) ;
        data.push_back(c -> getName()) ;
        data.push_back(to_string(c -> getCustomerRecord())) ;
        data.push_back(to_string(c -> getDues())) ;
        data.push_back(to_string(c -> getNumberOfCarsRented())) ;
    }
    writeToFile("./DB/customer.csv", data, 6) ;
}

void CustomerDBM::UpdateCustomer(Customer* customer) {
    customers[customer -> getUserId()] = customer ;  // O(1) update
}

Customer* CustomerDBM::SelectCustomer(string userid) {
    if(customers.count(userid))
        return customers[userid] ;  // O(1) lookup
    return NULL ;
}

vector<Customer*> CustomerDBM::ListCustomers() {
    vector<Customer*> list ;
    for(auto& pair : customers)
        list.push_back(pair.second) ;
    return list ;
}

void CustomerDBM::AddCustomer(Customer* customer) {
    if(customers.count(customer -> getUserId())) {
        cout << "UserID already exists!" << endl ;
        return ;
    }
    customers[customer -> getUserId()] = customer ;  // O(1) insert
    cout << "Customer added successfully!" << endl ;
}

void CustomerDBM::DeleteCustomer(string userid) {
    if(customers.count(userid)) {
        customers.erase(userid) ;  // O(1) delete
        cout << "Customer deleted successfully!" << endl ;
        return ;
    }
    cout << "UserID does not exist!" << endl ;
}

// ─── EmployeeDBM ──────────────────────────────────────────────────────────────

EmployeeDBM::EmployeeDBM() {
    vector<string> data = readFromFile("./DB/employee.csv", 6) ;
    if( data.size() == 1 ) return ;
    for(int i = 0 ; i < data.size() ; i+=6){
        Employee* employee = new Employee(data[i], data[i+1], data[i+2], stof(data[i+3]), stod(data[i+4])) ;
        employee -> setNumberOfCarsRented(stoi(data[i+5])) ;
        employees[data[i]] = employee ;  // key = userid
    }
}

EmployeeDBM::~EmployeeDBM() {
    vector<string> data ;
    for(auto& pair : employees) {
        Employee* e = pair.second ;
        data.push_back(e -> getUserId()) ;
        data.push_back(e -> getPassword()) ;
        data.push_back(e -> getName()) ;
        data.push_back(to_string(e -> getEmployeeRecord())) ;
        data.push_back(to_string(e -> getDues())) ;
        data.push_back(to_string(e -> getNumberOfCarsRented())) ;
    }
    writeToFile("./DB/employee.csv", data, 6) ;
}

void EmployeeDBM::UpdateEmployee(Employee* employee) {
    employees[employee -> getUserId()] = employee ;  // O(1) update
}

Employee* EmployeeDBM::SelectEmployee(string userid) {
    if(employees.count(userid))
        return employees[userid] ;  // O(1) lookup
    return NULL ;
}

vector<Employee*> EmployeeDBM::ListEmployees() {
    vector<Employee*> list ;
    for(auto& pair : employees)
        list.push_back(pair.second) ;
    return list ;
}

void EmployeeDBM::AddEmployee(Employee* employee) {
    if(employees.count(employee -> getUserId())) {
        cout << "UserID already exists!" << endl ;
        return ;
    }
    employees[employee -> getUserId()] = employee ;  // O(1) insert
    cout << "Employee Added!" << endl ;
}

void EmployeeDBM::DeleteEmployee(string userid) {
    if(employees.count(userid)) {
        employees.erase(userid) ;  // O(1) delete
        cout << "Employee Deleted!" << endl ;
        return ;
    }
    cout << "Employee not found!" << endl ;
}

// ─── ManagerDBM ───────────────────────────────────────────────────────────────

ManagerDBM::ManagerDBM() {
    vector<string> data = readFromFile("./DB/manager.csv", 3) ;
    if( data.size() == 1 ) return ;
    for(int i = 0 ; i < data.size() ; i+=3){
        Manager* manager = new Manager(data[i], data[i+1], data[i+2]) ;
        managers[data[i]] = manager ;  // key = userid
    }
}

ManagerDBM::~ManagerDBM() {
    vector<string> data ;
    for(auto& pair : managers) {
        Manager* m = pair.second ;
        data.push_back(m -> getUserId()) ;
        data.push_back(m -> getPassword()) ;
        data.push_back(m -> getName()) ;
    }
    writeToFile("./DB/manager.csv", data, 3) ;
}

void ManagerDBM::UpdateManager(Manager* manager) {
    managers[manager -> getUserId()] = manager ;  // O(1) update
}

Manager* ManagerDBM::SelectManager(string userid) {
    if(managers.count(userid))
        return managers[userid] ;  // O(1) lookup
    return NULL ;
}

vector<Manager*> ManagerDBM::ListManagers() {
    vector<Manager*> list ;
    for(auto& pair : managers)
        list.push_back(pair.second) ;
    return list ;
}

void ManagerDBM::AddManager(Manager* manager) {
    if(managers.count(manager -> getUserId())) {
        cout << "UserID already exists!" << endl ;
        return ;
    }
    managers[manager -> getUserId()] = manager ;  // O(1) insert
    cout << "Manager Added!" << endl ;
}

void ManagerDBM::DeleteManager(string userid) {
    if(managers.count(userid)) {
        managers.erase(userid) ;  // O(1) delete
        cout << "Manager Deleted!" << endl ;
        return ;
    }
    cout << "UserID does not exist!" << endl ;
}