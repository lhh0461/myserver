#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#include <string>
#include <vector>

using std::vector;
using std::string;

int readFileList(const char *basePath, vector<string> & filelist)
{
    std::vector<std::string> result;
    DIR *dir;
    struct dirent *ptr;
    char base[1000];

    if ((dir=opendir(basePath)) == NULL)
    {
        perror("Open dir error...");
        exit(1);
    }

    while ((ptr=readdir(dir)) != NULL)
    {
        if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir
            continue;
        else if(ptr->d_type == 8)    ///file
        {
            printf("baePath=%s, name=%s\n",basePath,ptr->d_name);
            result.push_back(std::string(ptr->d_name));
        }
        else if(ptr->d_type == 10)    ///link file
        {
            //printf("d_name:%s/%s\n",basePath,ptr->d_name);
            result.push_back(std::string(ptr->d_name));
        }
        else if(ptr->d_type == 4)    ///dir
        {
            //memset(base,'\0',sizeof(base));
            strcpy(base,basePath);
            strcat(base,"/");
            strcat(base,ptr->d_name);
            result.push_back(std::string(ptr->d_name));
            readFileList(base);
        }
    }
    closedir(dir);
    return result;
}

int main()
{
    std::vector<std::string> a = readFileList("./");
}
