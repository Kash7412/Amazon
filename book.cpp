#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string ISBN, std::string author) :
    Product(category, name, price, qty), //change to use super constructor notation
    isbn_(ISBN),
    author_(author)
{

}

Book::~Book()
{

}

/**
* Returns the appropriate keywords that this product should be associated with
*/
std::set<std::string> Book::keywords() const
{
  std::set<std::string> keys;
  keys = parseStringToWords(author_);
  keys.insert(isbn_);
  std::set<std::string> temp = parseStringToWords(name_);
  keys = setUnion(keys, temp);
  return keys;
}

/**
* Returns a string to display the product info for hits of the search
*/
std::string Book::displayString() const
{
  stringstream ss;
  ss << name_ << "\nAuthor: " << author_ << " ISBN: " << isbn_ << "\n" << price_ << " " << qty_ << " left." << endl;
  return ss.str();
}

void Book::dump(std::ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}