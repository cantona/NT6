// wuchang1.c 武場
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "武場");
        set("long", @LONG
這裏是全真教的演武場，地下的青磚本來鋪的整整齊齊，卻
不知道被誰踩出了幾十個大大小小的凹坑。看的出來，這裏成年
累月的有弟子修煉掌法步法，天長日久，地下就踩出了凹坑。
LONG
        );
        set("outdoors", "chongyang");
        set("exits", ([
                "south" : __DIR__"wuchang2",
                "north" : __DIR__"houtang2",
                "southeast" : __DIR__"xiuxishi",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -2750);
        set("coor/y", 100);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}