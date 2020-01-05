#include "ConfigDialog.h"

#include "Application.h"

#include <QFile>
#include <QDebug>
#include <QTreeView>


#include <opencv2/core.hpp>

#include <iostream>
#include <future>
#include <experimental/coroutine>
//#include <experimental/future>

namespace coro = std::experimental;

struct coroutine_type
{
   struct promise_type
   {
      int _value{ 0 };
      coroutine_type get_return_object() { return { *this }; }
      auto initial_suspend() { return coro::suspend_never{}; }
      auto final_suspend() { return coro::suspend_always{}; }
      void unhandled_exception() { std::terminate(); }
      void return_value(int val) 
      { 
         _value = val; 
      }
   };

   void resume() { _coro.resume(); }
   int get() { return _coro.promise()._value; }

   using HDL = coro::coroutine_handle<promise_type>;

   coroutine_type() = default;
   coroutine_type(const coroutine_type&) = delete;
   ~coroutine_type() { _coro.destroy(); }

private:
   coroutine_type(promise_type& p) : _coro(HDL::from_promise(p)) {}

   coro::coroutine_handle<promise_type> _coro;
};

struct generator_type
{
   struct promise_type
   {
      int _value;
      generator_type get_return_object() { return { *this }; }
      auto initial_suspend() { return coro::suspend_never{}; }
      auto final_suspend() { return coro::suspend_never{}; }
      void unhandled_exception() { std::terminate(); }

      void return_void() {}
      auto yield_value(int val) 
      { 
         _value = val; 
         return coro::suspend_always();
      }
   };

   void resume() { _coro.resume(); }
   int get() { return _coro.promise()._value; }

   using HDL = coro::coroutine_handle<promise_type>;

   generator_type() = default;
   generator_type(const coroutine_type&) = delete;
   ~generator_type() { _coro.destroy(); }

private:
   generator_type(promise_type& p) : _coro(HDL::from_promise(p)) {}

   coro::coroutine_handle<promise_type> _coro;
};


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

coroutine_type coroutine()
{
   qDebug() << "befor suspension";
   co_await coro::suspend_always();
   qDebug() << "resumed";
   co_return 42;
}

generator_type generator()
{
   for (size_t i = 0; i < 5; i++)
   {
      co_yield i;
   }
}

int main(int argc, char *argv[])
{
   auto value = coroutine();
   value.resume();
   qDebug() << value.get();

   auto gen = generator();
   qDebug() << gen.get();
   gen.resume();
   qDebug() << gen.get();
   gen.resume();
   qDebug() << gen.get();
   gen.resume();
   qDebug() << gen.get();


   Application a(argc, argv, "");

   auto fut = calc_async();
   fut.wait();

   ConfigDialog w;
   w.show();

   return a.exec();
}
