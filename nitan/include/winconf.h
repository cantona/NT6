
//分站是否不接受新玩家註冊
#undef REFUSE_NEW_PLAYER

//多少天后清除未上線的未交費用户
#define UNLOG_IDLE      90

//是否使用MYSQL數據庫及是否存儲用户數據到MYSQL庫裏，不使用數據庫則#undef DB_SAVE！
#undef DB_SAVE

//是否存儲用户數據到文本文件裏，定義了 1 就表示是，如果定義了 0 就表示否！
#define TX_SAVE         1

//是否定時為玩家保存檔案!
#define AUTO_SAVE       1

//對所有物品都允許下線保留!
#undef NO_QUIT_DROP

#define QUIT_SAVE_ALL   1

//對存入MYSQL的字符串做轉換!
#define DB_STR(x)    "'" + replace_string(x, "'", "''") + "'"

//定義最多有多少個圖標可以使用!
#define MAX_ICONS 2159

//客户端要求版本號!
#define CURRENT_CLIENT_VERSION "2060"

#define TMA "\x19" //ASCII碼25
#define TMB "\x1A" //ASCII碼26
#define TMI(x) (TMA+x+TMB)
#define INFO TMI
#define HEND sprintf("%c",18)

#define PTEXT(x) TMI("ptext "+x)
#define ALERT(x) TMI("alert "+x)
#define MTEXT(x) TMI("ptext "+x)
#define L_ITEM(x) RANK_D->new_short(x)
#define L_ICON(x) TMI("licon "+x)
#define CLEAN0  TMI("lbclear0")
#define ADD0(x) TMI("lbadd0 "+L_ITEM(x)+";")
#define REM0(x) TMI("lbrem0 "+L_ITEM(x)+";")
#define CLEAN1  TMI("lbclear1")
#define ADD1(x) TMI("lbadd1 "+L_ITEM(x)+";")
#define REM1(x) TMI("lbrem1 "+L_ITEM(x)+";")
#define CLEAN2  TMI("lbclear2")
#define ADD2(x) TMI("lbadd2 "+L_ITEM(x)+";")
#define REM2(x) TMI("lbrem2 "+L_ITEM(x)+";")
