// cloth.c

#include <armor.h>;
inherit CLOTH;

void create()
{
        set_name("鶉衣", ({ "cloth" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "丐幫弟子行走江湖的時候，一般都是穿這樣的衣服。");
                set("unit", "件");
                set("material", "cloth");
                set("armor_prop/armor", 1);
        }
        setup();
}
