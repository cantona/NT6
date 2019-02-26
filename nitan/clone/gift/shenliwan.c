// shenliwan.c 神力丸

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "神力丸" NOR, ({ "shenli wan", "wan"}) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一顆圓圓的神力丸，據説吃了可以增強臂力。增加先天屬性至五點\n");
                set("value", 10000);
                set("unit", "顆");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        message_vision("$N一仰脖，吞下了一顆" + this_object()->name() +
                       "。\n", me);
        if( query("gift/shenliwan", me) >= 5 || 
            query("gift/str/succeed", me) >= 5 )
        {
                message_vision("$N眨眨眼。\n", me);
                tell_object(me, "你覺得這藥沒啥味道，還不如花生好吃。\n");
        } else
        if (random(5) == 0)
        {
                addn("gift/str/fail", 1, me);
                tell_object(me, "不過你覺得好像沒什麼作用。\n");
        } else
        {
                tell_object(me, HIR "你覺得雙臂幾乎爆裂，充滿了力量。\n" NOR);
                addn("str", 1, me);
                addn("gift/str/succeed", 1, me);
        }

        if( query("gift/shenliwan", me)<5 )
                addn("gift/shenliwan", 1, me);
        destruct(this_object());
        return 1;
}
