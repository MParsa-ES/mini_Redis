You can Run the Final compiled version of the project from the mini_redis.exe file.
You can also use the configuration for VSCode inside the .vscode folder.
At last if you want to manually compile it yourself using g++ run below command in the root of the project.
g++ -std=c++17 src/main.cpp src/HashMap.cpp src/ListHashMap.cpp src/LinkedList.cpp src/ZTree.cpp src/ZSet.cpp src/ZSetHashMap.cpp src/Graph.cpp src/GraphHashMap.cpp src/LinkCutTree.cpp  -I include -o mini_redis