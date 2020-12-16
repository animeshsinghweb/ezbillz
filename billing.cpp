#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

void generateBill()
{

  Bill b;

  vector<Bill> bills = getBillsData();
  size_t b_size = bills.size();

  time_t now = time(0);
  b.createdAt = ctime(&now);
  b.createdAt.pop_back(); // removes \n from the last character

  b.billNumber = b_size + 1;
  Customer c;

  cout << "Bill Number " << b.billNumber << endl;

  cout << "\n Enter customer phone number:";
  cin >> c.phone;

  string url = "data/customer/";
  string customerURL = url + c.phone;
  string customerFileURL = customerURL + csv;

  ifstream file(customerFileURL);

  if (!file || !file.is_open())
  {
    // customer not found
    cout << "\n Enter Customer Name: ";
    cin >> c.name;

    cout << "\n Enter Customer email: ";
    cin >> c.email;

    cout << "\n Enter Customer address: ";
    cin >> c.address;

    c.amountDue = 0.00;
  }
  else
  {
    // customer found;
    c = getCustomerData(c.phone);
  }

  file.close();

  c.lastBillNumber = b_size + 1;
  b.customer = c;

  vector<productsOnCart> stock = getProductsData();
  size_t s_size = stock.size();

  vector<productsOnCart> addedToCart;
  productsOnCart st;

  cout << "All Current Inventories: " << endl;
  displayAllProducts(stock);

  cout << "\n Keep on adding product id (1 to " << s_size << "):\n";
  cout << "Enter 0 when finished adding\n\n";

  int pID, pQ;
  cin >> pID;

  while (pID < 1)
  {
    cout << "Add atleast one product to card to proceed.\n";
    cout << "Please enter valid product id \n";
    cin >> pID;
  }

  while (pID > 0)
  {
    // initial input by user is not 0 now
    //   keep on adding product till user inputs 0 as productID

    st = stock[pID - 1];

    // check if products is available in cart
    if (st.quantity == 0)
    {
      cout << "\nThere is no stock for " << st.productName;
      cout << "\nPlease try another product: \n";

      cout << "\n Keep on adding product id (1 to " << s_size << "):\n";
      cout << "Enter 0 when finished adding\n\n";
      cin >> pID;
      st = stock[pID - 1];
    }

    do
    {
      cout << "Enter quantity for " << st.productName << "(1 to " << st.quantity << "): ";
      cin >> pQ;
    } while (pQ < 1 || pQ > st.quantity);

    // if pID already exists in the cart
    // just update the quantity
    int productAlreadyExistsInCart = -1;
    size_t size_atC = addedToCart.size();
    for (size_t i = 0; i < size_atC; i++)
    {
      if (addedToCart[i].productID == pID)
      {
        productAlreadyExistsInCart = i;
        break;
      }
    }

    // add product to cart and reduce the stock
    if (productAlreadyExistsInCart > -1)
    {
      addedToCart[productAlreadyExistsInCart].quantity += pQ;
      cout << "\n\t Updated " << st.productName << "'s quantity in the Cart: ";
      cout << addedToCart[productAlreadyExistsInCart].quantity << endl;
    }
    else
    {
      st.quantity = pQ;
      addedToCart.push_back(st);
      cout << "\n\t Added " << st.productName << " to Cart: ";
      cout << st.quantity << endl;
    }

    stock[st.productID - 1].quantity -= pQ;

    cout << "\n Keep on adding product id (1 to " << s_size << "):\n";
    cout << "Enter 0 when finished adding\n\n";

    cin >> pID;
  }

  displayAllProducts(addedToCart);

  cout << "\n Bill for " << addedToCart.size() << " total quantity is being generated.\n";
  b.cart = addedToCart;

  b.taxableAmount = (float)b.amountBeforeTax();
  cout << "\n Taxable Amount is : Rs." << b.taxableAmount;
  cout << "\n Tax : " << TAX;
  b.netAmount = (float)b.netPayable();
  cout << "\n Net Amount incl Tax: Rs." << b.netAmount;
  cout << "\n \n Amount to be collected from " << b.customer.name << " for final settlement is: Rs." << b.customer.amountDue + b.netAmount << "\n\t including previous due of " << b.customer.amountDue;

  cout << "\n\n Enter Cash Mode (cash/bank): ";
  cin >> b.mode;
  cout << "\n Enter Amount Received: ";
  cin >> b.amountPaid;

  b.dueAmount = b.due() + b.customer.amountDue;
  cout << "\n Amount Due: " << b.dueAmount;

  c.amountDue += b.dueAmount;
  b.customer = c;
  saveCustomer(c, c.phone);
  cout << "\n\n \t Customer Data Updated \n";

  saveProducts(stock, -1);
  cout << "\n\n \t Inventory Stock Updated \n";

  saveBill(b, b.billNumber);
  saveProducts(b.cart, b.billNumber);

  cout << "\n\n \t Bill Saved & Generated \n \n";
  displayBill(b);
}
