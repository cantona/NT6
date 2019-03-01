// Room: /d/gaibang/underwx.c

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "草堆下面");
        set("long", @LONG
這是無錫城外杏子林丐幫大義分舵草堆的洞裡。四周丟滿了各種雜
物，還有丐幫弟子收集的破銅爛鐵等。從這裡通往丐幫的秘密通道。
LONG );
        set("exits", ([
                "out"   : "/d/wuxi/dayifenduo",
                "north" : __DIR__"wxandao2",
        ]));
        set("objects",([
                CLASS_D("gaibang") + "/xie" : 1,
        ]));
        set("coor/x", 400);
        set("coor/y", -740);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}