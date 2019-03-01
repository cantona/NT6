#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "莊府大廳");
        set("long", @LONG
這是一間靈堂，堂上供了七八個牌位。看來一座靈堂上供的是一
家死人。
LONG );
    set("exits", ([
        "east" : "/d/beijing/zhuang5",
    ]));
    set("objects", ([
        "/d/shenlong/npc/dizi": 1,
    ]));
    set("outdoors", "beijing");
    set("coor/x", 90);
        set("coor/y", 4720);
        set("coor/z", 0);
        setup();
    replace_program(ROOM); 
}