// huangshan.c
//

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIY"黃衫"NOR, ({ "huang shan", "shan", "cloth" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("long", "一件鵝黃色的女子長衫。");
                set("material", "cloth");
                set("armor_prop/armor", 10);
        }
        setup();
}
