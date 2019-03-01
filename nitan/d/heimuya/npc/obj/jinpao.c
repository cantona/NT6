#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIW "日月錦袍" NOR, ({ "jin pao", "jin", "pao", "cloth" }));
        set("long", HIW "這是一件日月神教長老所穿戴的華麗錦袍。\n" NOR);
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "件");
                set("armor_prop/armor", 1);
                set("value", 10000);
                set("no_sell", "我的天…連日月神教的東西你都拿出來賣？");
        }
        setup();
}