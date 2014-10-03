#ifndef OS_H
#define OS_H

#include <sys/stat.h>
#include <dirent.h>
#include <map>
#include <string>

inline bool file_exists(const std::string& name)
{
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

inline std::multimap<std::string, std::string> do_ls(const char *dirname, bool recoursive = false)
{
    /*
     * std::map<Directory, Filename> files
     */
    typedef std::multimap<std::string, std::string> mmtype;
    mmtype files;

    DIR *dir_ptr;
    dirent *direntp;
    if((dir_ptr=opendir(dirname))==NULL)
    {
        fprintf(stderr,"myls:cannot open %s\n",dirname);
    }else{
        while((direntp=readdir(dir_ptr))!=NULL){
            if(*(direntp->d_name) != '.' ){
                if( (direntp->d_type == DT_DIR) && recoursive)
                {
                    char *newdir = new char[256];
                    memset(newdir, 0, sizeof(newdir));
                    strcpy(newdir, dirname);
                    if(newdir[strlen(dirname)-1] != '/') strcat(newdir, "/");
                    strcat(newdir, direntp->d_name);
                    do_ls(newdir);
                    delete[] newdir;
                }else
                if(direntp->d_type != DT_LNK)
                {
                    files.insert(mmtype::value_type(dirname, direntp->d_name));
                    //files[dirname] = direntp->d_name;
                }
            }
        }
    closedir(dir_ptr);
    }
    return files;
}


#endif
