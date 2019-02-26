#include <ansi.h>

inherit VRM_SERVER;

#define ENTER_ROOM_X    0
#define ENTER_ROOM_Y    0
#define ENTER_ROOM_Z    0

void create()
{
        // 迷宮房間所繼承的物件的檔案名稱。
        set_inherit_room( ROOM );


        // 迷宮房間存在的時間。
        set_remove_time(1800);

        set_lonely_create(1);

        //迷宮房間裏的怪物。
        set_maze_npcs(__DIR__"npc/beast");

        // 迷宮中的怪物出現可能性
        set_npcs_rate(50);

        //迷宮房間裏的BOSS。
        set_exit_npcs(__DIR__"npc/dragon");

        //迷宮的單邊長
        set_maze_long(10);

        //入口方向(出口在對面)
        set_entry_dir("east");

        //入口與區域的連接方向
        set_link_entry_dir("east");

        //入口與區域的連接檔案名
        set_link_entry_room("/d/xueshan/shenghu");

        //出口與區域的連接方向
        set_link_exit_dir("west");

        //出口與區域的連接檔案名
        set_link_exit_room("/d/xueshan/shenghu");

        //入口房間短描述
        set_entry_short("天之盡頭");

        //入口房間描述
        set_entry_desc(@LONG
這裏風光秀麗，當真是好去處！高崖上視野開闊，遠望四周，
把天下景色看的清清楚楚。遠處大海如明鏡般平整。山崖上長有
無數異草，飄着淡淡香氣。天空中的太陽向天邊漸漸落下，水中
的陽光朝岸邊緩緩游去。
LONG
);

        //BOSS房間短描述
        set_exit_short("天之涯");

        //BOSS房間描述
        set_exit_desc(HIC"

這裏就是天之盡頭。。。。。。
"NOR);

        //迷宮房間的短描述
        set_maze_room_short("天之盡頭");

        //迷宮房間的描述，如果有多條描述，製造每個房
        //間的時候會從中隨機選擇一個。
        set_maze_room_desc(@LONG
這裏風光秀麗，當真是好去處！高崖上視野開闊，遠望四周，
把天下景色看的清清楚楚。遠處大海如明鏡般平整。山崖上長有
無數異草，飄着淡淡香氣。天空中的太陽向天邊漸漸落下，水中
的陽光朝岸邊緩緩游去。
LONG
);

        //以下是入口座標
        set_link_entry_room_x(ENTER_ROOM_X);
        set_link_entry_room_y(ENTER_ROOM_Y);
        set_link_entry_room_z(ENTER_ROOM_Z);
        
        // 迷宮房間是否為户外房間？
        set_outdoors(1);
}


