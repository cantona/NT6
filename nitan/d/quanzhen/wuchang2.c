// wuchang2.c 武場
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "武場");
        set("long", @LONG
這裡是全真教的演武場，地下的青磚本來舖的整整齊齊，卻
不知道被誰踩出了幾十個大大小小的凹坑。看的出來，這裡成年
累月的有弟子修煉掌法步法，天長日久，地下就踩出了凹坑。武
場中央立著幾個練功用的木人。
LONG
        );
        set("outdoors", "chongyang");
        set("exits", ([
                "north" : __DIR__"wuchang1",
                "east" : __DIR__"xiuxishi",
                "southeast" : __DIR__"shantang",
        ]));

        set("objects", ([
                "/d/shaolin/npc/mu-ren" : 4,
        ]));

        set("coor/x", -2750);
        set("coor/y", 90);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}