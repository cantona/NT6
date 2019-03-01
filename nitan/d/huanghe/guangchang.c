// Room: /huanghe/guangchang.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "廣場");
        set("long", @LONG
廣場佔地甚大，部置嚴謹。往西過去可達黃河幫的「俠義廳」。
周圍則是些房舍，供幫眾居住。
LONG );
        set("exits", ([
                "east"  : __DIR__"huanghegate",
                "west"  : __DIR__"xiayiting",
        ]));
        set("objects", ([
                __DIR__"npc/wu" : 1,
                __DIR__"npc/qian" : 1,
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "huanghe");
        set("coor/x", -2010);
        set("coor/y", 520);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}