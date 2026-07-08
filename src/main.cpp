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
        case LPUSH:
        {
            string value;
            cin >> value;
            list.lpush(key, value);
            break;
        }
        case RPUSH:
        {
            string value;
            cin >> value;
            list.rpush(key, value);
            break;
        }
        case LPOP:
        {
            list.lpop(key);
            break;
        }
        case RPOP:
        {
            list.rpop(key);
            break;
        }
        case LRANGE:
        {
            int start, end;
            cin >> start >> end;
            list.lrange(key, start, end);
            break;
        }
        case ZADD:
        {
            int score;
            string member;
            cin >> score >> member;
            set.add(key, score, member);
            break;
        }
        case ZREM:
        {
            string member;
            cin >> member;
            set.rem(key, member);
            break;
        }
        case ZSCORE:
        {
            string member;
            cin >> member;
            set.score(key, member);
            break;
        }
        case ZRANK:
        {
            string member;
            cin >> member;
            set.rank(key, member);
            break;
        }
        case GCREATE:
        {
            graph.GCreate(key);
            break;
        }
        case GADDNODE:
        {
            string nodeName;
            cin >> nodeName;
            graph.GAddNode(key, nodeName);
            break;
        }
        case GADDEDGE:
        {
            string src, dest;
            int weight;
            cin >> src >> dest >> weight;
            graph.GAddEdge(key, src, dest, weight);
            break;
        }
        case GCONNECTED:
        {
            string src, dest;
            cin >> src >> dest;
            graph.GConnected(key, src, dest);
            break;
        }
        case GMST:
        {
            graph.GMST(key);
            break;
        }
        default:
            cout << "Unknown Command" << '\n';
            break;
        }
    } while (1);

    return 0;
}
