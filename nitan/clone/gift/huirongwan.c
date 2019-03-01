// xiandan.c 仙丹

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "毀容丸" NOR, ({ "huirong wan", "wan", "huirong" }) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一顆園園的丹丸，據說吃了可以變的越來越醜，真不知道誰還要這個東西耶。\n");
                set("value", 10000);
                set("unit", "粒");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        message_vision("$N一仰脖，吞下了一粒" + this_object()->name() +
                       "。\n", me);
        if( query("per", me) <= 13 )
        {
                message_vision("$N忽然“哇哇”，吐了一地。\n", me);
                tell_object(me, "你覺得嘴裡非常的苦。\n");
        } else
        {
                tell_object(me, HIG "你開始發覺你的容貌開始改變，變的難看多了。\n" NOR);
                addn("per", -1, me);
        }

        destruct(this_object());
        return 1;
}
