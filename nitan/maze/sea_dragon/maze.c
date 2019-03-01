#include <ansi.h>

inherit VRM_SERVER;

#define ENTER_ROOM_X    0
#define ENTER_ROOM_Y    0
#define ENTER_ROOM_Z    0

void create()
{
        // 迷宮房間所繼承的物件的檔案名稱。
        set_inherit_room( ROOM );

        set_lonely_create(1);
        // 迷宮進入要求最低等級。

        // 迷宮進入要求最高等級。

        // 迷宮房間存在的時間。
        set_remove_time(1800);

        //迷宮房間裡的怪物。
        set_maze_npcs(__DIR__"npc/beast");

        // 迷宮中的怪物出現可能性
        set_npcs_rate(50);

        //迷宮房間裡的BOSS。
        set_exit_npcs(__DIR__"npc/dragon");

        //迷宮的單邊長
        set_maze_long(10);

        //入口方向(出口在對面)
        set_entry_dir("north");

        //入口與區域的連接方向
        set_link_entry_dir("north");

        //入口與區域的連接檔案名
        set_link_entry_room("/d/xiakedao/haibin");

        //出口與區域的連接方向
        set_link_exit_dir("south");

        //出口與區域的連接檔案名
        set_link_exit_room("/d/xiakedao/haibin");

        //入口房間短描述
        set_entry_short("海底迷宮");

        //入口房間描述
        set_entry_desc(@LONG
這裡水色變的渾濁起來，周圍已看不大清楚了。偶有暗流襲來，卷
起陣陣的泥流。四處長著些高高的海草，密密麻麻把頭上遮的一絲
光芒也沒有了。
LONG
);

        //BOSS房間短描述
        set_exit_short("海之角");

        //BOSS房間描述
        set_exit_desc(HIB"

這裡就是海的盡頭了。。。。。。
"NOR);

        //迷宮房間的短描述
        set_maze_room_short("海底迷宮");

        //迷宮房間的描述，如果有多條描述，制造每個房
        //間的時候會從中隨機選擇一個。
        set_maze_room_desc(@LONG
這裡水色變的渾濁起來，周圍已看不大清楚了。偶有暗流襲來，卷
起陣陣的泥流。四處長著些高高的海草，密密麻麻把頭上遮的一絲
光芒也沒有了。
LONG
);

        //以下是入口坐標
        set_link_entry_room_x(ENTER_ROOM_X);
        set_link_entry_room_y(ENTER_ROOM_Y);
        set_link_entry_room_z(ENTER_ROOM_Z);
        
        // 迷宮房間是否為戶外房間？
        //set_outdoors(1);
}


