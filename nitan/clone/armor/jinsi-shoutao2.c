// shoutao.c  手套

#include <armor.h>
#include <ansi.h>

inherit HANDS;

void create()
{
        set_name(HIW "金絲手套" NOR, ({ "jinsi shoutao2", "jinsi", "shoutao2" }) );
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "雙");
                set("long", HIW "這是一雙金絲鑄造而成的手套，閃閃發亮。\n" NOR);
                set("value", 750000);
                set("material", "gold");
                set("armor_prop/armor", 500);
                set("armor_prop/unarmed_damage", 700);
                set("limit", ([
                        "exp"    :  2000000,
                        "int"    :  55,
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}