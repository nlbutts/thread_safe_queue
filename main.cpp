// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <thread>
#include <iostream>
#include <chrono>
#include "thread_queue.h"

using namespace std;
using namespace std::chrono_literals;

double runtime = 30;

void producer(Queue<int> &q)
{
  auto start = chrono::system_clock::now();
  auto stop = chrono::system_clock::now();
  chrono::duration<double> diff = stop - start;
  int i = 0;

  while (diff.count() < runtime)
  {
    this_thread::sleep_for(2s);
    cout << "Producer thread pushing: " << i << endl;
    q.push(i++);
    stop = chrono::system_clock::now();
    diff = stop - start;
  }
}

void consumer(Queue<int> &q)
{
  auto start = chrono::system_clock::now();
  auto stop = chrono::system_clock::now();
  chrono::duration<double> diff = stop - start;
  int i = 0;

  while (diff.count() < runtime)
  {
    i = q.pop();
    cout << "Consumer thread received: " << i << endl;
    stop = chrono::system_clock::now();
    diff = stop - start;
  }
}

int main (int argc, char *argv[])
{
  cout << "Hello threads" << endl;

  Queue<int> q1;

  thread p(producer, std::ref(q1));
  thread c(consumer, std::ref(q1));

  cout << "Waiting..." << endl;
  this_thread::sleep_for(40s);

  cout << "Waiting for threads to join" << endl;

  p.join();
  c.join();

  cout << "Exiting" << endl;

  return 0;
}