inherit ROOM;
#include <ansi.h>

void create()
{
        set("short","明教地道");
        set("long", @LONG
這裏是明教的地道，只見前方一條彎彎曲曲的道路不知道通往何
方。你只有試走（zou）下去看看。
LONG );
        set("exits",([
            "out"    : "/d/lanzhou/guangchang",
        ]));
        set("no_beg","1");

        set("no_clean_up", 0);
        setup();
}

void init()
{
        add_action("do_zou", "zou");
}

int do_zou(string arg)
{       
        object me = this_player();
 
        if (me->is_busy() || me->is_fighting())
             return notify_fail("你還是忙完了再説吧！\n");

        message_vision(HIY "$N" HIY "快步向前走去 ……\n" NOR, me);

        me->move(__DIR__"neishi");

        message_vision(HIY "$N" HIY "從地道中跳了出來！\n" NOR, me);

        me->start_busy(2);

        return 1;
}
