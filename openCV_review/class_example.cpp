#include <iostream>
#include <sstream>

class UserType;

class UserType
{
public:
	using value_type = char;
	using iterator = value_type*;
	using const_iterator = const value_type*;
	
	UserType() = default;
	virtual ~UserType() = default;
	UserType(const UserType& user);
	UserType& operator=(const UserType& user);
	UserType(UserType&& user);
	UserType& operator=(UserType&& user);

	struct DateType
	{
		DateType(int year, int month, int day)
			: year_(year), month_(month), day_(day) {}
		int year_;
		int month_;
		int day_;
		
		const std::string to_string() const
		{
			std::ostringstream oss;
			oss << year_ << "." << month_ << "." << day_;
			return oss.str();
		}
	};

	void setName(std::string str);
	void setBirth(const DateType& date);
	
	const std::string& getName() const { return str_name_;  }
	const DateType& getBirth() const { return Birth_;  }
	
private:
	std::string str_name_;
	DateType Birth_ = DateType(1900, 01, 01);
};

void UserType::setName(std::string str)
{
	str_name_ = str;
}

void UserType::setBirth(const DateType& date)
{
	Birth_ = date;
}

int maintest()
{
	UserType User;
	std::cout << User.getName() << '\t' << User.getBirth().to_string() << std::endl;
	User.setName("David");
	User.setBirth(UserType::DateType(1999, 12, 31));
	std::cout << User.getName() << '\t' << User.getBirth().to_string() <<
		std::endl;

	return EXIT_SUCCESS;
}