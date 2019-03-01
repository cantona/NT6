// zhitao.c 指套

#include <armor.h>

inherit FINGER;

void create()
{
        set_name( "指套", ({ "finger", "zhitao" }) );
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "副");
                set("long", "這是五個環環相鏈的鐵指套，前端鋒利如刃，既可暗藏掌中傷人，又可保護指關節。\n");
                set("value", 6000);
                set("material", "steel");
                set("armor_prop/armor", 5);
        }
        setup();
}