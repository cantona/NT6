#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "鄂魚潭中");
        set("long", @LONG
鄂魚潭中寒水刺骨，深不見底，潭底水聲潺潺，令人毛骨
悚然。看來要離開這裡只有遊(swim)回岸邊(bank)。
LONG);
        set("objects", ([
                "/clone/quarry/eyu" : 1 + random(6),
        ]));

        set("no_clean_up", 0);
        setup();
}

void init()
{       
        add_action("do_swim", ({ "swim", "you" }));
}

int do_swim(string arg)
{
        object me = this_player();
        object ob;

        if (! arg || arg != "bank" )
                return notify_fail("你要往哪兒遊？\n");

        if (! ob = find_object(__DIR__"eyutan1"))
                ob = load_object(__DIR__"eyutan1");

        if (me->is_busy())
                return notify_fail("你現在正忙著呢！\n");

        if (me->is_fighting())
                return notify_fail("你還是先把你面前這個家伙解決了再說。\n");

        tell_object(me, HIY "你使盡所有力氣向岸邊遊去…\n" NOR);
        tell_room(ob, HIC + me->name() + "遊了上來。\n" NOR, me);
        me->move(ob);

        return 1;
}