// head.c -腦袋
#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(RED"頭顱"NOR, ({ "head"}));
        set_weight(300);
        if( clonep() )
            set_default_object(__FILE__);
        else {
            set("unit", "顆");
            set("value", 10);
            set("long",RED"一顆鮮血淋淋的首級，須發散亂，余血正緩緩滲出。\n"NOR);
        }
}