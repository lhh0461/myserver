//webset address: http://www.cplusplus.com/reference/unordered_map/unordered_map/bucket_count/
#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
int main()
{
    std::map<std::string, std::string> mymap =
    {
        { "house","maison" },
        { "apple","pomme" },
        { "tree","arbre" },
        { "12","porte" },
        { "book","livre" },
        { "door","porte" },
        { "11","porte" },
        { "grapefruit","pamplemousse" }
    };
    //unsigned n = mymap.bucket_count();
    unsigned n = mymap.size();
    std::cout << "mymap has " << n << " buckets.\n";
    for (auto it = mymap.begin(); it != mymap.end(); ++it)
        std::cout << "[" << it->first << ":" << it->second << "] " << std::endl;
    std::cout << "\n";
    return 0;
    
    int double1= 3.14;
    int _;
    int catch-22_;
    int 1_or_2 = 1;
    double Double = 3.1;
}
