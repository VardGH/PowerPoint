#include <csignal>
#include <iostream>

#include <cli/cli.hpp>

#include <QApplication>

#include <ui/mainwindow.h>


void signalHandler(int signal)
{
    //TODO: get all the engines and do graceful shutdown
    cli::cli::get_instance().stop();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow main_window;
    main_window.setGeometry(100, 100, 800, 500);
    main_window.show();
    return app.exec();
    
    // signal(SIGABRT, signalHandler);
    // signal(SIGINT,  signalHandler);
    // signal(SIGTERM, signalHandler);

    // try {
    //     cli::cli::get_instance().start();
    // } catch (const std::exception& ex) {
    //     std::cout << "Exception happend: " << ex.what() << std::endl;
    // } catch (...) {
    //     std::cout << "Exception happend: this is unknown exception which is not handled in application" << std::endl;
    // }
    // cli::cli::get_instance().stop();
    return 0;
}
