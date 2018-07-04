#include <iostream>
#include <QCoreApplication>
#include <sio_client.h>
#include <sio_message.h>
#include <sio_socket.h>

#include <mutex>
#include <condition_variable>
#include <string>

using namespace sio;
using namespace std;
std::mutex _lock;

std::condition_variable_any _cond;
bool connect_finish = false;

class connection_listener
{
    sio::client &handler;

public:

    connection_listener(sio::client& h):
    handler(h)
    {
    }


    void on_connected()
    {
        _lock.lock();
        _cond.notify_all();
        connect_finish = true;
        _lock.unlock();
    }
    void on_close(client::close_reason const& reason)
    {
        std::cout<<"sio closed "<<std::endl;
        exit(0);
    }

    void on_fail()
    {
        std::cout<<"sio failed "<<std::endl;
        exit(0);
    }
};

socket::ptr current_socket;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    sio::client h;
    connection_listener l(h);

    h.set_open_listener(std::bind(&connection_listener::on_connected, &l));
    h.set_close_listener(std::bind(&connection_listener::on_close, &l,std::placeholders::_1));
    h.set_fail_listener(std::bind(&connection_listener::on_fail, &l));
    h.connect("wss://192.168.77.4:3000");

    _lock.lock();
    if(!connect_finish)
    {
        _cond.wait(_lock);
    }
    _lock.unlock();

    current_socket = h.socket();

    string nickname;
    while (nickname.length() == 0) {
        cout<<"Type your nickname:";

        getline(cin, nickname);
    }

    current_socket->emit("add user", nickname);

    current_socket->on("new message", sio::socket::event_listener_aux([&](string const& name, message::ptr const& data, bool isAck,message::list &ack_resp)
                       {
                           _lock.lock();
                           string user = data->get_map()["username"]->get_string();
                           string message = data->get_map()["message"]->get_string();
                           cout<<""<<user<<":"<<message<<endl;
                           _lock.unlock();
                       }));

    for (std::string line; std::getline(std::cin, line);) {
        if(line.length()>0)
        {
            current_socket->emit("new message", line);
        }
    }

    h.sync_close();
    h.clear_con_listeners();

    return a.exec();
}
