
#include <armor.h>
#include <ansi.h>

inherit MYHEART2;

void create()
{
        set_name(HIR "火麒麟﹒凈化" NOR, ({ "jinghua fu", "jinghua", "fu" }) );
        set_weight(1);
        if( clonep())
                set_default_object(__FILE__);
        else {
                set("material", "paper");
                set("unit", "張");
                set("long", HIR "這是一張火紅色的靈符，火燄中隱約浮現出「凈化」二字。\n" NOR);
                set("value", 10000000);
                set("limit", ([
                        "exp"    :   50000000,
                ]));
                set("armor_prop/int", 40);                
                set("armor_prop/qy", 3);
                set("armor_prop/fy", 3);

        }
        setup();
}

int query_autoload()
{
        return 1;
}