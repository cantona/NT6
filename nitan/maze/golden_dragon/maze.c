
#include <ansi.h>
inherit VRM_SERVER;

void create()
{
        // 迷宮房間所繼承的物件的檔案名稱。
        set_inherit_room( ROOM );

        // 迷宮進入要求最低等級。
        //set_enter_min_level(10);

        // 迷宮進入要求最高等級。
        //set_enter_max_level(20);

        set_lonely_create(1);

        // 迷宮房間時間ID和刷新時間。
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
        set_entry_dir("south");

        //入口與區域的連接方向
        set_link_entry_dir("south");

        //入口與區域的連接檔案名
        set_link_entry_room("/d/dragon/spiritgate");

        //出口與區域的連接方向
        set_link_exit_dir("north");

        //出口與區域的連接檔案名
        set_link_exit_room("/d/dragon/spiritgate");

        //入口房間短描述
        set_entry_short("忘憂園");

        //入口房間描述
        set_entry_desc(@LONG
這兒就是關外的忘憂園。周圍陰森森的，只有四個黑乎乎的洞口，
也不知通向何處。
LONG
);

        //BOSS房間短描述
        set_exit_short("沙之底");

        //BOSS房間描述
        set_exit_desc(HIY"

這裡就是沙漠盡頭。。。。。。
"NOR);

        //迷宮房間的短描述
        set_maze_room_short("忘憂園");

        //迷宮房間的描述，如果有多條描述，制造每個房
        //間的時候會從中隨機選擇一個。
        set_maze_room_desc(@LONG
這兒就是關外的忘憂園。周圍陰森森的，只有四個黑乎乎的洞口，
也不知通向何處。
LONG
);

        // 迷宮房間是否為戶外房間？
        //set_outdoors(1);
}

