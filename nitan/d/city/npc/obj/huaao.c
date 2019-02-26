//Cloth :huaao.c

#include <armor.h>
inherit CLOTH;

void create()
{
        set_name("繡花短襖", ({ "hua ao", "cloth"}) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一套繡花的的布襖，略小了點，好像是童裝。\n");
                set("unit", "套");
                set("value", 100);
                set("material", "cloth");
                set("armor_prop/armor", 1);
                set("kid_only", 1);
                set("female_only", 1);
        }
        setup();
}