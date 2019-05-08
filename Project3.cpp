// Project3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include "targetver.h"
#include "ServerAPI.h"
#include <vector>
#include <string>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

///////////////////////////////////Initial setup of Business Table//////////////////////////////////////////
Table business_build() {
	ifstream businput("business.json");
	vector<json> businesses;
	json temp;
	Table busi({ "business_id", "name", "city", "state","review_count", "Monday", "Tuesday", "Wednesday", 
		"Thursday", "Friday", "Saturday", "Sunday" });
	vector<Record> b_rec(50);
	Record tmp;

	int i = 0;
	while (i < 50) {
		businput >> temp;
		businesses.push_back(temp);
		i++;
	}
	Record r;
	///////////////////////////////////Filling business table////////////////////////////////////////////////////
	for (int j = 0; j < 50; j++) {
		
		double temp_num = (businesses[j]["review_count"]);
		
		tmp.elems.push_back(businesses[j]["business_id"]);
		tmp.elems.push_back(businesses[j]["name"]);
		tmp.elems.push_back(businesses[j]["city"]);
		tmp.elems.push_back(businesses[j]["state"]);
		
		tmp.elems.push_back(to_string(temp_num));

		if (!businesses[j]["hours"]["Monday"].empty()) {
			tmp.elems.push_back(businesses[j]["hours"]["Monday"]);
		}
		if (!businesses[j]["hours"]["Tuesday"].empty()) {
			tmp.elems.push_back(businesses[j]["hours"]["Tuesday"]);
		}
		if (!businesses[j]["hours"]["Wednesday"].empty()) {
			tmp.elems.push_back(businesses[j]["hours"]["Wednesday"]);
		}
		if (!businesses[j]["hours"]["Thursday"].empty()) {
			tmp.elems.push_back(businesses[j]["hours"]["Thursday"]);
		}
		if (!businesses[j]["hours"]["Friday"].empty()) {
			tmp.elems.push_back(businesses[j]["hours"]["Friday"]);
		}
		if (!businesses[j]["hours"]["Saturday"].empty()) {
			tmp.elems.push_back(businesses[j]["hours"]["Saturday"]);
		}
		if (!businesses[j]["hours"]["Sunday"].empty()) {
			tmp.elems.push_back(businesses[j]["hours"]["Sunday"]);
		}
	
		//b_rec.push_back(tmp);
		
		busi.insertRecord(&tmp);
		tmp = r;
	}


	return busi;

}

Table user_build() {
	///////////////////////////////////Initial setup of User Table//////////////////	
	ifstream userinput("user.json");

	vector<json> users;
	json temp;
	Table use({"name", "review_count", "yelping_since", "useful", "fans", "average_stars","user_id" });
		vector <Record> u_rec(100);
	Record tmp;

	int i = 0;
	while (i < 100) {
		userinput >> temp;
		users.push_back(temp);
		i++;
	}
	Record r;
	///////////////////////////////////Filling user table///////////////////////	
	for (int j = 0; j < 100; j++) {
		double temp_num1 = (users[j]["review_count"]);
		double temp_num2 = (users[j]["useful"]);
		double temp_num3 = (users[j]["fans"]);
		double temp_num4 = (users[j]["average_stars"]);

		
		tmp.elems.push_back(users[j]["name"]);
		tmp.elems.push_back(to_string(temp_num1));
		tmp.elems.push_back(users[j]["yelping_since"]);
		tmp.elems.push_back(to_string(temp_num2));
		tmp.elems.push_back(to_string(temp_num3));
		tmp.elems.push_back(to_string(temp_num4));
		tmp.elems.push_back(users[j]["user_id"]);

		use.insertRecord(tmp);
		tmp = r;
	}

	return use;
}

