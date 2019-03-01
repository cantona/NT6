// message.h

#ifndef __MESSAGE_H__
#define __MESSAGE_H__


//
// Client 訊息類別定義
//
#define SYSMSG          "SYSMSG"                // 系統訊息
#define ENVMSG          "ENVMSG"                // 環境訊息
#define CMDMSG          "CMDMSG"                // 指令訊息
#define CHNMSG          "CHNMSG"                // 頻道訊息
#define EMTMSG          "EMTMSG"                // 表情訊息
#define SAYMSG          "SAYMSG"                // 說話訊息
#define TELLMSG         "TELLMSG"               // 交談訊息
#define ERRMSG          "ERRMSG"                // 錯誤訊息
#define ETCMSG          "ETCMSG"                // 其他訊息
#define GAMEMSG         "GAMEMSG"               // 遊戲訊息

int  is_loging_now();
int  start_log();
void end_log();
void log_message(string msg);
void log_command(string cmd);
void receive_message(string msgclass, string msg);
void clear_written();
int  is_waiting_command();
void write_prompt();
void receive_snoop(string msg);

#endif
