// unknow.c 未名仙丹

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "火紅仙丹" NOR, ({ "huohong xiandan", "dan", "xiandan" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一顆園園的火紅仙丹，據説吃了可以增強身法。增加先天屬性至五點\n");
                set("value", 10000);
                set("unit", "顆");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        message_vision("$N一仰脖，吞下了一顆" + this_object()->name() +
                       "。\n", me);
        if( query("gift/unknowdan", me) >= 5 || 
            query("gift/dex/succeed", me) >= 5 )
        {
                message_vision("$N搖搖晃晃的，突然“啪嗒”一下子摔了個跟頭。\n", me);
                tell_object(me, "你覺得吃完以後頭重腳輕的。\n");
        } else
        if (random(5) == 0)
        {
                addn("gift/dex/fail", 1, me);
                tell_object(me, "不過你覺得好像沒什麼作用。\n");
        } else
        {
                tell_object(me, HIM "霎時間你覺得腿骨欲裂，一時疼痛難"
                            "忍，幾乎暈了過去。\n" NOR);
                addn("dex", 1, me);
                addn("gift/dex/succeed", 1, me);
        }

        if( query("gift/unknowdan", me)<5 )
                addn("gift/unknowdan", 1, me);
        destruct(this_object());
        return 1;
}
