// jieqiwan.c
inherit ITEM;
#include <ansi.h>

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(MAG"九轉結氣丸"NOR, ({"jieqi wan", "jieqi", "wan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("vegetable", 15);
                set("nostrum", 82);
                set("level", 110);
                set("long","這是一顆透著紫紅色調的九轉結氣丸。此丸乃武當珍藥，提高功力，靈效無比。\n");
                set("value", 100);
                set("no_drop", "這樣東西不能離開你。\n");
        }
        set("pour_type", "1");
        setup();
}

int do_eat(string arg)
{
        int force_limit, neili_limit;

        object me = this_player();

        force_limit = me->query_skill("force")*10;
        neili_limit=query("max_neili", me);

        if(!id(arg)) return notify_fail("你要吃什麼？\n");
        if(!present(this_object(), me))
                return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎著了。\n");

        me->start_busy(2);
        if ( me->query_skill_mapped("force") != "taiji-shengong" )
        {
                addn("max_neili", -10, me);
                message_vision(HIR "$N吃下一顆九轉結氣丸，只覺得肝腸寸斷，原來所練內功不符，反而大損真元！\n" NOR, me);
//                me->unconcious();
                me->start_busy(10);
        }
        else
        {
                if ( (int)me->query_condition("taoist_drug" ) > 0 )
                {
                        addn("max_neili", -1, me);
                        message_vision(HIR "$N吃下一顆九轉結氣丸，只覺得頭重腳輕，搖搖欲倒，原來服食太急太多，藥效適得其反！\n" NOR, me);
                }
                else if ( neili_limit <= force_limit )
                {
                        addn("max_neili", 1, me);
                        message_vision(HIG "$N吃下一顆九轉結氣丸，只覺渾身真氣遊走，過紫宮，入泥丸\n透十二重樓，遍布奇筋八脈！\n" NOR, me);
                }
                me->apply_condition("taoist_drug", 60);
        }
        destruct(this_object());
        return 1;
}
