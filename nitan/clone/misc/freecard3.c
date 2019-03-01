// card.c
#include <ansi.h>;

inherit ITEM;

void create()
{
        set_name(HIY "五十萬兩建房卡" NOR, ({"fee free card"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long",HIY "這是一張價值五十萬兩黃金的建房卡，把他交給魯班可以建相應價值的房屋。\n" NOR);
                set("value", 1);
                                set("fee free", 500000);
                set_weight(100);
        }
        setup();
}

int query_autoload()
{
        return 1;
}