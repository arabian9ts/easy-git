//
//  util.hpp
//  eat
//
//  Created by arabian9ts on 2017/04/16.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef util_hpp
#define util_hpp

#include "eat.hpp"
#include "sha1.hpp"
#include <dirent.h>

/**
 * 現在のブランチを返す
 */
std::string getBranch();

/**
 * 現在の時刻を返す
 */
std::string getTime();

/**
 * 指定したファイルのすべての行を読み込んで返す
 * endline : 行末に付加する文字列
 */
std::string read(std::string filename, std::string endline="", int skip_empty_line=0);

/**
 * ファイルのハッシュ値を計算する
 */
std::string sha1Code(std::string filepath);

/**
 * 文字列を指定のデリミタで分割した結果をvectorで返す
 */
std::vector<std::string> split(std::string input, char delimiter);

/**
 * logをvectorで返す
 * vectorの中身はhash, date, msgのサイクル
 */
std::vector<std::string> getLogs(std::string branch);

/**
 * 指定したパス先がファイルかどうかをチェックする
 * 1 : ファイル, 0 : ファイルでない
 */
int isFile(std::string filename);

/**
 * ファイルが存在するか確認する
 * return: 1: 存在する 0: 存在しない
 */
int isExist(std::string filename);

/**
 * 同階層のファイル、ディレクトリ名の一覧を取得
 */
std::vector<std::string> file_dir_list(std::string path);

/**
 * 指定したファイルに文字列を書き込む
 * opt : 書き込みオプション
 */
int write(std::string filepath, std::string msg, std::ios_base::openmode opt);

/**
 * 最新コミットのハッシュ値を返す
 * branch: コミットログを取得したいブランチ
 */
std::string last_commit(std::string branch);

/**
 * ファイルを作成する
 */
void touch(std::string filename);

/**
 * ファイルを一括削除する
 */
void rmfiles(std::vector<std::string> filelist);

/**
 * ignoreを考慮した削除リストを作成
 */
void ignored_list(std::vector<std::string> filelist);

#endif /* util_hpp */
