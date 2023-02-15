#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) :
    Product(category, name, price, qty),
    size_(size),
    brand_(brand)
{

}

Clothing::~Clothing()
{

}

/**
* Returns the appropriate keywords that this product should be associated with
*/
std::set<std::string> Clothing::keywords() const
{
  std::set<std::string> keys;
  keys = parseStringToWords(brand_);
  std::set<std::string> temp = parseStringToWords(name_);
  keys = setUnion(keys, temp);
  return keys;
}

/**
* Returns a string to display the product info for hits of the search
*/
std::string Clothing::displayString() const 
{
  stringstream ss;
  ss << name_ << "\nSize: " << size_ << " Brand: " << brand_ << "\n" << price_ << " " << qty_ << " left." << endl;
  return ss.str();
}

void Clothing::dump(std::ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}