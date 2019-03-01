

#include <armor.h>
#include <ansi.h>

inherit CLOTH;


void create()
{
        set_name(HIB "夜行衣" NOR, ({ "yexing yi", "yexing", "yi" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("long", HIB "一件黑色的夜行衣，穿上它可以讓你身法更輕盈。\n" NOR);
                set("material", "cloth");
                set("value", 800000);
                set("armor_prop/armor", 100);
                set("armor_prop/dodge", 10);
                set("special/desc", HIR "提升有效輕功10級。"); 
                set("limit", ([
                        "exp"  :  1200000,
                ]));
                
        }
        setup();
}

int query_autoload()
{
        return 1;
}
