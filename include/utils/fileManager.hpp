#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>
#include <fstream>
#include <stdexcept>
#include <ctime>
#include <iomanip>
#include <sstream>

#if defined(_WIN32)
  #include <direct.h>
  #include <sys/stat.h>
#else
  #include <sys/stat.h>
  #include <sys/types.h>
  #include <unistd.h>
#endif

namespace files {

    inline std::string now_iso() {
        std::time_t t = std::time(nullptr);
        std::tm tm{};
        #if defined(_WIN32)
            localtime_s(&tm, &t);
        #else
            tm = *std::localtime(&t);
        #endif
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    inline std::string parent_dir(const std::string& path) {
        if (path.empty()) return {};
        size_t pos_slash = path.find_last_of('/');
        size_t pos_back  = path.find_last_of('\\');
        size_t pos = std::string::npos;
        if (pos_slash != std::string::npos && pos_back != std::string::npos)
            pos = (pos_slash > pos_back) ? pos_slash : pos_back;
        else if (pos_slash != std::string::npos)
            pos = pos_slash;
        else if (pos_back != std::string::npos)
            pos = pos_back;

        if (pos == std::string::npos) return {};
        return path.substr(0, pos);
    }

    inline bool mkdir_once(const std::string& dir) {
        if (dir.empty()) return true;
        #if defined(_WIN32)
            struct _stat st{};
            if (_stat(dir.c_str(), &st) == 0 && (st.st_mode & _S_IFDIR)) return true;
            return _mkdir(dir.c_str()) == 0;
        #else
            struct stat st{};
            if (stat(dir.c_str(), &st) == 0 && S_ISDIR(st.st_mode)) return true;
            return ::mkdir(dir.c_str(), 0755) == 0;
        #endif
    }

    inline void ensure_dir(const std::string& dir) {
        if (dir.empty()) return;

        std::string norm = dir;
        for (char& c : norm){ 
            if (c == '\\') c = '/';
        }

        std::string current;
        for (size_t i=0; i<norm.size(); ++i) {
            char ch = norm[i];
            if (ch == '/') {
                if (!current.empty()) {
                    mkdir_once(current);
                }
            }
            current.push_back(ch);
        }
        
        if (!current.empty() && current.back() != '/') {
            mkdir_once(current);
        }
    }

    inline void write_text(const std::string& path, const std::string& content) {
        std::string dir = parent_dir(path);
        ensure_dir(dir);
        std::ofstream out(path, std::ios::binary);
        if (!out) throw std::runtime_error("Failed to open: " + path);
        out << content;
        if (!out) throw std::runtime_error("Failed to write: " + path);
    }
}
#endif