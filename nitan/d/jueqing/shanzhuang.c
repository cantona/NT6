#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "絕情山莊");
        set("long", @LONG
此處便是絕情山莊，但見山莊掩映于蔥翠的林木之下，四
處繁花遍布，景致宜人。時有醉人的花香飄過，間雜著清脆的
百鳥之聲，令人不由心曠神怡。
LONG);
        set("outdoors", "jueqing");
        set("exits", ([
               "enter" : __DIR__"dating",
               "south" : __DIR__"shiban",
        ]));

        set("objects", ([
                __DIR__"npc/dizi1" : 4,
                __DIR__"npc/dizi2" : 4,
                CLASS_D("jueqing") + "/fan" : 1,
        ]));  

        set("no_clean_up", 0);

        setup();
}

int valid_leave(object me, string dir)
{
        object guard;

        if (dir != "enter"
           || ! objectp(guard = present("fan yiweng", this_object())))
                return ::valid_leave(me, dir);

        return guard->permit_pass(me, dir);
}
