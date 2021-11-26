#include <app.h>
#include <main_window.h>
#include <string>
#include <iostream>

int main()
{
  MainWindow mainWindow{};
  App app{};
  mainWindow.actionLoop([&]()
    {
      app.show();
    });

  return 0;
}