//
// Created by chiyuen on 2021/6/3.
//

#ifndef IO_OPTIMIZATION_COMMON_H
#define IO_OPTIMIZATION_COMMON_H

#include <string>
#include <glog/logging.h>

namespace common{
    using namespace std;

    /**
     * 初始化GLOG
     * @param argv
     */
    void InitGlog(char *argv[]);

    /**
     * 初始化日志
     * @param logpath
     * @param loglevel
     */
    void SetLogPath(string logpath, int loglevel = google::GLOG_INFO);

    namespace utils{

        /**
         * 创建文件夹
         * @param folder_path 文件夹路径 可以嵌套创建
         * @return
         */
        bool CheckAndMakeDir(const char *folder_path);



    }


}


#endif //IO_OPTIMIZATION_COMMON_H
