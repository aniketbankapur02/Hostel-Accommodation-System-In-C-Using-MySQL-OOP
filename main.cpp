//
//
///* run this program using the console pauser or add your own getch, system("pause") or input loop */
//#include <iostream>
//#include <mysql.h>
//#include <mysqld_error.h> // for error handling
//#include <windows.h>
//#include <sstream>
//
//using namespace std;
//
//const char *HOST = "localhost";
//const char *USER = "root";
//const char *PW = "root@3409";
//const char *DB = "myhostel_db";
//
//class hostel
//{
//private:
//    int Fee;
//    int Bed;
//    string Name;
//
//public:
//    hostel(string name,int bed, int fee)
//    {
//        Fee = fee;
//        Bed = bed;
//        Name = name;
//    }
//
//    string NameFun()
//    {
//        return Name;
//    }
//
//    int BedFun()
//    {
//        return Bed;
//    }
//
//    int FeeFun()
//    {
//        return Fee;
//    }
//};
//
//int main(int argc, char **argv)
//{
//
//    MYSQL *conn;
//    conn = mysql_init(NULL);
//
//    // sending connection to sql if connection happens it return 1 and !1 = 0 tell that error not occured dont runt this if block
//    // as connection is done
//    // else block will run indiaction that sql connecction is made
//    if (!mysql_real_connect(conn, HOST, USER, PW, DB, 3306, NULL, 0))
//    {
//        cout << "Error while loading " << mysql_error(conn) << endl; // mysql_error() to retrieve the error message associated with the connection attempt failure.
//    }
//    else
//    {
//        cout << "Succesfully made database connection";
//    }
//    Sleep(3000); // to show error msg for 3 sec input is in mili second a method in windows
//
//    hostel obj("3star_hostel", 2, 5000);
//
//
//int Bed = obj.BedFun();
//int fees = obj.FeeFun();
//
//stringstream s1;
//s1 << Bed;
//string bed = s1.str();
//
//stringstream s2;
//s2 << fees;
//string Fees = s2.str();
//
//string insert = "INSERT INTO hostel(Name, Bed, Fee) VALUES ('" + obj.NameFun() + "', '" + bed + "', '" + Fees + "' )";
//mysql_query(conn,insert.c_str());
//
//if(mysql_query(conn,insert.c_str())){
//	cout<<"Error: "<<mysql_error(conn)<<endl;
//}
//else{
//	cout<<"Inserted Successfuly!"<<endl;
//}
//
//
//    bool exit = false;
//
//    while (!exit)
//    {
//
//        system("cls");
//
//        cout << "Welcome to hostel accommodation system" << endl;
//        cout << "*******************************************" << endl;
//
//        cout << "1. Reserve Bed: " << endl;
//        cout << "2. Exit: " << endl;
//
//        cout << "Choose your choice :" << endl;
//        int var;
//        cin >> var;
//
//        if (var == 1)
//        {
//            string n;
//            cout << endl;
//            cout << "Enter Student Name: ";
//            cin >> n;
//
//            // now check whether bed is avaiable or not
//
//            string check = "SELECT Bed FROM hostel WHERE Name = '" + obj.NameFun() + "'  ";
//            // lets ecexute this query we use this method mysql_query(conn,.c_str())
//
//            int total_rooms;
//            if (mysql_query(conn, check.c_str()))
//            {
//                cout << "Error: " << mysql_error(conn) << endl; // if return 0
//            }
//            else
//            {
//                // if return 1
//                MYSQL_RES *res;
//                res = mysql_store_result(conn);
//                if (res)
//                {
//                    MYSQL_ROW row = mysql_fetch_row(res);
//
//                    if (row)
//                    { // got the cell value of rooms from unique hostel name
//                        total_rooms = atoi(row[0]);
//                    }
//                    mysql_free_result(res);
//
//
//                    if (total_rooms > 0)
//                    {
//                        total_rooms--;
//                    }
//
//                    // now update rooms from table
//                    // write a query for that to udate room
//
//                    stringstream s3;
//                    s3 << total_rooms;
//                    string total_room = s3.str();
//
//                    string update = "UPDATE  hostel SET Bed ='" + total_room + "' where  Name = '" + obj.NameFun() + "'  ";
//
//                    // lets ecexute this query we use this method mysql_query(conn,.c_str())
//                    if (mysql_query(conn, update.c_str()))
//                    {
//                        cout << "Error: " << mysql_error(conn) << endl; // if return 0
//                    }
//                    else if (total_rooms == 0)
//                    {
//                        cout << "No bed is avaiable sorry";
//                    }
//
//                    else
//                    {
//                        cout << endl;
//                        cout << "Successfully reserved a room for "<<" " << n << "at"<<"  "<< obj.NameFun() << endl;
//                        cout << "Please Pay " << obj.FeeFun() << " Rupees." << endl;
//                        ; // if return 1
//                    }
//                    Sleep(8000);
//
//                }
//			}
//		} // if end
//                else if (var == 2)
//                {
//                    exit = true;
//                    cout << "Good Luck" << endl;
//                    Sleep(3000);
//                }
//                else
//                {
//                    cout << "Invalid Input" << endl;
//                    Sleep(3000);
//                }
//            
//        
//	}// end while
//        mysql_close(conn);
//
//        return 0;
//    }
//    
//    
    

#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <windows.h>
#include <sstream>
using namespace std;
const char *HOST = "localhost";
const char *USER = "root";
const char *PW = "root@3409";
const char *DB = "myhostel_db";

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

    
