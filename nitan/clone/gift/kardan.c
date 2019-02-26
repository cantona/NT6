// xiandan.c 仙丹

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "福緣丹" NOR, ({ "kar dan", "dan", "kar" }) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一顆園園的仙丹，據説吃了可以增強運氣。\n");
                set("value", 10000);
                set("unit", "粒");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        message_vision("$N一仰脖，吞下了一粒" + this_object()->name() +
                       "。\n", me);
        if( query("kar", me) >= 30 )
        {
                message_vision("$N忽然“哇哇”，吐了一地。\n", me);
                tell_object(me, "你覺得嘴裏非常的苦。\n");
        } else
        {
                tell_object(me, HIG "你開始覺得你的運氣開始不錯起來，你的福緣指數提升了。\n" NOR);
                addn("kar", 1, me);
        }

        destruct(this_object());
        return 1;
}
