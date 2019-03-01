// datang1.c 大堂一進
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "大堂一進");
        set("long", @LONG
這裏是大堂，是全真教接待客人的地方。堂很大，幾十張桌椅一
字排開也絲毫不顯擁擠。地下鋪着整齊的青磚，幾名道童正忙前忙後
地端茶送水招呼客人。
LONG
        );
        set("exits", ([
                "east" : __DIR__"datang2",
                "west" : __DIR__"damen",
                "north" : __DIR__"huizhentang",
                "south" : __DIR__"xianzhentang",
        ]));
        set("objects",([
                __DIR__"npc/daotong" : 1,
                CLASS_D("quanzhen")+"/first" :1,
        ]));
        set("valid_startroom", 1);
        set("coor/x", -2800);
        set("coor/y", 110);
        set("coor/z", 170);
        setup();
        "clone/board/quanzhen_b"->foo();
}
