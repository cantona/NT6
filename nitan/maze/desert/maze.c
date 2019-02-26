#include <ansi.h>

inherit VRM_SERVER;

void create()
{
        //迷宮房間所繼承的物件的檔案名稱。
        set_inherit_room( ROOM );

        //唯一房間
        set_unique_room( ({
                "/maze/desert/unique_room/guai_boss_room",
                "/maze/desert/unique_room/guai_boss_room",
                "/maze/desert/unique_room/guai_boss_room",
                "/maze/desert/unique_room/guai_boss_room",
        }) );
        set_center_room("/maze/desert/unique_room/king_boss_room");

        //迷宮房間裏的怪物。
        set_maze_npcs( ([
                "/maze/desert/npc/guai": 1 + random(3),
        ]) );

        set_npcs_rate(80);

        set_lonely_create(1);

        set_maze_boxs(5);


        //迷宮的單邊長
        set_maze_long(8);

        //入口方向(出口在對面)
        set_entry_dir("north");

        //入口與區域的連接方向
        set_link_entry_dir("north");

        //入口與區域的連接檔案名
        set_link_entry_room("/d/changan/ca10");

        //出口與區域的連接方向
        set_link_exit_dir("south");

        //出口與區域的連接檔案名
        set_link_exit_room(__DIR__"out");  


        //普通房間描述
        set_maze_room_short(RED "無盡大漠" NOR);

        set_maze_room_desc(@LONG
一望無際的大漠，烈日、風沙、苦寒、酷熱，無時不在折磨着每
一個人，在這裏，如果你沒有飲水，很有可能就會被曬死，沙子滾燙，
足以把腳燙爛，一到晚上，卻又冰冷得透骨。
LONG);

        //入口房間短描述
        set_entry_short(HIR "無盡大漠入口" NOR);

        //入口房間描述
        set_entry_desc(@LONG
一望無際的大漠，烈日、風沙、苦寒、酷熱，無時不在折磨着每
一個人，在這裏，如果你沒有飲水，很有可能就會被曬死，沙子滾燙，
足以把腳燙爛，一到晚上，卻又冰冷得透骨。
LONG);

        //出口房間短描述
        set_exit_short(WHT "無盡大漠出口" NOR);

        //出口房間描述
        set_exit_desc(@LONG
一望無際的大漠，烈日、風沙、苦寒、酷熱，無時不在折磨着每
一個人，在這裏，如果你沒有飲水，很有可能就會被曬死，沙子滾燙，
足以把腳燙爛，一到晚上，卻又冰冷得透骨。
LONG);
        set_outdoors(1);
}
