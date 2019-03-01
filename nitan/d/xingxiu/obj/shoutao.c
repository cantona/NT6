#include <armor.h>
inherit HANDS;
#include <ansi.h>;

void create()
{
        set_name(HIY "金絲手套" NOR, ({ "jinsi shoutao", "shoutao", "jinsi" }));
        set_weight(2900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "這是一雙用金絲編制而成的手套，戴上他可以拿取或觸摸帶毒的物品而不會中毒。\n" NOR);
                set("unit", "雙");
                set("material", "iron");             
                set("value", 500);
                set("no_sell", "這你也賣？\n");
                set("armor_prop/armor", 1);
        }
        setup();
}