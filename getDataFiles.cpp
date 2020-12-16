#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// #include "structures.cpp"

using namespace std;

Customer getCustomerData(string phone)
{
  Customer c;

  string url = "data/customer/";
  string customerURL = url + phone;
  string customerFileURL = customerURL + csv;

  ifstream file(customerFileURL);

  getline(file, c.name);
  string amountDue, lastBillNumber;

  while (!file.eof())
  {
    getline(file, c.name, ',');
    getline(file, c.phone, ',');
    getline(file, c.email, ',');
    getline(file, c.address, ',');
    getline(file, amountDue, ',');
    getline(file, lastBillNumber, '\n');

    c.amountDue = stof(amountDue);
    c.lastBillNumber = stoi(lastBillNumber);
  }
  file.close();

  return c;
}

vector<productsOnCart> getProductsData(string location = "data/products/product.csv")
{
  //returns vector of products read from
  vector<productsOnCart> products;
  productsOnCart p;

  ifstream file(location);
  if (!file.is_open() || !file)
  {
    // file not found
    return products;
  }

  string productID, quantity, price;

  getline(file, p.productName);

  while (!file.eof())
  {
    // ProductId, Name, Stock, Price
    getline(file, productID, ',');
    getline(file, p.productName, ',');
    getline(file, quantity, ',');
    getline(file, price);

    p.productID = stoi(productID);
    p.quantity = stoi(quantity);
    p.price = stof(price);

    products.push_back(p);
  }
  file.close();
  return products;
}

vector<Bill> getBillsData()
{
  // returns vector of Bills read from bills.csv

  vector<Bill> bills;

  string line, billNumber, cPhone, cartID, taxableAmount, netAmount, amountPaid, dueAmount;

  ifstream billFile("data/billing/bills.csv");

  getline(billFile, line, '\n');

  Customer c1;
  Bill b1;
  vector<productsOnCart> p1;

  while (billFile.eof() == false)
  {

    getline(billFile, billNumber, ',');
    getline(billFile, cPhone, ',');
    getline(billFile, cartID, ',');
    getline(billFile, taxableAmount, ',');
    getline(billFile, netAmount, ',');
    getline(billFile, amountPaid, ',');
    getline(billFile, b1.mode, ',');
    getline(billFile, dueAmount, ',');
    getline(billFile, b1.createdAt);

    b1.billNumber = stoi(billNumber);
    b1.taxableAmount = stof(taxableAmount);
    b1.netAmount = stof(netAmount);
    b1.amountPaid = stof(amountPaid);
    b1.dueAmount = stof(dueAmount);

    c1 = getCustomerData(cPhone);

    // string cartStore = "data/billing/cart/";
    // string cartStoreURL = cartStore + cartID + csv;
    // p1 = getProductsData(cartStoreURL);

    b1.customer = c1;
    // b1.cart = p1;

    bills.push_back(b1);
  }
  billFile.close();

  return bills;
}
