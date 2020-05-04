#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
int Find(const string magazines[], int num, string name);
void Add(string magazines[], int quantities[], float unitPrices[], int& num);
void SortByName(string magazines[], int quantities[], float prices[], int num);
void SortByQuantity(string magazines[], int quantities[], float prices[], int num);
void SortByPrice(string magazines[], int quantities[], float prices[], int num);
void Sort(string magazines[], int quantities[], float prices[], int mindex, int i);
void Print(const string magazines[], int quantities[], float prices[], int num);
void Dispense(string magazines[], int quantities[], float unitPrices[], int& num, float& totalSales);
void Cut(float prices[], int num);
void Average(int quantities[], float prices[], int num);
const int MAXSELECTIONS = 6;
const int NAME_WIDTH = 20;
const int QUANTITY_WIDTH = 5;
const int PRICE_WIDTH = 6;

int main()
{
   string magazines[MAXSELECTIONS];
   int quantities[MAXSELECTIONS];
   float unitPrices[MAXSELECTIONS];
   int numMagazines = 0;
   float priceMagazines = 0;
   float totalSales = 0;
   int quantityMagazines = 0;
   char command;
   cout << fixed << showpoint << setprecision(2) << endl;

   cin >> command;
   while (!cin.eof())
   {
      if (command == 'A')
      {
         Add(magazines, quantities, unitPrices, numMagazines);
      }
      else if (command == 'D')
      {
         Dispense(magazines, quantities, unitPrices, numMagazines, totalSales);
      }
      else if (command == 'P')
      {
         Print(magazines, quantities, unitPrices, numMagazines);
      }
      else if (command == 'S')
      {
         cin >> command;
         if (command == 'N')
         {
            SortByName(magazines, quantities, unitPrices, numMagazines);
            cout << "Magazines sorted by name." << endl;
            if (numMagazines == 0)
            {
               cout << "The magazine stand is empty!" << endl;
            }
         }
         else if (command == 'Q')
         {
            SortByQuantity(magazines, quantities, unitPrices, numMagazines);
            cout << "Magazines sorted by quantity." << endl;
            if (numMagazines == 0)
            {
               cout << "The magazine stand is empty!" << endl;
            }
         }
         else if (command == 'P')
         {
            SortByPrice(magazines, quantities, unitPrices, numMagazines);
            cout << "Magazines sorted by price." << endl;
            if (numMagazines == 0)
            {
               cout << "The magazine stand is empty!" << endl;
            }
         }
      }
      else if (command == 'C')
      {
         Cut(unitPrices, numMagazines);
      }
      else if (command == 'V')
      {
         Average(quantities, unitPrices, numMagazines);
      }
      else
      {
         cout << "Invalid command!" << endl;
         cin.ignore(200, '\n');
      }
      cin >> command;
   }

   cout << "Total sales amount for the mini magazine stand is $" << totalSales 
      << endl << endl << "Normal Termination of Program 4." << endl;
}

int Find(const string magazines[], int num, string name)
{
   for (int i = 0; i < num; i++)
   {
      if (magazines[i] == name)
      {
         return i;
      }
   }
   return -1;
}

void Add(string magazines[], int quantities[], float unitPrices[], int& num)
{
   string name;
   int newQuantity;
   float newPrice;
   cin >> name >> newQuantity >> newPrice;
   int index = Find(magazines, num, name);
   if (index >= 0)
   {
      quantities[index] += newQuantity;
      cout << newQuantity << " " << name << " added." << endl;
      if (newPrice != unitPrices[index])
      {
         unitPrices[index] = newPrice;
         cout << "Unit price updated to " << unitPrices[index] << "." << endl;
      }
   }
   else if (num >= MAXSELECTIONS)
   {
      cout << name + " not added. The magazine stand is full." << endl;
   }
   else
   {
      magazines[num] = name;
      quantities[num] = newQuantity;
      cout << name << " added." << endl;
      unitPrices[num] = newPrice;
      num++;
   }
   SortByName(magazines, quantities, unitPrices, num);
}

