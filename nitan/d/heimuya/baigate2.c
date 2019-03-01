#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "碎石小道");
        set("long", @LONG
這裡是一條碎石小道，向西可到達日月神教下第二大堂白虎堂的
大門，這裡不時有白虎堂的弟子走動。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
                "north" : __DIR__"baigate1",
                "south" : __DIR__"linjxd3",
        ]));
        set("objects", ([
                __DIR__"npc/dizi4" : 1,
        ]));
        setup();
        replace_program(ROOM);
}