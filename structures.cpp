#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 6 %
#define TAX 0.06

string csv = ".csv";

struct Customer
{
  string name, email, address, phone;
  int lastBillNumber;
  float amountDue;
};

struct productsOnCart
{
  int productID;
  string productName;
  float price;
  int quantity;
  float amount()
  {
    return (float)price * quantity;
  }
};

struct Bill
{
  int billNumber;
  string createdAt;
  Customer customer;
  int quantity;
  vector<productsOnCart> cart;
  string mode; // mode of Payment
  float amountPaid, taxableAmount, netAmount, dueAmount;

  float amountBeforeTax()
  {
    size_t size = cart.size();
    float amt = 0.00;
    quantity = 0;
    for (int i = 0; i < size; i++)
    {
      productsOnCart p = cart[i];
      quantity += p.quantity;
      amt += p.price * p.quantity;
    }
    // taxableAmount = amt;
    return amt;
  }

  float netPayable()
  {
    return amountBeforeTax() + TAX * amountBeforeTax();
  }

  float due()
  {
    return netPayable() - amountPaid;
  }
};
