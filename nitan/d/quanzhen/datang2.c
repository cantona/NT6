// datang2.c 大堂二進
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "大堂二進");
        set("long", @LONG
這裏是大堂的第二重，是全真教弟子做功課的所在。現在還不到
功課時間，大堂裏空蕩蕩的，只有全真教掌管上下雜事的掌理道長帶
領着幾個小道童在整理桌椅，預備餐飯。
LONG
        );
        set("exits", ([
                "east" : __DIR__"datang3",
                "west" : __DIR__"datang1",
                "north" : __DIR__"cetang",
                "south" : __DIR__"piandian",
        ]));
        set("objects",([
                __DIR__"npc/zhangli" : 1,
                __DIR__"npc/daotong1" : 1,
        ]));
        set("coor/x", -2790);
        set("coor/y", 110);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}
