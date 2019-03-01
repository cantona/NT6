// dahuan-dan.c 大還丹

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("大還丹", ({"dahuan dan", "dahuan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("long", "這是一顆紫紅晶亮的大還丹。此丹乃少林珍藥，提"
                            "高功力，靈效無比。\n");
                set("value", 10000);
                set("only_do_effect", 1);
        }

        setup();
}

int do_effect(object me)
{
        int force_limit, neili_limit;

        force_limit = me->query_skill("force")*10;
        neili_limit=query("max_neili", me);
        
        me->start_busy(2);
        if ((int)me->query_condition("bonze_drug" ) > 0)
        {
                addn("max_neili", -1, me);
                message_vision(HIR "$N" HIR "吃下一顆大還丹，只覺得頭"
                               "重腳輕，搖搖欲倒，原來服食太急太多，藥"
                               "效適得其反！\n" NOR, me);
        } else
        if (neili_limit <= force_limit)
        {
                addn("max_neili", 1, me);
                message_vision(HIG "$N" HIG "吃下一顆大還丹，只覺得體內"
                               "真力源源滋生，過紫宮，入泥丸透十二重樓，"
                               "遍布奇筋八脈，全身功力頓然提高！\n" NOR, me);
        }

        me->apply_condition("bonze_drug", 60);
        destruct(this_object());
        return 1;
}
