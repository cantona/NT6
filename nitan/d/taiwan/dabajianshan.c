// Room: /d/taiwan/dabajianshan.c
// Last Modifyed by Ahda on Jan. 4 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "大霸尖山");
        set("long", @LONG
竹東郡與大湖郡交界處，一峯突立，即為大霸尖山，山高千丈，和
東側連互的次高山組成山脈，素有「世紀奇峯」之稱的大霸尖山，巨巖
突兀，泰雅族尊奉為「祖山」。
LONG );
        set("exits", ([
                "westdown" : __DIR__"maolishe",
        ]));
        set("objects", ([
//                __DIR__"npc/taiyaren": 1,
        ]));
        set("outdoors", "taiwan");
        set("coor/x", 2530);
        set("coor/y", -6990);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
