#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "天香堂大門");
        set("long", @LONG
這是日月神教下第四大堂天香堂的大門，門前擺放着兩座石獅，
鎮守着朱漆大門。大門兩旁站着數名輕裝女子，單手持着長鞭，警惕
地注視着周圍的一切。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
                    "south" : __DIR__"dating4",
                    "north" : __DIR__"tianroad2",
        ]));
        set("objects", ([
                __DIR__"npc/dizi6" : 2,
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        if (objectp(present("riyue dizi", environment(me)))
           && dir == "south"
            && query("family/family_name", me )
            && query("family/family_name", me) != "日月神教" )
                return notify_fail(CYN "日月弟子將你攔住，説道：這裏乃神"
                                   "教重地，他人不得入內。\n" NOR);

        return ::valid_leave(me, dir);
}