Table review_build() {
	///////////////////////////////////Initial setup of review Table//////////////////
	ifstream reviewinput("review.json");
	vector<json> reviews;
	json temp;
	Table rev({ "text","user_id",  "stars","business_id" });
		vector <Record> rev_rec(100);
	Record tmp;

	int i = 0;
	while (i < 100) {
		reviewinput >> temp;
		reviews.push_back(temp);
		i++;
	}
	Record r;
	///////////////////////////////////Filling review table///////////////////////	
	for (int j = 0; j < 100; j++) {
		double temp_num = reviews[j]["stars"];



		tmp.elems.push_back(reviews[j]["text"]);
		tmp.elems.push_back(reviews[j]["user_id"]);
		tmp.elems.push_back(to_string(temp_num));
		tmp.elems.push_back(reviews[j]["business_id"]);

		rev.insertRecord(tmp);
		tmp = r;
	}

	return rev;
}


void print_table_four(Table t) {
	vector<string> att = t.getAttributes();

	cout << "name" << setw(15) << "review count" << setw(15) << "yelping since" << setw(13) << "useful" << setw(13) << "fans" << setw(20) << "avg score" << setw(18) << "user id";
	cout << endl;
	vector<Record> rec_v;

	for (int i = 0; i < t.records.size(); i++) {
		rec_v.push_back(t.records[i]);
	}


	for (int j = 0; j < rec_v.size(); j++) {
		for (int k = 0; k < rec_v[j].getSize(); k++) {
		
			cout << rec_v[j][k] << "\t";
		
		}

		cout << endl;
	}
}

void print_table_one(Table t) {
	vector<string> att = t.getAttributes();
	
	cout << "Business ID" << setw(25) << "Name" << setw(17) << "State" << endl;

	vector<Record> rec_v;
	for (int i = 0; i < t.records.size(); i++)
		rec_v.push_back(t.records[i]);

	for (int j = 0; j < rec_v.size(); j++) {
		for (int k = 0; k < rec_v[j].getSize(); k++) {
			cout << rec_v[j][k] << "\t";
		}

		cout << endl;
	}
}

void print_table_time(Table t) {
	
	cout << "name" << setw(27) << "M" << setw(16) << "T" << setw(16) << "W" << setw(16) << "Th" << setw(16) << "F" << setw(16) << "Sat" << setw(16) << "Sun" << endl;

	cout << endl;

	vector<Record> rec_v;
	for (int i = 0; i < t.records.size(); i++)
		rec_v.push_back(t.records[i]);

	for (int j = 0; j < rec_v.size(); j++) {
		for (int k = 0; k < rec_v[j].getSize(); k++) {
			cout << rec_v[j][k] << "\t";
		}

		cout << endl;
	}
}

void print_table_two(Table t) {
	vector<string> att = t.getAttributes();

	cout << "Business ID" << setw(23) << "Name" << setw(25) << "City" << setw(16) << "State" << setw(17) << "Review Count" << endl;

	vector<Record> rec_v;
	for (int i = 0; i < t.records.size(); i++)
		rec_v.push_back(t.records[i]);

	for (int j = 0; j < rec_v.size(); j++) {
		for (int k = 0; k < rec_v[j].getSize(); k++) {
			cout << rec_v[j][k] << "\t";
		}

		cout << endl;
	}
}




