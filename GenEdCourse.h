#ifndef GENED_H_
#define GENED_H_
#include <string>
#include "Course.h"
namespace sict {
	class GenEdCourse : public Course {
		// Provides a friendship for the class GenEdCourseTester, to access this classes members.
		friend class GenEdCourseTester;
	private:
		int langLevel_;
	public:
		// An no arguement constructor to initalize member variables.
		GenEdCourse();
		// A five argument constructor that sets the langLevel_ and that calls the four arguement constructor 
		// from course to set the course code, title, credits, and study load.
		GenEdCourse(const char*, const char*, int, int, int);
		// A getter that returns langLevel_.
		int getLangLevel() const;
		// A setter that sets the langLevel_ of the current object.
		void setLangLevel(int);
		// A display function that accepts a reference to ostream, displays the course information using the ostream reference, and then returns it.
		std::ostream& display(std::ostream& os) const;
		// A store function that accepts a fstream reference, writes the course information to the fstream, and returns it.
		std::fstream& store(std::fstream& fileStream, bool addNewLine) const;
		// A load function that accepts a fstream reference, reads the course information from it, uses setters to store the information into the 
		// current object, and returns the fstream reference.
		std::fstream& load(std::fstream& fileStream);
		// A read function that accepts a fstream reference, takes in user input, and uses the setters to set the values in the member 
		// variables of the current object.
		std::istream& read(std::istream& istr);
	};
	// A helper operator that accepts an ostream reference and an object of the GenEdCourse class, calls the display function, and returns  the ostream reference.
	std::ostream& operator<<(std::ostream&, const GenEdCourse&);
}
#endif
