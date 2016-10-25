#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <fstream>
#include "general.h"
#include "ICTCourse.h"
namespace sict {
	ICTCourse::ICTCourse() {
		strcpy(computerSystem_, "matrix");
	}
	ICTCourse::ICTCourse(const char* courseCode, const char* courseTitle, int credits, int studyLoad, const char* cpS) : Course(courseCode, courseTitle,
		credits, studyLoad) {
		if (strcmp(cpS, "") != 0 && cpS != nullptr) {
			strcpy(computerSystem_, cpS);	
		}
		else
			strcpy(computerSystem_, "error!");
	}
	const char* ICTCourse::getComputerSystem() const {
		return computerSystem_;
	}
	void ICTCourse::setComputerSystem(const char* value) {
		strcpy(computerSystem_, value);
	}
	std::ostream& operator<<(std::ostream& os, const ICTCourse& obj) {
		obj.display(os);
		return os;
	}
	std::ostream& ICTCourse::display(std::ostream& os) const {
		Course::display(os);
		os << std::setw(8) << std::right << computerSystem_ << std::setw(1) << std::right << "|" << std::right << std::setw(13) << "|";
		return os;
	}
	std::fstream& ICTCourse::store(std::fstream& fileStream, bool addNewLine) const {
		if (fileStream.is_open()) {
			fileStream << TYPE_ICT; 
			Course::store(fileStream, false);
			fileStream << computerSystem_;
			if (addNewLine == true) {
				fileStream << '\n';
			}
		}	
		return fileStream;
	}
	std::fstream& ICTCourse::load(std::fstream& fileStream) {
		std::string system;
		if (fileStream.is_open()) {
				Course::load(fileStream);
				getline(fileStream, system, '\n');
				strcpy(computerSystem_, system.c_str());
		}
		return fileStream;
	}
	std::istream& ICTCourse::read(std::istream& istr) {
		std::string cps;
		Course::read(istr);
        std::cout << "Computer System: ";
		istr >> cps;
		strcpy(computerSystem_, cps.c_str());
		return istr;
	}
}		
