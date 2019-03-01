//qingpao.c

#include <armor.h>

inherit CLOTH;

void create()
{
    set_name("青色絲袍", ({"si pao", "cloth", "pao"}) );
    set_weight(1000);
    if( clonep() )
       set_default_object(__FILE__);
    else {
        set("female_only", 1);
        set("unit", "件");
        set("long", "這是件質地輕柔的青色鏤花絲袍，特別受女性青睞。\n");
        set("material", "cloth");
        set("value",70);
        set("armor_prop/armor", 4);
    }
    setup();
}