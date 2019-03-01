#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", "後院");
        set("long", @LONG
你走進後院，迎面是一個大花園，很是美觀。池中立著塊
巨大無比的假山 (jiashan)。水池的兩旁種滿了花草，鬱鬱蔥
蔥，樹木枝葉茂密，遮蓋了大半個院子。南邊一條長長的木制
長廊，通往苗家的後廳。
LONG);
        set("exits", ([
                  "south" : __DIR__"miaojia_zoulang2",
        ]));

        set("item_desc", ([
                "jiashan" : WHT "\n你發現假山背面光滑無比，似"
                            "乎還刻有什麼文字。\n" NOR,
        ]));

        set("no_clean_up", 0);
        set("coor/x", -8990);
	set("coor/y", -940);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_think", "think");
}

int do_think(string arg)
{
        object me;
        object weapon;
        me = this_player();

        if (! living(me)) return 0;

        if (! living(this_player()) || arg != "jiashan")
                return notify_fail("你要參悟什麼？\n");

        if (me->is_busy())
                return notify_fail("你現在正忙著呢。\n");

        if ((int)me->query_skill("miaojia-neigong", 1) < 1)
                return notify_fail("你發現假山上所記載的東西與自己所學"
                                   "毫無幹系，看不出究竟。\n");

        if ((int)me->query_skill("miaojia-neigong", 1) < 100)
                return notify_fail("你發現假山上所記載的內功心法過于深"
                                   "奧，自己全然無法看懂。\n");

        if ((int)me->query_skill("miaojia-neigong", 1) > 180)
                return notify_fail("你發現假山上所記載的內功心法過于膚"
                                   "淺，對自己已毫無幫助。\n");

        if (! me->can_improve_skill("miaojia-neigong"))
                return notify_fail("可能是實戰經驗不足的緣故，你再難以"
                                   "領會假山上記載的內容。\n");

        if( query("jing", me)<80 )
                return notify_fail("你現在精神不濟，過于疲倦，還是休息"
                                   "一會吧。\n");

        me->receive_damage("jing", 60);

        if (me->can_improve_skill("miaojia-neigong"))
        {
                // 天賦聰穎增加研讀速度
                if( query("special_skill/clever", me) )
                        me->improve_skill("miaojia-neigong",query("int", me)+5);
                else
                        me->improve_skill("miaojia-neigong",query("int", me));
        }

        me->start_busy(random(2));
        message_vision(HIY "\n$N" HIY "聚精會神的參詳假山上所記載的心法，"
                       "似有所悟。\n" NOR, me);
        write(HIC "你對「苗家內功」有了新的領悟。\n" NOR);
        return 1;
}