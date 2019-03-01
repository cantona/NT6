// xiandan.c 仙丹

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "糊塗丹" NOR, ({ "hutu dan", "dan", "hutu" }) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一顆園園很臟的丹藥，據說吃了可以降低智力。\n");
                set("value", 10000);
                set("unit", "顆");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        message_vision("$N一仰脖，吞下了一顆" + this_object()->name() +
                       "。\n", me);

        if( query("gift/int/succeed", me)<1 )
        {
                tell_object(me, "不過你覺得好像沒什麼作用。\n");
        } else
        {
                tell_object(me, HIG "一股火熱驀然從腦中升起，"
                            "你頭痛欲裂，恰在此時一股混濁之意"
                            "油然而起，頓感腦子不好使了。\n");
                addn("int", -1, me);
                addn("gift/int/succeed", -1, me);
                if( query("gift/int/all", me)>0 )
                addn("gift/int/all", -1, me);
                addn("gift/xiandan", -1, me);
        }

        destruct(this_object());
        return 1;
}

