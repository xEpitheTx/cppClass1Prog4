#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
int Find(const string magazines[], int num, string name);
void Add(string magazines[], int quantities[], float unitPrices[], int& num, float& price, int& quantity);
void Sort(string magazines[], int quantities[], float prices[], int num, char command);
void Print(const string magazines[], int quantities[], float prices[], int num);
void Dispense(string magazines[], int quantities[], float unitPrices[], int& num);
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
   int quantityMagazines = 0;
   char command;
   cout << fixed << showpoint << setprecision(2) << endl;

   cin >> command;
   while (!cin.eof())
   {
      if (command == 'A')
      {
         Add(magazines, quantities, unitPrices, numMagazines, priceMagazines, quantityMagazines);
      }
      else if (command == 'D')
      {
         Dispense(magazines, quantities, unitPrices, numMagazines);
      }
      else if (command == 'P')
      {
         Print(magazines, quantities, unitPrices, numMagazines);
      }
      else if (command == 'S')
      {
         cin >> command;
         Sort(magazines, quantities, unitPrices, numMagazines, command);
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
   //need to keep track of how much was dispensed and price and print out total sales at eof
   //cout << "Total sales amount for the mini magazine stand is $22.63";
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

void Add(string magazines[], int quantities[], float unitPrices[], int& num, float& price, int& quantity)
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
         cout << "Unit price updated to " << unitPrices[index] << endl;
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
      cout << newQuantity << " " << name << " added." << endl;
      unitPrices[num] = newPrice;
      num++;
   }
   Sort(magazines, quantities, unitPrices, num, 'n');
}

void Dispense(string magazines[], int quantities[], float unitPrices[], int& num)
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
      quantities[index]--;
      if (quantities[index] <= 0)
      {
         magazines[index] = magazines[num - 1];
         quantities[index] = quantities[num - 1];
         unitPrices[index] = unitPrices[num - 1];
         num--;
      }
   }
}

void Print(const string magazines[], int quantities[], float prices[], int num)
{
   float totalValue = 0;
   if (num == 0)
   {
      //cout << "The magazine stand is empty!" << endl;
   }
   else
   {
      cout << "Magazines in the mini magazine stand: " << endl;
      for (int i = 0; i < num; i++)
      {
         cout << setw(NAME_WIDTH) << magazines[i] << setw(QUANTITY_WIDTH) << quantities[i] << setw(PRICE_WIDTH) << prices[i] << endl;
      }
   }
   for (int i = 0; i < num; i++)
   {
      totalValue += quantities[i] * prices[i];
   }
   cout << "Total value of the magazines in the stand: " << totalValue << endl << endl;
}

void Sort(string magazines[], int quantities[], float prices[], int num, char command)
{
   if (command == 'N' || command == 'n')
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
         string tempMags = magazines[i];
         magazines[i] = magazines[mindex];
         magazines[mindex] = tempMags;

         int tempQuantity = quantities[i];
         quantities[i] = quantities[mindex];
         quantities[mindex] = tempQuantity;

         float tempPrice = prices[i];
         prices[i] = prices[mindex];
         prices[mindex] = tempPrice;
      }
      if (command == 'N')
      {
         cout << "Magazines sorted by name." << endl;
      }
   }
   if (command == 'Q')
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
         int tempQuantity = quantities[i];
         quantities[i] = quantities[mindex];
         quantities[mindex] = tempQuantity;

         string tempMags = magazines[i];
         magazines[i] = magazines[mindex];
         magazines[mindex] = tempMags;


         float tempPrice = prices[i];
         prices[i] = prices[mindex];
         prices[mindex] = tempPrice;
      }
      cout << "Magazines sorted by quantity." << endl;
   }
   if (command == 'P')
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
      cout << "Magazines sorted by price." << endl;
   }
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
      cout << "Average unit price for all magazines is $0.00" << endl;
      cout << "The magazine stand is empty!" << endl << endl;
   }
   else
      cout << "Average unit price for all magazines is $" << totalPrice / numMags << endl;
}
