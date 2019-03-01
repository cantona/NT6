// shigu.c
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("石鼓", ({ "shi gu", "gu" }) );
        set_weight(30000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "這是一個很古樸的石鼓，江南書香門第中的愛物。\n");
                set("value", 100);
                set("material", "stone");
                set("no_get",1);
                set("no_drop",1);
        }
        setup();
}
