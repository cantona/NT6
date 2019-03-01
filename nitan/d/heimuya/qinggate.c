#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "青龍堂大門");
        set("long", @LONG
這裡是日月神教下第三大堂青龍堂的大門，門前擺放著兩座石獅，
鎮守著朱漆大門。大門兩旁站著數名輕裝弟子，雙手握著鋼刀，警惕
地注視著周圍的一切。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
                "northdown" : __DIR__"guang",
                "south" : __DIR__"dating3",
        ]));
        set("objects", ([
                __DIR__"npc/dizi5" : 2,
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        if (objectp(present("riyue dizi", environment(me)))
           && dir == "south"
            && query("family/family_name", me) != "日月神教" )
                return notify_fail(CYN "日月弟子將你攔住，說道：這裡乃神"
                                   "教重地，他人不得入內。\n" NOR);

        return ::valid_leave(me, dir);
}