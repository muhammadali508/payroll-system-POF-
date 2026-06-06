#include<iostream>
#include<fstream>
#include<string>
using namespace std;

// ==========================================
// BASE CLASS: Employee
// ==========================================
class Employee
{
private:
    int id;
    string name;
    string department;

public:
    // Default Constructor
    Employee()
    {
        id = 0;
        name = "";
        department = "";
    }

    // Parameterized Constructor
    Employee(int i, string n, string d)
    {
        id = i;
        name = n;
        department = d;
    }

    // Copy Constructor
    Employee(Employee &e)
    {
        id = e.id;
        name = e.name;
        department = e.department;
    }

    // Destructor
    ~Employee()
    {
        // destructor
    }

    // Getters
    int getId()           { return id; }
    string getName()      { return name; }
    string getDept()      { return department; }

    // Setters
    void setId(int i)           { id = i; }
    void setName(string n)      { name = n; }
    void setDept(string d)      { department = d; }

    // Virtual function for Polymorphism
    virtual double calculateSalary() = 0;
    virtual string getType() = 0;

    virtual void display()
    {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Department: " << department << endl;
    }
};


// ==========================================
// DERIVED CLASS 1: FullTimeEmployee
// ==========================================
class FullTimeEmployee : public Employee
{
private:
    double basicSalary;
    double houseAllowance;
    double medicalAllowance;
    double taxDeduction;

public:
    // Default Constructor
    FullTimeEmployee() : Employee()
    {
        basicSalary = 0;
        houseAllowance = 0;
        medicalAllowance = 0;
        taxDeduction = 0;
    }

    // Parameterized Constructor
    FullTimeEmployee(int i, string n, string d,
                     double basic, double house,
                     double medical, double tax)
                     : Employee(i, n, d)
    {
        basicSalary = basic;
        houseAllowance = house;
        medicalAllowance = medical;
        taxDeduction = tax;
    }

    // Copy Constructor
    FullTimeEmployee(FullTimeEmployee &f) : Employee(f)
    {
        basicSalary = f.basicSalary;
        houseAllowance = f.houseAllowance;
        medicalAllowance = f.medicalAllowance;
        taxDeduction = f.taxDeduction;
    }

    // Destructor
    ~FullTimeEmployee() {}

    // Getters
    double getBasic()   { return basicSalary; }
    double getHouse()   { return houseAllowance; }
    double getMedical() { return medicalAllowance; }
    double getTax()     { return taxDeduction; }

    // Setters
    void setBasic(double b)   { basicSalary = b; }
    void setHouse(double h)   { houseAllowance = h; }
    void setMedical(double m) { medicalAllowance = m; }
    void setTax(double t)     { taxDeduction = t; }

    // Calculate Salary - Polymorphism
    double calculateSalary()
    {
        double gross = basicSalary + houseAllowance + medicalAllowance;
        double net = gross - taxDeduction;
        return net;
    }

    string getType() { return "FullTime"; }

    void display()
    {
        cout << "--- Full Time Employee ---" << endl;
        Employee::display();
        cout << "Basic Salary    : " << basicSalary << endl;
        cout << "House Allowance : " << houseAllowance << endl;
        cout << "Medical Allow   : " << medicalAllowance << endl;
        cout << "Tax Deduction   : " << taxDeduction << endl;
        cout << "Net Salary      : " << calculateSalary() << endl;
        cout << "--------------------------" << endl;
    }
};


// ==========================================
// DERIVED CLASS 2: PartTimeEmployee
// ==========================================
class PartTimeEmployee : public Employee
{
private:
    double hourlyRate;
    int hoursWorked;
    double bonus;

public:
    // Default Constructor
    PartTimeEmployee() : Employee()
    {
        hourlyRate = 0;
        hoursWorked = 0;
        bonus = 0;
    }

    // Parameterized Constructor
    PartTimeEmployee(int i, string n, string d,
                     double rate, int hours, double b)
                     : Employee(i, n, d)
    {
        hourlyRate = rate;
        hoursWorked = hours;
        bonus = b;
    }

    // Copy Constructor
    PartTimeEmployee(PartTimeEmployee &p) : Employee(p)
    {
        hourlyRate = p.hourlyRate;
        hoursWorked = p.hoursWorked;
        bonus = p.bonus;
    }

