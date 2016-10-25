#ifndef COURSE_H_
#define COURSE_H_
#include "Streamable.h"
#include "general.h"
namespace sict {
	class Course : public Streamable {
		// Provides a friendship for the class CourseTester, to access this classes members.
		friend class CourseTester;
	private:
		char courseCode_[MAX_COURSECODE_LEN + 1];
		char* courseTitle_;
		int courseCredits_;
		int studyLoad_;
	public:
		// An no arguement constructor to initalize member variables.
		Course();
		// A four argument constructor to set the course code, title, credits, and study load.
		Course(const char* cc, const char* ct, int cred, int sl);
		// A copy constructor to set the member variables of a new instance of this class using the values of an existing instance of the class.
		Course(const Course&);
		// An assignment operator that is used to change one instance of a class with the values of another, assuming it is not the same object.
		Course& operator=(const Course&);
		// A setter for the course code.
		void setCourseCode(const char*);
		// A setter for the course title, that deletes the existing the title, before allocating memory for a new one.
		void setCourseTitle(const char*);
		// A setter for course credits.
		void setCredits(int);
		// A setter for the course study load.
		void setStudyLoad(int);
		// A getter for the course code.
		const char* getCourseCode() const;
        // A getter for the course title.
		char* getCourseTitle() const;
		// A getter fot the course credits.
		int getCredits() const;
		// A getter for the course study load.
		int getStudyLoad() const;
		// A function to check if any member variables of the current object were set to a safe empty state.
		bool isEmpty();
		// An equals equals operator that checks if the string passed in is equal to the other string.
		bool operator==(const char *);
		// A plus equals operator that adds a value to an existing integer and returns the result.
		int operator+=(int);
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
		// A virtual destructor that deletes the course title, and sets it to nullptr. Set to virtual to ensure the most derived classes destructor to be called.
		virtual ~Course();
	};
	// A helper operator that accepts an ostream reference and an object of the Course class, calls the display function, and returns  the ostream reference.
	std::ostream& operator<<(std::ostream&, const Course&);
}
#endif