void Dispense(string magazines[], int quantities[], float unitPrices[], int& num, float& totalSales)
{
   string name;
   cin >> name;
   int index = Find(magazines, num, name);
   if (index == -1)
   {
      cout << "Cannot dispense " << name << ". It's out of stock." << endl;
   }
   if (index >= 0)
   {
      cout << "Dispensed one " << name << endl;
      totalSales += unitPrices[index];
      quantities[index]--;
      if (quantities[index] <= 0)
      {
         for (int i = index; i < num - 1; i++)
         {
            magazines[i] = magazines[i + 1];
            quantities[i] = quantities[i + 1];
            unitPrices[i] = unitPrices[i + 1];
         }
            num--;
      }
   }
}

void Print(const string magazines[], int quantities[], float prices[], int num)
{
   float totalValue = 0;
   if (num > 0)
   {
      cout << "Magazines in the mini magazine stand:" << endl << endl;
      for (int i = 0; i < num; i++)
      {
         cout << setw(NAME_WIDTH) << magazines[i] << setw(QUANTITY_WIDTH) << quantities[i] <<
            setw(PRICE_WIDTH) << prices[i] << endl;
      }
   }
   cout << endl;
   for (int i = 0; i < num; i++)
   {
      totalValue += quantities[i] * prices[i];
   }
   cout << "Total value of the magazines in the stand: $" << totalValue << endl << endl;
}

void SortByName(string magazines[], int quantities[], float prices[], int num)
{
      for (int i = 0; i < num - 1; i++)
      {
         int mindex = i;
         for (int j = i + 1; j < num; j++)
         {
            if (magazines[j] < magazines[mindex])
            {
               mindex = j;
            }
         }
         Sort(magazines, quantities, prices, mindex, i);
      }      
}

void SortByQuantity(string magazines[], int quantities[], float prices[], int num)
{
   for (int i = 0; i < num - 1; i++)
   {
      int mindex = i;
      for (int j = i + 1; j < num; j++)
      {
         if (quantities[j] < quantities[mindex])
         {
            mindex = j;
         }
      }
      Sort(magazines, quantities, prices, mindex, i);
   }
}

void SortByPrice(string magazines[], int quantities[], float prices[], int num)
{
   for (int i = 0; i < num - 1; i++)
   {
      int mindex = i;
      for (int j = i + 1; j < num; j++)
      {
         if (prices[j] < prices[mindex])
         {
            mindex = j;
         }
      }
      Sort(magazines, quantities, prices, mindex, i);
   }
}

void Sort(string magazines[], int quantities[], float prices[], int mindex, int i)
{
   float tempPrice = prices[i];
   prices[i] = prices[mindex];
   prices[mindex] = tempPrice;

   string tempMags = magazines[i];
   magazines[i] = magazines[mindex];
   magazines[mindex] = tempMags;

   int tempQuantity = quantities[i];
   quantities[i] = quantities[mindex];
   quantities[mindex] = tempQuantity;
}

void Cut(float prices[], int num)
{
   float percentPriceCut;
   cin >> percentPriceCut;
   for (int i = 0; i < num; i++)
   {
      prices[i] *= 1 - percentPriceCut;
   }
   cout << "Unit prices have been cut " << percentPriceCut * 100 << "%" << endl;
}

void Average(int quantities[], float prices[], int num)
{
   float totalPrice = 0;
   int numMags = 0;
   for (int i = 0; i < num; i++)
   {
      totalPrice += prices[i];
      numMags = i + 1;
   }
   if (totalPrice == 0 || numMags == 0)
   {
      cout << "Average unit price for all magazines is $0.00" << endl 
         << "The magazine stand is empty!" << endl << endl;
   }
   else
      cout << "Average unit price for all magazines is $" << totalPrice / numMags << endl;
}