int main() {

	string option;
	
	Database db;
	Table query;
	Table business = business_build();
	Table users = user_build();
	Table reviews = review_build();
	string searchoption;
	db.addTable(business,"business");
	db.addTable(users,"users");
	db.addTable(reviews,"reviews");

	while (option != "quit") {
		cout << "Welcome to the main menu! " << endl;
		cout << "Please type the number of what option you would like to proceed with: " << endl;
		cout << "1 - Find a business" << endl;
		cout << "2 - More information about a business" << endl;
		cout << "3 - Reviews about a business" << endl;
		cout << "4 - More information about a user" << endl;
		cout << "Enter <quit> if you would like to exit." << endl;


		cin >> option;
		if (option == "quit")
			break;

		if (option == "1") {
			cout << "How would you like to search for a business?" << endl;
			cout << "You can search by <city> or <state>." << endl;
			cout << "You can also type <main> to go back to the main menu. " << endl;
			cin >> searchoption;
			if (searchoption == "main") {
				cout << endl << endl << endl << endl;
				continue;
			}

			if (searchoption == "city") {
				string searchcity;
				cout << "Enter a city without spaces. Example: Houston" << endl;
				cin.ignore();
				getline(cin, searchcity);
				query = db.query("business_id, name, city", "business", "city = " + searchcity);
				cout << endl << endl << endl << endl;
				print_table_one(query);
				cout << endl << endl << endl << endl;
				continue;
			}

			if (searchoption == "state") {
				string searchstate;
				cout << "Enter a states initials. Example: TX" << endl;
				cin >> searchstate;
				query = db.query("business_id, name, state", "business", "state = " + searchstate);
				cout << endl << endl << endl << endl;
				print_table_one(query);
				cout << endl << endl << endl << endl;
				continue;
			}

		}

		if (option == "2") {
			cout << "How would you like to find the business?" << endl;
			cout << "It can be found by <name> or <business_id> (Case Sensative)" << endl;
			cout << "You can also type <main> to go back to the main menu. " << endl;
			cin >> searchoption;
			string yesorno;
			if (searchoption == "main") {
				cout << endl << endl << endl << endl;
				continue;
			}

			if (searchoption == "name") {
				string searchname;
				
				cout << "Enter the name of the business you would like to search" << endl;
				cin.ignore();
				getline(cin, searchname);
				
				query = db.query("business_id, name, city, state, review_count", "business", "name = " + searchname);
				cout << endl << endl << endl << endl;
				print_table_two(query);
				cout << endl << endl << endl << endl;

				cout << "Would you like the hours of operation?" << endl;
				string a;
				cin >> a;
				
				if (a == "yes") {
					query = db.query("name, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday", "business", "name = " + searchname);
					cout << endl << endl << endl << endl;
					print_table_time(query);
					cout << endl << endl << endl << endl;
				}

				cout << endl << endl << endl << endl;
				continue;
			}

			if (searchoption == "business_id") {
				string searchid;
				cout << "Enter the <business_id> of the business you would like to search. (This is case sensative)" << endl;
				cin >> searchid;
				query = db.query("business_id, name, city, state, stars, review_count", "business", "business_id = " + searchid);
				cout << endl << endl << endl << endl;
				print_table_two(query);
				cout << endl << endl << endl << endl;

				cout << "Would you like the hours of operation?" << endl;
				cin >> yesorno;
				if (yesorno == "yes") {
					query = db.query("name, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday", "business", "business_id = " + searchid);
					cout << endl << endl << endl << endl;
					print_table_time(query);
					cout << endl << endl << endl << endl;
				}
				cout << endl << endl << endl << endl;
				continue;
			}
		}

		if (option == "3") {
			cout << "Enter the <business_id> you would like to return reviews for. " << endl;
			cout << "You can also type <main> to return to the main menu. " << endl;
			string searchid;
			cin >> searchid;

			if (searchid == "main") {
				cout << endl << endl << endl << endl;
				continue;
			}

			query = db.query("text, user_id, stars, useful", "reviews", "business_id = " + searchid);
			vector<string> att = query.getAttributes();
			cout << endl;
			for (int i = 1; i < att.size(); i++)
				cout << att[i] << "\t" << "\t" << "\t";
			cout << endl;
			vector<Record> rec_v;
			for (int i = 0; i < query.getNumRecords(); i++)
				rec_v.push_back(query.records[i]);
			cout << endl;
			for (int j = 0; j < rec_v.size(); j++) {
				for (int k = 1; k < rec_v[j].getSize(); k++) {
					cout << rec_v[j][k] << "\t";
				}
				cout << endl;
				cout << endl << rec_v[j][0] << endl;
			}
			cout << endl;
			cout << endl << endl << endl << endl;
			continue;

		}

		if (option == "4") {
			string searchid;
			cout << "Enter the <user_id> you would like to return information on. " << endl;
			cout << "You can also type <main> to return to the main menu. " << endl;
			cin >> searchid;

			if (searchid == "main") {
				cout << endl << endl << endl << endl;
				continue;
			}

			query = db.query("user_id, name, review_count, yelping_since, useful, fans, average_stars", "users", "user_id = " + searchid);
			cout << endl << endl << endl << endl;
			print_table_four(query);
			cout << endl << endl << endl << endl;
			continue;

		}

	}
}