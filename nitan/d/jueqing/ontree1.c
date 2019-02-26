#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", NOR + RED "大棗樹上" NOR);
        set("long", @LONG
這裏是石窟內的一棵百仗高的大棗樹上，但見此處被樹葉
所蓋，密不透風。
LONG);
        set("exits", ([
              "up"    :  __DIR__"ontree2",
              "down"  :  __DIR__"undertan",
        ]));

        set("no_clean_up", 0);

        setup();

}

void init()
{       
        add_action("do_jump", ({ "jump", "tiao" }));
}

int do_jump(string arg)
{
        object me = this_player();
        object ob;

        if (! arg || arg != "down" )
                return notify_fail("你要往哪兒跳？\n");

        if (! ob = find_object(__DIR__"undertan"))
                ob = load_object(__DIR__"undertan");

        if (me->is_busy())
                return notify_fail("你現在正忙着呢！\n");

        if (me->is_fighting())
                return notify_fail("你還是先把你面前這個傢伙解決了再説。\n");

        tell_room(ob, HIC + me->name() + "從大棗樹上跳了下來。\n" NOR, me);

        me->move(ob);

        return 1;

}

int valid_leave(object me, string dir)
{
        if (dir == "down")
        { 
               write(HIC "這裏離地面太高，看來你只有跳下去了。\n" NOR);
               return -1;
        }

        return 1;
} 

