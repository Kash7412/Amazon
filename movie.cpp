#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating) :
    Product(category, name, price, qty),
    genre_(genre),
    rating_(rating)
{

}

Movie::~Movie()
{

}

/**
* Returns the appropriate keywords that this product should be associated with
*/
std::set<std::string> Movie::keywords() const
{
  std::set<std::string> keys;
  keys = parseStringToWords(name_);
  keys.insert(convToLower(genre_));
  return keys;
}

/**
* Returns a string to display the product info for hits of the search
*/
std::string Movie::displayString() const 
{
  stringstream ss;
  ss << name_ << "\nGenre: " << genre_ << " Rating: " << rating_ << "\n" << price_ << " " << qty_ << " left." << endl;
  return ss.str();
}

void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}