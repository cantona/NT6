// 地獄迷宮
// by Lonely
// inherit VRM_SERVER;
#include <ansi.h>
inherit "/adm/daemons/vrm_server";

void create()
{
        //迷宮房間所繼承的物件的檔案名稱。
        set_inherit_room( ROOM );

        //迷宮房間裏的怪物。
        //set_maze_npcs(__DIR__"npc/baihu");

        //迷宮的單邊長
        set_maze_long(10);

        //入口方向(出口在對面)
        set_entry_dir("south");

        //入口與區域的連接方向
        set_link_entry_dir("south");

        //入口與區域的連接檔案名
        set_link_entry_room(__DIR__"jimiesi");

        //出口與區域的連接方向
        set_link_exit_dir("north");

        //出口與區域的連接檔案名
        set_link_exit_room(__DIR__"baihuxue");

        //入口房間短描述
        set_entry_short(HIB "黑森林" NOR);

        //入口房間描述
        set_entry_desc(HIB @LONG
這裏是據説就是黑森林，裏面全是陰霧，陰氣逼人，不小心就可能迷
失方向了。
LONG NOR);

        //出口房間短描述
        set_exit_short(HIB "黑森林" NOR);

        //出口房間描述
        set_exit_desc(HIB @LONG
你眼前一亮，深深的吸了口氣，心想總算是出來了。不過景色忽的一
邊，眼前出現一個黑乎乎的山洞。
LONG NOR
);

        //迷宮房間的短描述
        set_maze_room_short(HIB "黑森林" NOR);

        //迷宮房間的描述，如果有多條描述，製造每個房
        //間的時候會從中隨機選擇一個。
        set_maze_room_desc(HIB @LONG
四周越來越暗了，你膽顫心驚的象前摸索着，到處是一些
迷路人的屍體和骷髏。不時傳來一陣陣鬼哭浪嚎,好像有什麼
東西在暗中窺視着，你不由的加快了腳步。
LONG NOR
);

        // 迷宮房間是否為户外房間？
        set_outdoors(0);
}

