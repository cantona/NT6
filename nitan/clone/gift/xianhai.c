// xianhai.c 陷害卡

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "陷害卡" NOR, ({ "card", "throw card"}) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一張詭祕的卡片，據説用它可以陷害別人。\n");
                set("value", 1);
                set("no_sell", 1);
                set("unit", "張");
                set("time_to_leave", 20);
        }
}