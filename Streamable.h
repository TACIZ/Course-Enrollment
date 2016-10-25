#ifndef STREAMABLE_H_
#define STREAMABLE_H_
#include <fstream>
namespace sict {
	class Streamable {
		public:
			// Pure virtual functions that initialize this class to be abstract, and makes every derived class require a definition of each. 
			virtual std::fstream& store(std::fstream& file, bool addNewLine = true) const = 0;
			virtual std::fstream& load(std::fstream& file) = 0;
			virtual std::ostream& display(std::ostream& os) const = 0;
		    virtual std::istream& read(std::istream& is) = 0;
	};
}
#endif	
