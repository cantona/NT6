#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "天柱峰");
        set("long", @LONG
你爬上衡山五峰之一的天柱峰，四望群山縹緲雲霧中，每每天陰
地濕時候，這裡就是天柱雲氣的所在了。衡山派絕學天柱劍法便是從
中領悟出來的。
LONG );
        set("exits", ([ 
                "westdown"   : __DIR__"shanlu10",
                "eastdown"   : __DIR__"shanlu7",
        ]));

        set("objects", ([
                CLASS_D("henshan") + "/lu" : 1,
        ]));    

        set("no_clean_up", 0);

	set("coor/x", -6970);
	set("coor/y", -5550);
	set("coor/z", 30);
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
                return notify_fail("你現在正忙著呢。\n");

        if ((int)me->query_skill("sword", 1) < 30)
                return notify_fail("你的基本劍法火候不夠，無法領悟天柱劍法。\n");

        if ((int)me->query_skill("tianzhu-jian", 1) > 120)
                return notify_fail("你發現已經不能從這裡再領悟更高的天柱劍法。\n");

        if( query("jing", me)<25 )
                return notify_fail("你現在精神不濟，過于疲倦，還是休息"
                                   "一會吧。\n");

        me->receive_damage("jing", 20);

        if (me->can_improve_skill("tianzhu-jian"))
                me->improve_skill("tianzhu-jian", add);

        me->start_busy(random(2));
        message_vision(HIY "\n$N" HIY "聚精會神的參詳天柱峰，"
                       "似有所悟。\n" NOR, me);
        write(HIC "你對「天柱劍法」有了新的領悟。\n" NOR);
        return 1;
}