//
//  util.cpp
//  eat
//
//  Created by arabian9ts on 2017/04/16.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#include "util.hpp"

/**
 * 現在の時刻を返す
 */
std::string getTime(){
    time_t now = std::time(nullptr);
    char clock[20];
    strftime(clock, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));
    return clock;
}

/**
 * 現在のブランチを返す
 */
std::string getBranch(){
    std::vector<std::string> dirs=split(read(".eat/HEAD","/"), '/');
    std::string branch=dirs.back();
    return branch;
}

/**
 * 指定したファイルのすべての行を読み込んで返す
 */
std::string read(std::string filename, std::string endline){
    std::ifstream ifs(filename.c_str());
    std::string line="";
    std::string buff="";
    if(ifs){
        while(getline(ifs,line))
        {
            buff+=line+endline;
        }
    }
    ifs.close();
    return buff;
}

/**
 * ファイルのハッシュ値を計算する
 */
std::string sha1Code(std::string filepath){
    return sha1(read(filepath));
}

/**
 * 文字列を指定のデリミタで分割した結果をvectorで返す
 */
std::vector<std::string> split(std::string input, char delimiter){
    std::istringstream stream(input);
    std::string field;
    std::vector<std::string> result;
    while (std::getline(stream, field, delimiter)) {
        result.push_back(field);
    }
    return result;
}

/**
 * logをvectorで返す
 * vectorの中身はhash, date, msgのサイクル
 */
std::vector<std::string> getLogs(std::string branch){
    return split(read(".eat/logs/"+branch,"\n"),'\n');
}

/**
 * 指定したパス先がファイルかどうかをてェックする
 * 1 : ファイル, 0 : ファイルでない
 */
int isFile(std::string filename){
    struct stat st;
    stat(filename.c_str(), &st);
    if ((st.st_mode & S_IFMT) == S_IFDIR)
        return 0;
    else
        return 1;
}

/**
 * 指定したファイルに文字列を書き込む
 * opt : 書き込みオプション
 */
int write(std::string filepath, std::string msg, std::ios_base::openmode opt){
    std::ofstream writing_file;
    writing_file.open(filepath, opt);
    writing_file << msg << std::endl;
    writing_file.close();
    return 0;
}

/**
 * 最新コミットのハッシュ値を返す
 */
std::string last_commit(std::string branch){
    std::vector<std::string> commit_log=getLogs(branch);
    std::string last_commit_hash="";
    
    if(commit_log.size()!=0){
        last_commit_hash=commit_log[commit_log.size()-1];
        std::cout << last_commit_hash << std::endl;
    }
    
    return last_commit_hash;
}

/**
* ファイルを作成する
*/
void touch(std::string filename){
    std::ofstream strm;
    strm.open(filename);
    strm.close();
}