    // Destructor
    ~PartTimeEmployee() {}

    // Getters
    double getRate()  { return hourlyRate; }
    int getHours()    { return hoursWorked; }
    double getBonus() { return bonus; }

    // Setters
    void setRate(double r)  { hourlyRate = r; }
    void setHours(int h)    { hoursWorked = h; }
    void setBonus(double b) { bonus = b; }

    // Calculate Salary - Polymorphism
    double calculateSalary()
    {
        return (hourlyRate * hoursWorked) + bonus;
    }

    string getType() { return "PartTime"; }

    void display()
    {
        cout << "--- Part Time Employee ---" << endl;
        Employee::display();
        cout << "Hourly Rate  : " << hourlyRate << endl;
        cout << "Hours Worked : " << hoursWorked << endl;
        cout << "Bonus        : " << bonus << endl;
        cout << "Net Salary   : " << calculateSalary() << endl;
        cout << "--------------------------" << endl;
    }
};


// ==========================================
// CONTROLLER CLASS: PayrollSystem
// ==========================================
class PayrollSystem
{
private:
    Employee* employees[100];
    int count;
    string filename;

public:
    // Constructor
    PayrollSystem()
    {
        count = 0;
        filename = "payroll.txt";
        loadFromFile();
    }

    // Destructor
    ~PayrollSystem()
    {
        for(int i = 0; i < count; i++)
        {
            delete employees[i];
        }
    }

    // Add Full Time Employee
    void addFullTime()
    {
        int id;
        string name, dept;
        double basic, house, medical, tax;

        cout << "\n--- Add Full Time Employee ---" << endl;
        cout << "Enter ID          : "; cin >> id;
        cin.ignore();
        cout << "Enter Name        : "; getline(cin, name);
        cout << "Enter Department  : "; getline(cin, dept);
        cout << "Basic Salary      : "; cin >> basic;
        cout << "House Allowance   : "; cin >> house;
        cout << "Medical Allowance : "; cin >> medical;
        cout << "Tax Deduction     : "; cin >> tax;

        employees[count] = new FullTimeEmployee(id, name, dept,
                                                basic, house, medical, tax);
        count++;
        cout << "Employee Added Successfully!" << endl;
    }

    // Add Part Time Employee
    void addPartTime()
    {
        int id, hours;
        string name, dept;
        double rate, bonus;

        cout << "\n--- Add Part Time Employee ---" << endl;
        cout << "Enter ID         : "; cin >> id;
        cin.ignore();
        cout << "Enter Name       : "; getline(cin, name);
        cout << "Enter Department : "; getline(cin, dept);
        cout << "Hourly Rate      : "; cin >> rate;
        cout << "Hours Worked     : "; cin >> hours;
        cout << "Bonus Amount     : "; cin >> bonus;

        employees[count] = new PartTimeEmployee(id, name, dept,
                                                rate, hours, bonus);
        count++;
        cout << "Employee Added Successfully!" << endl;
    }

    // Display All Employees
    void displayAll()
    {
        if(count == 0)
        {
            cout << "No employees found!" << endl;
            return;
        }

        cout << "\n====== All Employees ======" << endl;
        for(int i = 0; i < count; i++)
        {
            employees[i]->display();
        }
        cout << "Total Employees: " << count << endl;
    }

    // Search by ID
    void searchEmployee()
    {
        int id;
        cout << "Enter ID to search: "; cin >> id;

        for(int i = 0; i < count; i++)
        {
            if(employees[i]->getId() == id)
            {
                cout << "Employee Found!" << endl;
                employees[i]->display();
                return;
            }
        }
        cout << "Employee not found!" << endl;
    }

    // Delete Employee
    void deleteEmployee()
    {
        int id;
        cout << "Enter ID to delete: "; cin >> id;

        for(int i = 0; i < count; i++)
        {
            if(employees[i]->getId() == id)
            {
                delete employees[i];
                for(int j = i; j < count-1; j++)
                {
                    employees[j] = employees[j+1];
                }
                count--;
                cout << "Employee Deleted!" << endl;
                return;
            }
        }
        cout << "Employee not found!" << endl;
    }

