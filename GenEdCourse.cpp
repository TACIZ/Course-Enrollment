#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "GenEdCourse.h"
#include "ICTCourse.h"
namespace sict {
	GenEdCourse::GenEdCourse() {
		langLevel_ = 0;
	}
	GenEdCourse::GenEdCourse(const char* coursecode, const char* coursetitle, int credits, int studyload, int lang) : Course(coursecode, coursetitle,
		credits, studyload) {
		langLevel_ = lang;
	}
	int GenEdCourse::getLangLevel() const {
		return langLevel_;
	}
	void GenEdCourse::setLangLevel(int value) {
		langLevel_ = value;
	}
	std::ostream& operator<<(std::ostream& os, const GenEdCourse& obj) {
		obj.display(os);
		return os;
	}
	std::ostream& GenEdCourse::display(std::ostream& os) const {
		Course::display(os);
		os << std::setw(9) << std::right << "|" << std::setw(12) << std::right << langLevel_ << std::setw(1) << std::right << "|";
		return os;
	}
	std::fstream& GenEdCourse::store(std::fstream& fileStream, bool addNewLine) const {
		if (fileStream.is_open()) {
			fileStream << TYPE_GEN;
			Course::store(fileStream, false);
			fileStream << langLevel_;
			if (addNewLine == true) {
				fileStream << '\n';
			}

		}
		return fileStream;
	}
	std::fstream& GenEdCourse::load(std::fstream& fileStream) {
		std::string lang;
		int sl;
		if (fileStream.is_open()) {
				Course::load(fileStream);
				getline(fileStream, lang, '\n');
				std::stringstream conv(lang);
				conv >> sl;
				langLevel_ = sl;

		}
		return fileStream;
	}
	std::istream& GenEdCourse::read(std::istream& istr) {
		int lang;
		Course::read(istr);
		std::cout << "Language Requirement: ";
		istr >> lang;
		langLevel_ = lang;
		return istr;
	}
}
