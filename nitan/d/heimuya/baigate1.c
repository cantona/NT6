#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "碎石小道");
        set("long", @LONG
這裏是一條碎石小道，向西可到達日月神教下第二大堂白虎堂的
大門，這裏不時有白虎堂的弟子走動。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
                "west" : __DIR__"baigate",
                "south" : __DIR__"baigate2",
        ]));
        setup();
        replace_program(ROOM);
}