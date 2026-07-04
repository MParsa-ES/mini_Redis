#include <iostream>
#include <string>
#include <algorithm>
#include <ctype.h>

#include "HashMap.h"

using namespace std;

enum COMMAND
{
    SET,
    GET,
    DEL,
    EXISTS,
    EXPIRE,
    TTL,
    UNKNOWN
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
    return UNKNOWN;
}

int main()
{
    HashMap map;
    do
    {
        string cmd;
        string key;
        cin >> cmd >> key;
        std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
        COMMAND command = Transform(cmd);
        switch (command)
        {
        case SET:
        {
            string value;
            cin >> value;
            map.set(key, value);
            break;
        }
        case GET:
        {
            map.get(key);
            break;
        }
        case DEL:
        {
            map.del(key);
            break;
        }
        case EXISTS:
        {
            map.exists(key);
            break;
        }
        case EXPIRE:
        {
            int seconds;
            cin >> seconds;
            map.expire(key, seconds);
            break;
        }
        case TTL:
        {
            map.TTL(key);
            break;
        }

        default:
            cout << "Unknown Command" << '\n';
            break;
        }
    } while (1);

    return 0;
}
