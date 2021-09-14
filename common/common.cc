//
// Created by chiyuen on 2021/6/3.
//

#include <libnet.h>
#include "common.h"

void common::SetLogPath(string logpath, int loglevel) {
    if (logpath.empty()) {
        FLAGS_logtostderr = true;
    } else {
        //检查日志存放目录是否存在，不存在则创建目录
        LOG_ASSERT(utils::CheckAndMakeDir(logpath.c_str()));
        //设置日志输出路径
        FLAGS_log_dir = logpath;
        //设置日志最低输出级别
        FLAGS_minloglevel = loglevel;
        FLAGS_logtostderr = false;
        FLAGS_colorlogtostderr = true;
        DLOG(INFO) << "设置日志输出目录: " << logpath << " 日志输出等级: " << loglevel << endl;
    }
}

void common::InitGlog(char *argv[]) {

    google::InitGoogleLogging(argv[0]);
}

bool common::utils::CheckAndMakeDir(const char *folder_path) {
        if (access(folder_path, F_OK) != -1) {
            return true;
        }

        char path[256];
        char *path_buf;
        char temp_path[256];
        char *temp;
        int temp_len;

        memset(path, 0, sizeof(path));
        memset(temp_path, 0, sizeof(temp_path));
        strcat(path, folder_path);
        path_buf = path;

        while ((temp = strsep(&path_buf, "/")) != nullptr) {
            temp_len = strlen(temp);
            if (0 == temp_len) {
                continue;
            }
            strcat(temp_path, "/");
            strcat(temp_path, temp);
            if (-1 == access(temp_path, F_OK)) {
                if (-1 == mkdir(temp_path, 0777)) {
                    return false;
                }
            }
        }
        return true;
}