    // Payroll Report
    void generateReport()
    {
        if(count == 0)
        {
            cout << "No data to show!" << endl;
            return;
        }

        double total = 0;
        cout << "\n====== PAYROLL REPORT ======" << endl;

        for(int i = 0; i < count; i++)
        {
            cout << employees[i]->getName()
                 << " (" << employees[i]->getType() << ")"
                 << " - Salary: " << employees[i]->calculateSalary() << endl;
            total += employees[i]->calculateSalary();
        }

        cout << "----------------------------" << endl;
        cout << "Total Employees : " << count << endl;
        cout << "Total Payroll   : " << total << endl;
        cout << "Average Salary  : " << total/count << endl;
        cout << "============================" << endl;
    }

    // Save to File
    void saveToFile()
    {
        ofstream file(filename.c_str());
        if(!file)
        {
            cout << "Error opening file!" << endl;
            return;
        }

        for(int i = 0; i < count; i++)
        {
            if(employees[i]->getType() == "FullTime")
            {
                FullTimeEmployee* f = (FullTimeEmployee*)employees[i];
                file << "FT," << f->getId() << "," << f->getName() << ","
                     << f->getDept() << "," << f->getBasic() << ","
                     << f->getHouse() << "," << f->getMedical() << ","
                     << f->getTax() << "\n";
            }
            else
            {
                PartTimeEmployee* p = (PartTimeEmployee*)employees[i];
                file << "PT," << p->getId() << "," << p->getName() << ","
                     << p->getDept() << "," << p->getRate() << ","
                     << p->getHours() << "," << p->getBonus() << "\n";
            }
        }

        file.close();
        cout << "Data Saved to " << filename << endl;
    }

    // Load from File
    void loadFromFile()
    {
        ifstream file(filename.c_str());
        if(!file) return;

        string type;
        while(getline(file, type, ','))
        {
            if(type == "FT")
            {
                int id; string name, dept;
                double basic, house, medical, tax;
                char c;

                file >> id; file.get(c);
                getline(file, name, ',');
                getline(file, dept, ',');
                file >> basic; file.get(c);
                file >> house; file.get(c);
                file >> medical; file.get(c);
                file >> tax;
                file.ignore();

                employees[count] = new FullTimeEmployee(id, name, dept,
                                                        basic, house, medical, tax);
                count++;
            }
            else if(type == "PT")
            {
                int id, hours; string name, dept;
                double rate, bonus;
                char c;

                file >> id; file.get(c);
                getline(file, name, ',');
                getline(file, dept, ',');
                file >> rate; file.get(c);
                file >> hours; file.get(c);
                file >> bonus;
                file.ignore();

                employees[count] = new PartTimeEmployee(id, name, dept,
                                                        rate, hours, bonus);
                count++;
            }
        }
        file.close();
    }

    // Main Menu
    void run()
    {
        int choice;
        do
        {
            cout << "\n==============================" << endl;
            cout << "  Employee Payroll System" << endl;
            cout << "==============================" << endl;
            cout << " 1. Add Full-Time Employee" << endl;
            cout << " 2. Add Part-Time Employee" << endl;
            cout << " 3. Display All Employees" << endl;
            cout << " 4. Search Employee" << endl;
            cout << " 5. Delete Employee" << endl;
            cout << " 6. Generate Payroll Report" << endl;
            cout << " 7. Save Records" << endl;
            cout << " 0. Exit" << endl;
            cout << "------------------------------" << endl;
            cout << "Enter Choice: ";
            cin >> choice;

            switch(choice)
            {
                case 1: addFullTime();     break;
                case 2: addPartTime();     break;
                case 3: displayAll();      break;
                case 4: searchEmployee();  break;
                case 5: deleteEmployee();  break;
                case 6: generateReport();  break;
                case 7: saveToFile();      break;
                case 0:
                    saveToFile();
                    cout << "Goodbye!" << endl;
                    break;
                default:
                    cout << "Wrong choice!" << endl;
            }

        } while(choice != 0);
    }
};


// ==========================================
// main() function
// ==========================================
int main()
{
    PayrollSystem ps;
    ps.run();
    return 0;
}

