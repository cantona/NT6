inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "南院");
        set("long", @LONG
這裡是南跨院，院子裡有棵很大的榕樹，將天空大部遮住
院子裡靜悄悄的，幾只高大的藏獒在樹下來回踱步。 
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "east" : __DIR__"yaoshi",
                "south" : __DIR__"liandu",
                "west" : __DIR__"xiangfang",
                "north" : __DIR__"lianwu",
        ]));
        set("objects", ([
                  "/clone/quarry/gou3" : 2,
        ]));
        setup();
}

void init()
{
        add_action("do_climb", "climb");
}

int do_climb(string arg)
{
       
        object me = this_player();
        object ob;

        if (! arg || arg != "tree")
                return notify_fail("你要爬什麼？\n");

        message_vision(HIC "$N" HIC "撮了撮手，攀著榕樹的枝杈三下兩"
                       "下就爬了上去。\n" NOR, me);

        ob = load_object(__DIR__"tree");
        ob = find_object(__DIR__"tree");
        message("vision",query("name", me)+"從下面爬了上來。\n",ob);
        me->move(__DIR__"tree");
        return 1;
}
