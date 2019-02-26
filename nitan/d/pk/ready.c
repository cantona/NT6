// Room: /d/pk/ready.c

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "屠人場休息室");
        set("long", @LONG
這裏黑乎乎的，地上還有一些粘滿了血跡的布條，偶然也看得到斷
了的長劍、鋼刀什麼的。北面的門緊緊的鎖着，裏面散發出一陣陣血腥
的氣味。
LONG
        );
        set("exits", ([
                "south" : __DIR__"entry",
        ]));

        set("no_fight", 1);
        setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "south")
                message_vision("$N溜出了休息室。\n", me);
        return 1;
}