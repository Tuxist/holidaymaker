#include <iostream>
#include <employee.h>

void Employee(holidaymaker::EmployeePool *empool) {
    int runloop=0;
    while(runloop==0) {
        std::cout << "-------------Employee Menu------------\n"
                  << "(1) Add Employee\n"
                  << "(2) Delete Employee\n"
                  << "(3) List Employee's\n"
                  << "(4) Save to File\n"
                  << "(5) Exit Menu\n";
        int input=0;
        std::cin >> input;
        switch(input) {
        case 1: {
            holidaymaker::Employee *newem=empool->addEmployee();
            std::cout << "Enter Forename/Vorname:\n";
            char fname[255];
            std::cin >> fname;
            newem->setForename(fname);
            std::cout << "Enter Surname/Nachname:\n";
            char sname[255];
            std::cin >> sname;
            newem->setSurname(sname);
            std::cout << "Enter Birthday day:\n";
            int bday;
            std::cin >> bday;
            newem->setBirthdayDay(bday);
            std::cout << "Enter Birthday month:\n";
            int bmonth;
            std::cin >> bmonth;
            newem->setBirthdayMonth(bmonth);
            std::cout << "Enter Birthday year:\n";
            int byear;
            std::cin >> byear;
            newem->setBirthdayYear(byear);
        }
        break;
        case 2: {
            std::cout << "Enter ID: \n";
            int id=-1;
            std::cin >> id;
            for(holidaymaker::Employee *curemply=empool->getfirstEmployee(); curemply; curemply=curemply->nextEmployee()) {
                if(curemply->getID()==id) {
                    empool->delEmployee(curemply);
                    break;
                }
            }
        }
        break;
        case 3: {
            for(holidaymaker::Employee *curemply=empool->getfirstEmployee(); curemply; curemply=curemply->nextEmployee()) {
                std::cout << "Employee:\n";
                std::cout << "  ID: " << curemply->getID() << "\n";
                std::cout << "  Forname/Vorname: " << curemply->getForename() << "\n";
                std::cout << "  Surname/Nachname: " << curemply->getSurname() << "\n";
                std::cout << "  Birthday/Geburtstag: " << curemply->getBirthdayDay() << "/" 
                                                       << curemply->getBirthdayMonth() << "/" 
                                                       << curemply->getBirthdayYear() << "\n";
            }
            break;
            case 4: {
                empool->saveFile("holidaymaker.xml");
            }
            break;
            case 5: {
                runloop=1;
            }
            break;
            default: {
                std::cout << "wrong input\n";
            }
            break;
        }
        }
    }
}

int main(int argc, char* argv[]) {
    holidaymaker::EmployeePool empool;
    if(!empool.loadFile("holidaymaker.xml")) {
        std::cerr << "Cannot load default xml file create new one\n";
    }
    Employee(&empool);
    return 0;
}
