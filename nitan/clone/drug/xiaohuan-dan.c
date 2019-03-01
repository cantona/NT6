// Code of ShenZhou
// xiaohuan-dan.c 小還丹

#include <ansi.h>

inherit ITEM;

void setup()
{}
int cure_ob(string);
void init()
{
        add_action("do_put", "put");
}

void create()
{
        set_name("小還丹", ({"xiaohuan dan", "xiaohuan", "dan"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("long", "這是一顆瑩白溜圓的小還丹。此丹乃少林奇藥，助長內力，靈效無比。\n");
                set("value", 5000);
                set("no_sell", 1);
                set("medicine", 1);
                set("no_drop", "這樣東西不能離開你。\n");
        }

        set("shaolin",1);
        setup();
}

int cure_ob(object me)
{
        if( query("neili", me) >= query("max_neili", me)*2 )
        return notify_fail("你現在沒必要吃小還丹。\n");

        if ( me->query_skill_mapped("force") != "hunyuan-yiqi" )
        {
                set("neili", 0, me);
                message_vision(HIR "$N吃下一顆小還丹，只覺得五臟欲裂，原來所練內功不符，反而大損修為！\n" NOR, me);
                me->unconcious();
                destruct(this_object());
                return 1;
        }

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

        destruct(this_object());
        return 1;
}

int do_put(string arg1, string arg2, string arg3)
{
        if( present(arg1, this_player()) == this_object() ) return 1;

        return 0;
}
