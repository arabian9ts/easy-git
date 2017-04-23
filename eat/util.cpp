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
    std::vector<std::string> dirs=split(read(".eat/HEAD"), '/');
    std::string branch=dirs.back();
    return branch;
}

/**
 * 指定したファイルのすべての行を読み込んで返す
 */
std::string read(std::string filename, std::string endline, int skip_empty_line){
    std::ifstream ifs(filename.c_str());
    std::string line="";
    std::string buff="";
    if(ifs){
        while(getline(ifs,line))
            if(!(skip_empty_line && (line=="\r" || line=="\n" || line=="\0")))
                buff+=line+endline;
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
    return split(read(".eat/logs/"+branch,"\n",1),'\n');
}

/**
 * 指定したパス先がファイルかどうかをチェックする
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
 * ファイルが存在するか確認する
 * return: 1: 存在する 0: 存在しない
 */
int isExist(std::string filename){
    struct stat st;
    int result=stat(filename.c_str(), &st);
    if(!result)
        return 1;
    return 0;
}

/**
 * 同階層のファイル、ディレクトリ名の一覧を取得
 */
std::vector<std::string> file_dir_list(std::string path){
    DIR *dir;
    struct dirent *dp;
    std::vector<std::string> result;
    
    /* subtreeが存在しないなら終了 */
    if(NULL==(dir=opendir(path.c_str()))){
        std::cout << "cannot open " << path << std::endl;
        return result;
    }
    
    /* すべてのディレクトリを読み込み */
    for(dp=readdir(dir);dp!=NULL;dp=readdir(dir)){
        /* .で始まるものとeatはスキップ */
        int start_with_dot=boost::algorithm::starts_with(dp->d_name, ".");
        if(!start_with_dot && dp->d_name!=std::string("eat"))
            result.push_back(dp->d_name);
    }
    
    return result;
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
    std::string last_commit_hash=read(".eat/refs/heads/"+branch);
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
