#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "石廩峯");
        set("long", @LONG
芙蓉峯是衡山五峯之一，每逢下雨的時候，雨水打在峯中的巖石
上，發出巨大的回聲，聲音洪亮，猶如書院中的讀書聲，是以該峯由
此而來，衡山派的石廩劍法也由此而悟。
LONG );

        set("exits", ([
                "westdown"   : __DIR__"liuyunping",
        ]));

        set("objects", ([
                __DIR__"npc/dizi1" : 2,
        ]));

        set("no_clean_up", 0);

	set("coor/x", -6920);
	set("coor/y", -5520);
	set("coor/z", 40);
	setup();
}

void init()
{       
        add_action("do_think", "think");
}

int do_think(string arg)
{
        object here, me = this_player();
        int add;

        if( query("special_skill/clever", me) )
                add = me->query_int() * 4;
        else
                add = me->query_int() * 3;

        if (! living(me) || arg != "feng")
                return notify_fail("你要參悟什麼？\n");

        if (me->is_busy() || me->is_fighting())
                return notify_fail("你現在正忙着呢。\n");

        if ((int)me->query_skill("sword", 1) < 30)
                return notify_fail("你的基本劍法火候不夠，無法領悟石廩劍法。\n");

        if ((int)me->query_skill("shilin-jian", 1) > 120)
                return notify_fail("你發現已經不能從這裏再領悟更高的石廩劍法。\n");

        if( query("jing", me)<25 )
                return notify_fail("你現在精神不濟，過於疲倦，還是休息"
                                   "一會吧。\n");

        me->receive_damage("jing", 20);

        if (me->can_improve_skill("shilin-jian"))
                me->improve_skill("shilin-jian", add);

        me->start_busy(random(2));
        message_vision(HIY "\n$N" HIY "聚精會神的參詳石廩峯，"
                       "似有所悟。\n" NOR, me);
        write(HIC "你對「石廩劍法」有了新的領悟。\n" NOR);
        return 1;
}