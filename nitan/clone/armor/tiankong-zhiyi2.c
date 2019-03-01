
#include <armor.h>
#include <ansi.h>

inherit SURCOAT;

void create()
{
        set_name(HIW "天空之翼" NOR, ({ "tiankong zhiyi2", "tiankong", "zhiyi2" }) );
        set_weight(2000);
        set("long", HIW "這是一件白色的披風，上繪藍天白雲，飄逸之極。\n" NOR);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("material", "steel");
                                set("value", 3000000);
                set("armor_prop/armor", 200);
                                set("armor_prop/dex", 10);
                                set("armor_prop/int", 3);
                                set("armor_prop/dodge", 30);
                                set("special/desc", HIR "提升有效輕功30級。");
                                set("limit", ([ 
                                        "exp" : 18000000,
                                        "scborn" : 1,
                                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
