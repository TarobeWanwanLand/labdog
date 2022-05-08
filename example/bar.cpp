#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>
#include <chrono>
#include <iostream>
#include <spdlog/spdlog.h>

using namespace boost::asio;

int main()
{
    io_service ioservice;

    steady_timer timer1{ioservice, std::chrono::seconds{3}};
    timer1.async_wait([](const boost::system::error_code &ec)
                      { spdlog::info("3 sec"); });

    ioservice.run();
}