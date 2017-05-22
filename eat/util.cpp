//
//  util.cpp
//  eat
//
//  Created by arabian9ts on 2017/04/16.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#include "util.hpp"

using namespace util;

/**
 * 現在の時刻を返す
 * @return : 現在時刻を"%Y-%m-%d %H:%M:%S"フォーマットしたもの
 */
std::string util::getTime(){
    time_t now = std::time(nullptr);
    char clock[20];
    strftime(clock, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));
    return clock;
}

/**
 * 現在のブランチを返す
 * @return : 現在ヘッドの向いているブランチ
 */
std::string util::getBranch(){
    std::vector<std::string> dirs=split(read(".eat/HEAD","",1), '/');    
    std::string branch=dirs.back();
    return branch;
}

/**
 * 指定したファイルのすべての行を読み込んで返す
 * @param filename : 読み込む対象のファイル名
 * @param endline : 一行読み込むごとに行末に書き込む文字
 * @param skip_empty_line : 空行をスキップするかどうか
 * @return ; 読み込んで連結した文字列
 */
std::string util::read(std::string filename, std::string endline, int skip_empty_line){
    std::ifstream ifs(filename.c_str());
    std::string line="";
    std::string buff="";
    if(ifs){
        while(getline(ifs,line)){
            if(line=="\r" || line=="\n" || line=="\0"){
//                std::cout << "empty line" << std::endl;
                if(!skip_empty_line){
                    buff+="\n"+endline;
                }
            }
            else
                buff+=line+endline;
        }
    }
    ifs.close();
    return buff;
}

/**
 * ファイルのハッシュ値を計算する
 * @param filepath : sha1化したいファイルのルートからの相対パス
 * @return : sha1ハッシュコード
 */
std::string util::sha1Code(std::string filepath){
    return hash::sha1(read(filepath));
}

/**
 * 文字列を指定のデリミタで分割した結果をvectorで返す
 * @param input : 分割対象の文字列
 * @param delimiter : 区切り文字
 * @return : 分割したリスト
 */
std::vector<std::string> util::split(std::string input, char delimiter){
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
 * @param branch : ログを取得したいブランチ名
 * @return : ログのリスト
 */
std::vector<Log> util::getLogs(std::string branch){
    std::vector<Log> logs;
    std::vector<std::string> elem=split(read(".eat/logs/"+branch,"\n",1),'\n');
    
    for(int i=elem.size()-1;i>=2;i--){
        logs.push_back(*new Log(elem[i], elem[i-1], elem[i-2]));
    }
    
    return logs;
}

/**
 * 指定したパス先がファイルかどうかをチェックする
 * @param filename : チェック対象のファイル名
 * @return : 1 -> ファイル, 0 -> ファイルでない
 */
int util::isFile(std::string filename){
    struct stat st;
    stat(filename.c_str(), &st);
    if ((st.st_mode & S_IFMT) == S_IFDIR)
        return 0;
    else
        return 1;
}

/**
 * ファイル/ディレクトリが存在するか確認する
 * @param filename : チェック対象のファイル名
 * @return : 1 -> 存在する, 0 -> 存在しない
 */
int util::isExist(std::string filename){
    struct stat st;
    int result=stat(filename.c_str(), &st);
    if(0==result)
        return 1;
    return 0;
}

/**
 * 同階層のファイル、ディレクトリ名の一覧を取得
 * @param path : ファイル/ディレクトリの一覧を取得したい階層のルートからの相対パス
 * @return : 同階層のすべてのファイルとディレクトリ名のリスト
 */
std::vector<std::string> util::file_dir_list(std::string path){
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
 * @param filepath : 書き出すファイルのパス
 * @param msg : 書き込む文字列
 * @param opt : 書き込みオプション
 */
void util::write(std::string filepath, std::string msg, std::ios_base::openmode opt){
    std::ofstream writing_file;
    writing_file.open(filepath, opt);
    writing_file << msg << std::endl;
    writing_file.close();
}

/**
 * 最新コミットのハッシュ値を返す
 * @param branch : 最新コミットを取得するブランチ名
 * @return : 指定したブランチの最終コミットのハッシュ値
 */
std::string util::last_commit(std::string branch){
    std::string last_commit_hash=read(".eat/refs/heads/"+branch);
    return last_commit_hash;
}

/**
 * commitファイルidのリストを取得
 * @param branch : コミットのハッシュリストを取得したいブランチ名
 * @return : 指定したブランチでのコミットハッシュリスト
 */
std::vector<std::string> util::commitlist(std::string branch){
    std::vector<std::string> comlist;
    std::vector<std::string> logs=split(read(".eat/logs/"+branch,"\n",1),'\n');
    
    for (int idx=logs.size()-1; idx>=0; idx--)
        if(2==idx%3)
            comlist.push_back(logs[idx]);
    return comlist;
}

/**
 * ファイルを作成する
 * @param filename : 作成するファイル名
 */
void util::touch(std::string filename){
    std::ofstream strm;
    strm.open(filename);
    strm.close();
}

/**
 * ファイルを一括削除する
 * @param filelist : 削除するファイル名のリスト
 */
void util::rmfiles(std::vector<std::string> filelist){
    int count=0;
    for (auto file : filelist){
        if(isFile(file)){
            std::remove(file.c_str());
            std::cout << count << " rm " << file << std::endl;
            count++;
        }
    }
}

/**
 * ignoreを考慮した削除リストを作成
 * @param filelist : eat管理ファイルのリスト
 * @return : ignoreを考慮したコミット対象ファイルリスト
 */
void util::ignored_list(std::vector<std::string> filelist){
    
}

/**
 * ファイルの差分を抽出する
 * @param f1 : 差分抽出対象ファイル1
 * @param f2 : 差分抽出対象ファイル2
 */
void util::diff(std::string f1, std::string f2){
    
}

/**
 * commit messageを取得
 * コミットメッセージを入力するまでループ
 * @return : コミットメッセージ
 */
std::string util::fetch_commit_msg(){
    std::string msg="";
    while(msg==""){
        std::cout << "commit message : ";
        std::getline(std::cin, msg);
    }
    return msg;
}


