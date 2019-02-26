#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", "騰蛟亭");
        set("long", @LONG
這裏是一個花園中的小亭子，雕樑畫棟，古色古香。壁上
掛着一幅「月下舞劍圖」。
LONG);

        set("exits", ([
                "south" : __DIR__"huating1",
                "west" : __DIR__"huayuan3",
        ]));

        set("item_desc", ([
                "tu": HIY "\n你只見圖中少女手持鋼鈎，含笑而立。恍惚間你"
                      "似乎覺得有無\n數道劍氣撲面而來。這裏面似乎隱含着"
                      "某種奧祕。\n\n" NOR,
        ]));
        setup();
}

void init()
{
        add_action("do_think", "think");
}

int do_think(string arg)
{
        object me = this_player();
        int add;

        if( query("special_skill/clever", me) )
                add = me->query_int() * 4;
        else
                add = me->query_int() * 3;

        if (! living(me) || arg != "tu")
                return notify_fail("你要參悟什麼？\n");

        if (me->is_busy() || me->is_fighting())
                return notify_fail("你現在正忙着呢。\n");

        if ((int)me->query_skill("sword", 1) < 30)
                return notify_fail("你的基本劍法火候不夠，無法領悟圖畫"
                                   "上的劍法。\n");

        if ((int)me->query_skill("jinwu-goufa", 1) < 30)
                return notify_fail("你發現圖中所記載的劍法過於深奧，自"
                                   "己一時難以領會。\n");

        if ((int)me->query_skill("jinwu-goufa", 1) > 150)
                return notify_fail("你發現圖中所記載的劍法過於膚淺，自"
                                   "己無法領會到任何東西。\n");

        if( query("jing", me)<25 )
                return notify_fail("你現在精神不濟，過於疲倦，還是休息"
                                   "一會吧。\n");

        me->receive_damage("jing", 20);

        if (me->can_improve_skill("jinwu-goufa"))
                me->improve_skill("jinwu-goufa", add);

        me->start_busy(random(2));
        message_vision(HIY "\n$N" HIY "聚精會神的參詳圖中所記載的劍法，"
                       "似有所悟。\n" NOR, me);
        write(HIC "你對「金蜈鈎法」有了新的領悟。\n" NOR);
        return 1;
}