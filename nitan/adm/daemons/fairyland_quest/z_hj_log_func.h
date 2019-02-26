// 本文件被 room_gameover_hj.c 及 room_cession_hj.c 調用。
// 22:53 03-10-22


#define        MY_LOG_FILE_NAME        "static/hj2003"

string get_log_file_name()
{
    int temp;

#ifdef        IS_TEST

temp = IS_TEST;

#endif

    if( temp )
        return MY_LOG_FILE_NAME + "_" + "testlog";

    return MY_LOG_FILE_NAME + ctime_format( "_YYM" );
}

// 每個月生成一份 LOG。
// 該月的LOG如果太大時，由MUD系統自動改寫，這裏不作考慮。
// 如果在測試狀態，得分以及兑換獎品的記錄，則會寫入另一個 log 文件中。

// 獎品轉讓處的 LOG 則依舊。

void hj_log_file(string log_msg)
{
    if( !log_msg ) return;
    log_file( get_log_file_name(), log_msg );
}

