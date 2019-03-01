// xiandan.c 仙丹

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "美容丸" NOR, ({ "per wan", "wan", "per" }) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一顆園園的丹丸，據說吃了可以越來越美麗，是每個女子夢寐以求的好東西。\n");
                set("value", 10000);
                set("unit", "粒");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        message_vision("$N一仰脖，吞下了一粒" + this_object()->name() +
                       "。\n", me);
        if( query("per", me) >= 30 )
        {
                message_vision("$N忽然“哇哇”，吐了一地。\n", me);
                tell_object(me, "你覺得嘴裡非常的苦。\n");
        } else
        {
                tell_object(me, HIG "你開始發覺你的容貌開始改變，變的漂亮多了。\n" NOR);
                addn("per", 1, me);
        }

        destruct(this_object());
        return 1;
}
