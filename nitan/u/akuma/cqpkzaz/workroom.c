// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <room.h>
inherit CREATE_CHAT_ROOM;

int is_chat_room() { return 1; }

void create()
{
        set("short", "想入非非的工作室");
        set("long", @LONG
這是沒有建造工作室的巫師的臨時住處，這裏的設備非常簡單，只有
一些常用物品。
LONG );

        set("exits", ([ /* sizeof() == 1 */
                "north" : "/d/wizard/wizard_room",
                "down" : "/d/city/wumiao",
        ]));

        set("valid_startroom", 1);
        set("no_fight", "1");
        set("no_clean_up", 0);
        setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "north" && ! wizardp(me))
                return notify_fail("那裏只有巫師才能進去。\n");

        return ::valid_leave(me, dir);
}

void init()
{
        add_all_action();
}
