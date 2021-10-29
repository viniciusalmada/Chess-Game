#include <app.h>
#include <main_window.h>
#include <string>
#include <iostream>

int main()
{
  App::start();
  MainWindow mw{};

  mw.show();

  return 0;
}