// douli.c 暗器

#include <ansi.h>
#include <armor.h>
inherit HEAD;

void create()
{
        set_name(BLK "油簍肩輿" NOR, ({"dou li"}) );
        set_weight(1000);
        if ( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "此輿用竹蔑做成如圍，再加黑油以防雨。此輿之取乎輕便，而不取華麗者也。\n");
                set("value", 600);
                set("unit", "頂");
                set("armor_prop/armor",2);
                set("armor_prop/per", 5);
                set("wear_msg","$N戴上一頂$n。\n");
                set("unequip_msg", "$N摘下頭上的$n，拿在手裡。\n");
        }
        setup();
}