// xiaohuan-dan.c 小還丹

#include <ansi.h>

inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIW"小還丹"NOR, ({"xiaohuan dan", "xiaohuan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("vegetable", 46);
                set("nostrum", 78);
                set("level", 60);
                set("long","這是一顆瑩白溜圓的小還丹。此丹乃少林奇藥，助長內力，靈效無比。\n");
                set("value", 10000);
                set("no_drop", "這樣東西不能離開你。\n");
        }
        set("pour_type", "1");

        set("shaolin",1);
        setup();
}

int do_eat(string arg)
{
        object me = this_player();

        if(!id(arg)) return notify_fail("你要吃什麼？\n");
        if(!present(this_object(), me))
                return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎着了。\n");

        if( query("neili", me) >= query("max_neili", me)*2 )
                return notify_fail("你現在沒必要吃小還丹。\n");
        me->start_busy(2);
        if( me->query_skill_mapped("force") != "hunyuan-yiqi" &&
                me->query_skill_mapped("force") != "zhanzhuang-gong" )
        {
                set("neili", 0, me);
                message_vision(HIR "$N吃下一顆小還丹，只覺得五臟欲裂，原來所練內功不符，反而大損修為！\n" NOR, me);
//                me->unconcious();
                me->start_busy(10);
        }
        else
        {
                if ( (int)me->query_condition("bonze_drug" ) > 0 )
                {
                        addn("neili", -200, me);
                        message_vision(HIR "$N吃下一顆小還丹，只覺得頭重腳輕，搖搖欲倒，原來服食太急太多，藥效適得其反！\n" NOR, me);
                }
                else
                {
                        addn("neili", 200, me);
                        message_vision(HIY "$N吃下一顆小還丹，只覺得身輕如燕，四肢百骸真氣充盈無比，幾欲奔騰而出！\n" NOR, me);
                }
                me->apply_condition("bonze_drug", 30);
        }
        destruct(this_object());
        return 1;
}