#include "ConfigDialog.h"

#include "Application.h"

#include <QFile>
#include <QDebug>
#include <QTreeView>


#include <opencv2/core.hpp>

#include <iostream>
#include <future>
#include <experimental/coroutine>

std::future<int> async_calc(int a, int b)
{
   auto fuc = [=]()
   {
      int c = a + b;
      return c;
   };

   return std::async(fuc);
}

std::future<int> async_fib(int n)
{
   if (n <= 2)
      co_return 1;

   int a = 1;
   int b = 1;

   // iterate computing fib(n)
   for (int i = 0; i < n - 2; ++i)
   {
      int c = co_await async_calc(a, b);
      a = b;
      b = c;
   }

   co_return b;
}

std::future<void> calc_async()
{
   std::vector<double> values(10, 0);
   std::vector<double> result(10, 0);
   std::iota(values.begin(), values.end(), 1);

   for (size_t i = 0; i < values.size(); i++)
   {
      const auto value = values.at(1);
      result[i] = co_await async_calc(value, value);
   }

   std::cout << "Hello " << std::endl;
}


int main(int argc, char *argv[])
{
   Application a(argc, argv, "");

   auto fut = calc_async();
   fut.wait();

   ConfigDialog w;
   w.show();

   return a.exec();
}
