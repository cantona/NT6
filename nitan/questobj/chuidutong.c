// chuidutong.c 吹毒筒
#include <ansi.h>
inherit ITEM;

#define max_poison 15
#define least_poison 5

void init()
{
}

void create()
{
        set_name(HIW"吹毒筒"NOR, ({ "chuidu tong", "ct" }) );
        set("taskobj", 1);
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
                set("unit", "支");
                set("value", 0);
                set("material", "steel");
                set("long", "這是一支黑黝黝的鐵筒，不知道做什麼用的。\n");
        }
        setup();
}