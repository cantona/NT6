// ycloth.c

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIY"黃馬褂"NOR, ({ "yellow magua", "cloth" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","這是件黃馬褂，是當今御賜，極盡榮耀，極顯恩寵。\n");
                set("unit", "件");
                set("value", 0);
                set("material", "cloth");
                set("armor_prop/armor", 150);
                set("armor_prop/per", 3);
        }
        setup();
}