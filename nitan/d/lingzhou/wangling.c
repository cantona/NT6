// Room: /lingzhou/wangling.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "西夏王陵");
        set("long", @LONG
這裡是西夏歷代皇帝的陵墓。座落在靈州西北，周圍四山環抱，環
境非常幽靜，周圍種滿了蒼鬆翠柏，其中當今西夏皇帝李元昊的父親趙
德明的陵墓最為雄偉，概因西夏雖自唐初開國，然直至宋初趙德明才稱
皇帝，所以李元昊常自比為李世民第二，而把他父親陵墓造的異常宏大。
LONG );
        set("exits", ([
                "southup" : __DIR__"qingxinquan",
                "north"   : __DIR__"chiling",
        ]));
        set("objects", ([
                __DIR__"npc/shiwushi" : 4,
        ]));
        set("outdoors", "lingzhou");
        set("coor/x", -6235);
        set("coor/y", 2985);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}