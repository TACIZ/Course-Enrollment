#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <fstream>
#include "ScmApp.h"
#include "ICTCourse.h"
#include "GenEdCourse.h"
namespace sict {
	ScmApp::ScmApp() {
		for (int i = 0; i < MAX_NO_RECS; i++) {
			courseList_[i] = nullptr;
		}
		noOfCourses_ = 0;
	}
	void ScmApp::pause() const {
		std::cout << "Press Enter to continue..." << std::endl;
		while (getchar() != '\n') {}
	}
	int ScmApp::menu() {
		int input;
		std::cout << "Seneca Course Management Tool" << std::endl;
		std::cout << "1- List courses." << std::endl;
		std::cout << "2- Display the details of a course." << std::endl;
		std::cout << "3- Add a course." << std::endl;
		std::cout << "4- Change the study load of a course." << std::endl;
		std::cout << "5- Load courses from a file." << std::endl;
		std::cout << "6- Save courses to a file." << std::endl;
		std::cout << "0- Exit Program" << std::endl;
		std::cout << ">";
		std::cin >> input;
		std::cout << std::endl;
		std::cin.ignore();
		if (input < 0 || input > 6)
			input = -1;
		return input;


	}
	ScmApp::ScmApp(const char* filename) {
		strcpy(filename_, filename);

		for (int i = 0; i < MAX_NO_RECS; i++) {
			courseList_[i] = nullptr;
		}
		noOfCourses_ = 0;
	}
	void ScmApp::listCourses() const {

		std::cout << " Row | Code |               Course Title              | Credits | Study Load | System | Lang. Req. |" << std::endl;
		std::cout << "-----|------|-----------------------------------------|---------|------------|--------|------------|" << std::endl;
		if (courseList_[0] != nullptr) {
			for (int i = 0; i < noOfCourses_; i++) {
				std::cout << std::setw(4) << std::right << i;
				std::cout << *courseList_[i] << std::endl;
				if (i == 10) {
					pause();
				}
			}
		}
		std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << std::endl;
	}
	int ScmApp::searchACourse(const char* courseCode) const {
		int k = -1;
		for (int i = 0; i < noOfCourses_; i++) {
			if (*(courseList_[i]) == courseCode) {
				k = i;
			}
		}
		return k;
	}
	void ScmApp::changeStudyLoad(const char* courseCode) {
		int var = searchACourse(courseCode);
		int sl;
		if (var == -1) {
			std::cout << "Not found!" << std::endl;
		}
		else {
			std::cout << "Please enter the amount of the study load: ";
			std::cin >> sl;
			int load = courseList_[var]->getStudyLoad();
			load += sl;
			courseList_[var]->setStudyLoad(load);
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
	void ScmApp::addACourse(int coursetype) {
		if (coursetype == 1) {
			courseList_[noOfCourses_] = new ICTCourse;
			courseList_[noOfCourses_]->read(std::cin);
			noOfCourses_++;
		}
		if (coursetype == 2) {
			courseList_[noOfCourses_] = new GenEdCourse;
			courseList_[noOfCourses_]->read(std::cin);
			noOfCourses_++;
		}
		std::cout << std::endl;
	}
	void ScmApp::loadRecs() {
		int readindex = 0;
		std::string type;

		dataFile_.open(filename_, std::ios::in);



		if (dataFile_.is_open()) {

			empty();
			while (!dataFile_.eof()) {

				getline(dataFile_, type, ',');

				    if(type == TYPE_GEN){

						courseList_[readindex] = new GenEdCourse;
						courseList_[readindex]->load(dataFile_);
						readindex++;
					}
					if (type == TYPE_ICT) {

						courseList_[readindex] = new ICTCourse;
						courseList_[readindex]->load(dataFile_);
						readindex++;
					}
			}
			noOfCourses_ = readindex;
			dataFile_.close();
		}
	}
	void ScmApp::saveRecs() {
		dataFile_.open(filename_, std::ios::out);

		for (int i = 0; i < noOfCourses_; i++) {
			if (i == (noOfCourses_ - 1)) {
				courseList_[i]->store(dataFile_, false);
			}
			else {
				courseList_[i]->store(dataFile_, true);
			}
		}
		dataFile_.close();
	}
	int ScmApp::run() {
		int counter = 0;
		int coursetype;
		char code[MAX_NO_RECS];
		char scode[MAX_NO_RECS];
		do {
			int i = menu();
			switch (i) {
			case 0:
				std::cout << "Goodbye!!" << std::endl;
				counter = 1;
				break;
			case 1:
				listCourses();
				break;
			case 2:
				std::cout << "Please enter the course code: ";
				std::cin >> code;
				if (searchACourse(code) != -1) {
					int k = searchACourse(code);
					std::cout << std::setw(4) << std::right << k << *courseList_[k];
				}
				else
					std::cout << "Not found!";
				break;
			case 3:
				std::cout << "Please enter the course type (1-ICT or 2-GenEd): ";
				std::cin >> coursetype;
				std::cin.ignore();
				addACourse(coursetype);
				break;
			case 4:
				std::cout << std::endl;
				std::cout << "Please enter the course code : ";
				std::cin >> scode;
				changeStudyLoad(scode);
				break;
			case 5:
				loadRecs();
				break;
			case 6:
				saveRecs();
				break;
			default:
				std::cout << "===Invalid Selection, try again.===" << std::endl;
				pause();
				break;
			}
		} while (counter != 1);
		return 0;
	}
	void ScmApp::empty() {
		for (int i = 0; i < noOfCourses_; i++) {
				delete courseList_[i];
				courseList_[i] = nullptr;
		}
	}
	ScmApp::~ScmApp() {
		empty();
	}

}
