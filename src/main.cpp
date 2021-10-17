#include <app.h>
#include <main_window.h>
int main(int argc, char* argv[])
{

  App app(argv[0]);
  MainWindow mw{};

  mw.show();

  return 0;
}