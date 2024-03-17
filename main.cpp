// making of table should be by user ie admin using command prompt
// CREATE TABLE hostel (
//     Name VARCHAR(255) PRIMARY KEY,
//     Bed INT NOT NULL,
//     Fee INT NOT NULL
// );

// insert/update of new hostel name , bed fees in table should be by user ie admin using command prompt
#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <windows.h>
#include <sstream>
using namespace std;
const char *HOST = "localhost";
const char *USER = "root";
const char *PW = "your password";
const char *DB = "your database name";

class Hostel {
private:
    std::string Name;
    int Bed;
    int Fee;
public:
    Hostel(std::string name, int bed, int fee) : Name(name), Bed(bed), Fee(fee) {}

    std::string getName() const { return Name; }
    int getBed() const { return Bed; }
    int getFee() const { return Fee; }
};

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, HOST, USER, PW, DB, 3306, NULL, 0)) {
        std::cout << "Error while connecting to database: " << mysql_error(conn) << std::endl;
        return 1;
    }

    Hostel hostels[5] = {
        Hostel("jscoe_hostel_1", 2, 5000),
        Hostel("jscoe_hostel_2", 2, 6000),
        Hostel("jscoe_hostel_3", 2, 7000),
        Hostel("jscoe_hostel_4", 2, 8000),
        Hostel("jscoe_hostel_5", 2, 9000)
    };
    for (int i = 0; i < 5; ++i) {
        Hostel& h = hostels[i];
        int intB = h.getBed();
        int intF = h.getFee(); 

        std::stringstream ss, as;
        ss << intB;
        std::string strB = ss.str();

        as << intF;
        std::string strF = as.str();

        std::string insert = "INSERT INTO hostel(Name, Bed, Fee) VALUES ('" + h.getName() + "', '" + strB + "', '" + strF + "' )";
        std::cout << "Insert Query: " << insert << std::endl;

        if (mysql_query(conn,insert.c_str())) {
            std::cout << "Error: " << mysql_error(conn) << std::endl;
        }
        else {
            std::cout << "Inserted Successfully!" << std::endl;
        }
    }

    // Committing the transaction
    if (mysql_query(conn, "COMMIT")) {
        std::cout << "Error committing transaction: " << mysql_error(conn) << std::endl;
        return 1;
    }


    bool exit = false;

    while (!exit) {
        system("cls");

        std::cout << "Welcome To Hostel Management System" << std::endl;
        std::cout << "***********************************" << std::endl;

        std::cout << "Available Hostels:" << std::endl;
        for (int i = 0; i < 5; ++i) {
            std::cout << i + 1 << ". " << "Name: " << hostels[i].getName() << ", Fee: " << hostels[i].getFee() << std::endl;
        }

        std::cout << "Enter the number of the hostel you want to choose OR type 0 for exit: ";
        int choice;
        std::cin >> choice;
         if (choice == 0) {
         	exit = true;
		 }

        if (choice >= 1 && choice <= 5) {
            std::cout << "You have chosen: " << hostels[choice - 1].getName() << std::endl;

            std::cout << "1. Reserve Bed" << std::endl;
            std::cout << "2. Exit" << std::endl;
            std::cout << "Enter Your Choice: ";
            int val;
            std::cin >> val;

            if (val == 1) {
                std::string studentName;
                std::cout << "Enter Student Name: ";
                std::cin >> studentName;

                int total;
                std::string check = "SELECT Bed FROM hostel WHERE Name = '" + hostels[choice ].getName() + "'";
                if (mysql_query(conn, check.c_str())) {
                    std::cout << "Error: " << mysql_error(conn) << std::endl;
                } else {
                    MYSQL_RES* res;
                    res = mysql_store_result(conn);
                    if (res) {
                        MYSQL_ROW row = mysql_fetch_row(res);
                        if (row) {
                            total = atoi(row[0]);
                        }
                        mysql_free_result(res);
                    }
                }

                if (total > 0) {
                    total--;
                    std::stringstream zs;
                    zs << total;
                    std::string strT = zs.str();

                    std::string update = "UPDATE hostel SET Bed = '" + strT + "' WHERE Name='" + hostels[choice ].getName() + "' ";
                    if (mysql_query(conn, update.c_str())) {
                        std::cout << "Error: " << mysql_error(conn) << std::endl;
                    } else {
                        std::cout << "Bed is Reserved Successfully in " << hostels[choice ].getName() << " Hostel For Student " << studentName << std::endl;
                        std::cout << "Please Pay " << hostels[choice ].getFee() << " Rupees." << std::endl;
                    }
                } else if (total == 0) {
                    std::cout << "Sorry! No Bed Available" << std::endl;
                }
                Sleep(8000);
            } else if (val == 2) {
                exit = true;
                std::cout << "Goodbye!" << std::endl;
                Sleep(3000);
            } else {
                std::cout << "Invalid Input" << std::endl;
                Sleep(3000);
            }
        } else {
            std::cout << "Invalid choice!" << std::endl;
        }
    }

    mysql_close(conn);

    return 0;
}

    
