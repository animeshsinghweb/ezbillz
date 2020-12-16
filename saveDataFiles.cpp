#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// #include "structures.cpp"
// #include "getDataFiles.cpp"

using namespace std;

void saveCustomer(Customer c, string phone)
{
  // Name,Phone,Email,Address,Due,Last BillID

  string url = "data/customer/";
  string customerURL = url + phone;
  string customerFileURL = customerURL + csv;

  ofstream fileOut(customerFileURL);
  fileOut << "Name,Phone,Email,Address,Due,Last BillID\n";
  fileOut << c.name << ",";
  fileOut << c.phone << ",";
  fileOut << c.email << ",";
  fileOut << c.address << ",";
  fileOut << c.amountDue << ",";

  fileOut << c.lastBillNumber;
  fileOut.close();
}

void saveBill(Bill b, int cartID)
{
  // Bill ID,Customer Phone,Cart Id,Taxable Amount,
  //  Net Amount,Paid,Mode,Due,createdAt

  vector<Bill> bills = getBillsData();
  size_t size = bills.size();

  ofstream fileOut("data/billing/bills.csv", ios::app);
  fileOut << "\n";
  fileOut << b.billNumber << ",";
  fileOut << b.customer.phone << ",";
  fileOut << cartID << ",";
  fileOut << b.taxableAmount << ",";
  fileOut << b.netAmount << ",";
  fileOut << b.amountPaid << ",";
  fileOut << b.mode << ",";
  fileOut << b.dueAmount << ",";
  fileOut << b.createdAt;

  fileOut.close();
}

void saveProducts(const vector<productsOnCart> products, int cartID)
{
  // cartID to be 0 or less for
  //     saving Inventories in data/products/product.csv
  //   anyother natural number value for
  //     saving cart in /data/billing/cart

  string fileURL;
  if (cartID > 0)
  {
    string url = "data/billing/cart/";
    string cID = to_string(cartID);
    string cartURL = url + cID;
    fileURL = cartURL + csv;
  }
  else
  {
    fileURL = "data/products/product.csv";
  }

  ofstream fileOut(fileURL);
  size_t size = products.size();
  productsOnCart p;

  if (cartID > 0)
  {
    fileOut << "ProductID,ProductName,Quantity,Price\n";
  }
  else
  {
    fileOut << "ProductId,Name,Stock,Price\n";
  }

  for (int i = 0; i < size; i++)
  {
    p = products[i];

    fileOut << p.productID << ",";
    fileOut << p.productName << ",";
    fileOut << p.quantity << ",";
    fileOut << p.price << (i == size - 1 ? "" : "\n");
  }
  fileOut.close();
}
