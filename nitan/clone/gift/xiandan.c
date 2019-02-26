// xiandan.c 仙丹

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "仙丹" NOR, ({ "xian dan", "dan", "xiandan" }) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一顆園園的仙丹，據説吃了可以增強智力。"
                    "增加先天屬性至五點\n");
                set("value", 10000);
                set("unit", "顆");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        message_vision("$N一仰脖，吞下了一顆" + this_object()->name() +
                       "。\n", me);
        if( query("gift/xiandan", me) >= 5 || 
            query("gift/int/succeed", me) >= 5 )
        {
                message_vision("$N忽然“哇哇”，吐了一地。\n", me);
                tell_object(me, "你覺得嘴裏非常的苦。\n");
        } else
        if (random(5) == 0)
        {
                addn("gift/int/fail", 1, me);
                tell_object(me, "不過你覺得好像沒什麼作用。\n");
        } else
        {
                tell_object(me, HIG "一股火熱驀然從腦中升起，"
                            "你頭痛欲裂，恰在此時一股清涼之意"
                            "油然而起，頓感舒泰無比。\n");
                addn("int", 1, me);
                addn("gift/int/succeed", 1, me);
        }

        if( query("gift/xiandan", me)<5 )
                addn("gift/xiandan", 1, me);
        destruct(this_object());
        return 1;
}
