#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(MAG "粉"RED"紅"BLU"披"HIW"風" NOR, ({ "color cloth", "cloth" }) );
        set_weight(1000);
        set("value", 5);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這件粉紅色的披風上面繡著幾只鳳凰，煞是性感。\n");
                set("unit", "塊");
                set("material", "cloth");
                set("armor_prop/con",20);
                set("armor_prop/per", 200);
                set("female_only", 1);
        }
        setup();
}
