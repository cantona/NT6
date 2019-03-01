// mangguzhuha.c

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}
void create()
{
        set_name(NOR"莽牯"HIR"朱"NOR"蛤", ({"ha"}));
        set("unit", "只");
        set("value", 40000);
        set("long","莽牯朱蛤是瘟神爺的坐騎，那也是說說罷了。文殊菩薩騎獅子，普賢菩薩騎白象，太上老君騎青牛，這莽牯朱蛤是萬毒之王，神通廣大，毒性厲害，故老相傳，就說它是瘟菩薩的坐騎。\n");
        set("pour_type", "1");
        setup();
}

int do_eat(string arg)
{
        object me=this_player();

        if (!id(arg)) return notify_fail("你要吃什麼？\n");
        if (!present(this_object(), me))
                return notify_fail("你要吃什麼？\n");
        if (me->is_busy() || random(2)==1 )
                return notify_fail("別急，慢慢吃，小心別毒死了。\n");

        message_vision(HIG"$N吃下一只"+name()+HIG"，頓覺精力漸生，全身委頓漸漸消去。\n" NOR, me);
        if (me->query_condition("drunk"))
                me->apply_condition("drunk",0);
        if (me->query_condition("flower_poison"))
                me->apply_condition("flower_poison",0);
        if (me->query_condition("ice_poison"))
                me->apply_condition("ice_poison",0);
        if (me->query_condition("iceshock"))
                me->apply_condition("iceshock",0);
        if (me->query_condition("rose_poison"))
                me->apply_condition("rose_poison",0);
        if (me->query_condition("sanxiao_poison"))
                me->apply_condition("sanxiao_poison",0);
        if (me->query_condition("scorpion_poison"))
                me->apply_condition("scorpion_poison",0);
        if (me->query_condition("slumber_drug"))
                me->apply_condition("slumber_drug",0);
        if (me->query_condition("snake_poison"))
                me->apply_condition("snake_poison",0);
        if (me->query_condition("ss_poison"))
                me->apply_condition("ss_poison",0);
        if (me->query_condition("xx_poison"))
                me->apply_condition("xx_poison",0);
        if (me->query_condition("zhua_poison"))
                me->apply_condition("zhua_poison",0);
        me->start_busy(2);
        destruct(this_object());
        return 1;
}