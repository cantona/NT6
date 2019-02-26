// fakesilver.c
#include <ansi.h>

inherit ITEM;
void create()
{
        set_name(HIW"白銀"NOR, ({"silver", "ingot", "silver_money"}));
        set_weight(2500000);
        set("no_get",1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "白花花的銀子，真是人見人愛。不過好像是鏢銀耶。\n");
                set("unit", "兩");
                set("material", "lead");
        }
        setup();
}
