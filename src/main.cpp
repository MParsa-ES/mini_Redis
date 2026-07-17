#include <iostream>
#include <string>
#include <algorithm>
#include <ctype.h>

#include "HashMap.h"
#include "ListHashMap.h"
#include "ZSetHashMap.h"
#include "GraphHashMap.h"

using namespace std;

enum COMMAND
{
    SET,
    GET,
    DEL,
    EXISTS,
    EXPIRE,
    TTL,
    LPUSH,
    RPUSH,
    LPOP,
    RPOP,
    LRANGE,
    ZADD,
    ZREM,
    ZSCORE,
    ZRANK,
    GCREATE,
    GADDNODE,
    GADDEDGE,
    GCONNECTED,
    GMST,
    EXIT,
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
    // ==================================
    if (cmd == "LPUSH")
        return LPUSH;
    if (cmd == "RPUSH")
        return RPUSH;
    if (cmd == "LPOP")
        return LPOP;
    if (cmd == "RPOP")
        return RPOP;
    if (cmd == "LRANGE")
        return LRANGE;
    // ===================================
    if (cmd == "ZADD")
        return ZADD;
    if (cmd == "ZREM")
        return ZREM;
    if (cmd == "ZSCORE")
        return ZSCORE;
    if (cmd == "ZRANK")
        return ZRANK;
    // ===================================
    if (cmd == "GCREATE")
        return GCREATE;
    if (cmd == "GADDNODE")
        return GADDNODE;
    if (cmd == "GADDEDGE")
        return GADDEDGE;
    if (cmd == "GCONNECTED")
        return GCONNECTED;
    if (cmd == "GMST")
        return GMST;
    // ====================================
    if (cmd == "EXIT")
        return EXIT;

    return UNKNOWN;
}

int main()
{
    HashMap map;
    ListHashMap list;
    ZSetHashMap set;
    GraphHashMap graph;
    cout << "Mini Redis is Running..." << '\n';
    do
    {
        string cmd;
        string key;
        cin >> cmd;
        std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
        COMMAND command = Transform(cmd);
        switch (command)
        {
        case SET:
        {
            cin >> key;
            string value;
            cin >> value;
            map.set(key, value);
            break;
        }
        case GET:
        {
            cin >> key;
            map.get(key);
            break;
        }
        case DEL:
        {
            cin >> key;
            map.del(key);
            break;
        }
        case EXISTS:
        {
            cin >> key;
            map.exists(key);
            break;
        }
        case EXPIRE:
        {
            cin >> key;
            int seconds;
            cin >> seconds;
            map.expire(key, seconds);
            break;
        }
        case TTL:
        {
            cin >> key;
            map.TTL(key);
            break;
        }
        case LPUSH:
        {
            cin >> key;
            string value;
            cin >> value;
            list.lpush(key, value);
            break;
        }
        case RPUSH:
        {
            cin >> key;
            string value;
            cin >> value;
            list.rpush(key, value);
            break;
        }
        case LPOP:
        {
            cin >> key;
            list.lpop(key);
            break;
        }
        case RPOP:
        {
            cin >> key;
            list.rpop(key);
            break;
        }
        case LRANGE:
        {
            cin >> key;
            int start, end;
            cin >> start >> end;
            list.lrange(key, start, end);
            break;
        }
        case ZADD:
        {
            cin >> key;
            int score;
            string member;
            cin >> score >> member;
            set.add(key, score, member);
            break;
        }
        case ZREM:
        {
            cin >> key;
            string member;
            cin >> member;
            set.rem(key, member);
            break;
        }
        case ZSCORE:
        {
            cin >> key;
            string member;
            cin >> member;
            set.score(key, member);
            break;
        }
        case ZRANK:
        {
            cin >> key;
            string member;
            cin >> member;
            set.rank(key, member);
            break;
        }
        case GCREATE:
        {
            cin >> key;
            graph.GCreate(key);
            break;
        }
        case GADDNODE:
        {
            cin >> key;
            string nodeName;
            cin >> nodeName;
            graph.GAddNode(key, nodeName);
            break;
        }
        case GADDEDGE:
        {
            cin >> key;
            string src, dest;
            int weight;
            cin >> src >> dest >> weight;
            graph.GAddEdge(key, src, dest, weight);
            break;
        }
        case GCONNECTED:
        {
            cin >> key;
            string src, dest;
            cin >> src >> dest;
            graph.GConnected(key, src, dest);
            break;
        }
        case GMST:
        {
            cin >> key;
            graph.GMST(key);
            break;
        }
        case EXIT:
        {
            return 0;
        }
        default:
            cout << "Unknown Command" << '\n';
            cin.clear();
            break;
        }
    } while (1);

    return 0;
}
