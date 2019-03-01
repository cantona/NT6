#include <ansi.h>
#include <armor.h>

inherit BOOTS;

void create()
{
        set_name( HIW "天降﹒狂風靴" NOR, ({ "kuangfeng xue3" }) );
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "雙");
                set("long", HIW "這是一雙西域銀狐之皮制成的靴子，據說穿上後行走如狂風。\n");
                set("value", 2000000);
                
                set("armor_prop/dex", 60); //後天身法+60
                set("armor_prop/dodge", 300);
                set("special/desc", "有效輕功等級提高300級。");
                set("material", "boots");
                set("limit", ([
                         "exp" : 100000000,
                         "scborn" : 1,
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
