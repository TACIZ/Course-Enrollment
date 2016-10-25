#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include "Course.h"
namespace sict {
	Course::Course() {
		courseCode_[0] = '\0';
		courseTitle_ = nullptr;
		courseCredits_ = 0;
		studyLoad_ = 0;
	}
	Course::Course(const char* cc, const char* ct, int cred, int sl) {
		strncpy(courseCode_, cc, MAX_COURSECODE_LEN + 1);
		courseTitle_ = new char[strlen(ct) + 1];
		strcpy(courseTitle_, ct);
		courseCredits_ = cred;
		studyLoad_ = sl;
	}
	Course::Course(const Course& copy) {
		courseTitle_ = nullptr;
		*this = copy;
	}
	Course& Course::operator=(const Course& copy) {
		if (this != &copy) {
			courseCredits_ = copy.courseCredits_;
			studyLoad_ = copy.studyLoad_;
			strcpy(courseCode_, copy.courseCode_);
			if (courseTitle_ != nullptr) {
				delete[] courseTitle_;
			}
			if (copy.courseTitle_ != nullptr) {
				courseTitle_ = new char[strlen(copy.courseTitle_) + 1];
				strcpy(courseTitle_, copy.courseTitle_);
			}
			else
				courseTitle_ = nullptr;
		}
		return *this;
	}
	void Course::setCourseCode(const char* code) {
		strcpy(courseCode_, code);
	}
	void Course::setCourseTitle(const char* title) {
		if (courseTitle_ != nullptr) {
			delete[] courseTitle_;
			courseTitle_ = nullptr;
		}
		courseTitle_ = new char[strlen(title) + 1];
		strcpy(courseTitle_, title);
	}
	void Course::setCredits(int credits) {
		courseCredits_ = credits;
	}
	void Course::setStudyLoad(int load) {
		studyLoad_ = load;
	}
	const char* Course::getCourseCode() const {
		return courseCode_;
	}
	char* Course::getCourseTitle() const {
		return courseTitle_;
	}
	int Course::getCredits() const {
		return courseCredits_;
	}
	int Course::getStudyLoad() const {
		return studyLoad_;
	}
	bool Course::isEmpty() {
		bool var;
		if (courseCode_[0] == '\0' || courseTitle_ == nullptr || courseTitle_[0] == '\0' || courseCredits_ == -1 || courseCredits_ == 0 || studyLoad_ == -1 || studyLoad_ == 0) {
			var = true;
		}
		else
			var = false;
		return var;
	}
	bool Course::operator==(const char* cmp) {
		bool var;
		if (strcmp(courseCode_, cmp) != 0) {
			var = false;
		}
		else
			var = true;
		return var;
	}
	int Course::operator+=(int sL) {
		studyLoad_ += sL;
		return studyLoad_;
	}
	std::ostream& Course::display(std::ostream& os) const {
		os << std::setw(2) << std::right << "|" << std::setw(6) << std::right << getCourseCode() << std::setw(1) << std::right << "|";
		os << std::setw(41) << std::left << getCourseTitle() << std::setw(1) << std::right << "|" << std::setw(9) << std::right << getCredits();
		os << std::setw(1) << std::right << "|" << std::setw(12) << std::right << getStudyLoad() << std::setw(1) << std::right << "|";
		return os;
	}
	std::ostream& operator<<(std::ostream& os, const Course& obj) {
		obj.display(os);
		return os;
	}
	std::fstream& Course::store(std::fstream& fileStream, bool addNewLine) const {
		if (fileStream.is_open()) {
			fileStream << "," << getCourseCode() << "," << getCourseTitle() << "," << getCredits() << "," << getStudyLoad() << ",";
			if (addNewLine == true) {
				fileStream << '\n';
			}
		}
		return fileStream;
	}
	std::fstream& Course::load(std::fstream& fileStream) {
		std::string code;
		std::string title;
		std::string credits;
		std::string load;

		if (fileStream.is_open()) {

				getline(fileStream, code, ',');

				getline(fileStream, title, ',');

				getline(fileStream, credits, ',');

				getline(fileStream, load, ',');

		}
		int cred;
		int sload;
		std::stringstream convc(credits);
			convc >> cred;
		std::stringstream convl(load);
			convl >> sload;
		setCourseCode(code.c_str());
		setCourseTitle(title.c_str());
		setCredits(cred);
		setStudyLoad(sload);
		return fileStream;
	}
	std::istream& Course::read(std::istream& istr) {

		std::string title;
		std::string code;
		int cred;
		int sl;

		std::cout << "Course Code: ";
		getline(istr, code);
		setCourseCode(code.c_str());
		std::cout << "Course Title: ";
		getline(istr, title);
		setCourseTitle(title.c_str());
		std::cout << "Course Credit: ";
		istr >> cred;
		setCredits(cred);
		std::cout << "Study Load: ";
		istr >> sl;
		setStudyLoad(sl);

		return istr;
	}
	Course::~Course() {
		delete[] courseTitle_;
		courseTitle_ = nullptr;
	}
}
