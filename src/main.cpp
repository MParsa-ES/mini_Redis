#include <iostream>
#include <string>

#include <HashMap.h>

using namespace std;

enum COMMAND
{
    SET,
    GET,
    DEL,
    EXISTS,
    EXPIRE,
    TTL
};

COMMAND Transform(string cmd)
{
    if (cmd == "SET")
        return SET;
    if (cmd == "GET")
        return GET;
    if (cmd == "DEL")
        return DEL;
    if (cmd == "EXISTS")
        return EXISTS;
    if (cmd == "EXPIRE")
        return EXPIRE;
    if (cmd == "TTL")
        return TTL;
}

int main()
{
    do
    {
        string cmd;
        string key;
        cin >> cmd >> key;
        COMMAND command = Transform(cmd);
        switch (command)
        {
        case SET:
        {
            string value;
            cin >> value;
            break;
        }
        case GET:
        {
            break;
        }
        case DEL:
        {
            break;
        }
        case EXISTS:
        {
            break;
        }
        case EXPIRE:
        {
            break;
        }
        case TTL:
        {
            break;
        }

        default:
            cout << "Unknown Command" << '\n';
            break;
        }
    } while (1);

    return 0;
}
