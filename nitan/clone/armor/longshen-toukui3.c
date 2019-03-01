// toukui.c 頭盔
 
#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIM "龍神頭盔" NOR, ({ "longshen toukui", "longshenshen3", "toukui3" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "steel");
                set("unit", "頂");
                set("long", HIM "這是一頂龍骨鑄造的頭盔，用以保護頭部。\n" NOR);
                set("value", 3500000);
                set("armor_prop/armor", 400);
                set("limit", ([
                        "dex"    :   65,
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}