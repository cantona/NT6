// cruise.h

#ifndef _CRUISE_H_
#define _CRUISE_H_

#define CRUISE_USER_DATA        0               // 玩家DBASE數據

// 認証信息
#define USER_ID                 0
#define USER_SITE               1
#define USER_MAGIC_NUMBER       2

// CRUISE-FTP的錯誤號
#define RESULT_OK               "1 "            // 結果正常
#define RESULT_CRUISE           "2 "            // 返回版本
#define RESULT_FILE             "10 "           // 返回文件
#define RESULT_NO_CRUISE        "90 "           // 沒有版本
#define RESULT_FINISH           "91 "           // 同步完畢
#define RESULT_ERR              "99 "           // 未知錯誤

// CRUISE-FTP服務器端的狀態
#define STATUS_LOGIN            1               // 剛剛登錄
#define STATUS_WAIT_COMMAND     2               // 等待命令
#define STATUS_SENDING          3               // 發送文件

// CRUISE-FTP客戶端的狀態
#define STATUS_CONNECTING       101             // 連接中
#define STATUS_GET_ITEM         102             // 獲得版本
#define STATUS_GET_ITEM_ID      103             // 獲得版本數據
#define STATUS_GET_FILE         104             // 讀取文件
#define STATUS_SYN              105             // 漫遊中
#define STATUS_FINISHED         106             // 漫遊結束

// CRUISE-FTP信息結構中的條目
#define STATUS                  0               // 狀態
#define FILE_NAME               1               // 文件名字
#define FILE_POS                2               // 文件位置
#define FILE_SIZE               3               // 文件大小
#define CMD_QUEUE               4               // 待處理的命令
#define PENDING_WRITE           5               // 等待發送的信息
#define CMD_BUFFER              6               // (服務器端)緩沖區
#define RESULT_BUFFER           6               // (客戶端)緩沖區
#define SUB_SITES               7               // 站點名字

// 每次通常應答返回的長度
#define NORMAL_RESULT_LEN       80              // 80個字節

// 每次發送的文件塊大小
#define FILE_BLOCK              1460            // 每次發送1460

#endif
