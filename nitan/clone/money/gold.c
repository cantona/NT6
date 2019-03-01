// gold.c

#include <ansi.h>

inherit MONEY;

void create()
{
        set_name(YEL "黃金" NOR , ({"gold", "ingot", "gold_money"}));
        set_weight(400);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("money_id", "gold");
                set("long", "黃澄澄的金子，人見人愛的金子，啊～～金子！\n");
                set("unit", "些");
                set("base_value", 10000 );
                set("base_unit", "兩");
                set("base_weight", 80);
        }
        set_amount(1);
}
