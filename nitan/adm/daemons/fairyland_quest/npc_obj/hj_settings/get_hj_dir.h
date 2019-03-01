// 非常重要。被 obj_list.h 調嵌，請勿改動。
// 1:36 03-10-19


string get_hj_dir()
{
    string *temp;
    string temp_dir;
    int i, a;

    temp = explode( base_name(this_object()) , "/" );
    temp_dir = "/";

    if( strsrch( base_name(this_object()) , "/npc_obj/" ) == -1 )
        a = sizeof( temp ) - 1;
    else a = sizeof( temp ) - 2;

    for( i=0; i < a; i++ )
        temp_dir += temp[i] + "/";

    return temp_dir;
}

#define        HJ_DIR        get_hj_dir()

#include "room_amount_hj.h"    // 該文件內定義了 HJ_ROOM_AMOUNT 幻境最大房間號
