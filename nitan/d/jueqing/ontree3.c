#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", NOR + RED "大棗樹上" NOR);
        set("long", @LONG
這裡是棗樹頂，四下望去，突然感覺一陣眩暈，原來這裡
離地面已有百來仗高了。抬頭一看，猛然間你眼光一閃，發現
上面竟有一根樹籐(teng)垂下。
LONG);
        set("item_desc", ([
              "teng" : HIG "\n看來可以借這根樹籐爬(climb)出石窟。\n" NOR,
        ]));
        set("exits", ([
              "down"  :  __DIR__"ontree2",
        ]));

        set("no_clean_up", 0);

        setup();

}

void init()
{       
        add_action("do_climb", ({ "climb", "pa" }));
}

int do_climb(string arg)
{
        object me = this_player();
        object ob;

        if (! arg || arg != "teng" )
                return notify_fail("你要往哪兒爬？\n");

        if (! ob = find_object(__DIR__"ligui"))
                ob = load_object(__DIR__"ligui");

        if (me->is_busy())
                return notify_fail("你現在正忙著呢！\n");

        if (me->is_fighting())
                return notify_fail("你還是先把你面前這個家伙解決了再說。\n");

        message_vision(HIY "$N順著樹籐向上爬去…\n" NOR, me);

        me->move(ob);

        return 1;

}

int valid_leave(object me, string dir)
{
        if (dir != "down")
                 write(HIC "這裡離地面太高，看來你只有跳下去了。\n" NOR);

        return 1;
}

