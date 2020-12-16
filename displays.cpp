#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

// #include "structures.cpp"

using namespace std;

void displayAllProducts(const vector<productsOnCart> cart)
{
  // products in cart iterator
  cout << "\n\nID | Product | Price | Quantity | Amount \n";
  size_t size = cart.size();
  for (int i = 0; i < size; i++)
  {
    productsOnCart p = cart[i];
    cout << p.productID << " | ";
    cout << p.productName << "  | ";
    cout << p.price << " |  ";
    cout << p.quantity << " | ";
    cout << p.amount() << "\n";
  }
}

void displayBill(Bill b)
{
  // displays the bill
  cout << "\033[2J\033[1;1H"; // clear screen

  cout << "\n\n \t\t\t ~~~~~~~~~~~~~~~~~~~~ \n\n";
  cout << "\n\n \t\t\t\t BILL RECEIPT \n\n\n\n ";
  cout << "\t\t\t\t EZ-MART\n";
  cout << "\t\t\t Churchgate, Mumbai| 400021\n";
  cout << "\t\t\t     +91-9123456780 \n";

  cout << "\n\n Bill Number: " << b.billNumber;
  cout << "\n \t Billing Time: " << b.createdAt;
  cout << "\n Customer Name: " << b.customer.name;
  cout << "\n Customer Phone: " << b.customer.phone;
  cout << "\n Customer Email: " << b.customer.email;

  displayAllProducts(b.cart);

  cout << "\n\n Amount Before Tax: " << b.taxableAmount;
  cout << "\n Total Quantities: " << b.quantity;
  cout << "\n Tax: " << (TAX * 100) << "%";
  cout << "\n Net Payable: " << b.netAmount;
  cout << "\n\n Mode of Payment: " << b.mode;
  cout << "\n Paid: " << b.amountPaid;
  cout << "\n\n Amount Overdue in Total by " << b.customer.name << " : " << b.dueAmount;

  cout << "\n\n\n Thank you for visiting!!";
  cout << "\n\n \t\t\t ~~~~~~~~~~~~~~~~~ \n\n";
}
