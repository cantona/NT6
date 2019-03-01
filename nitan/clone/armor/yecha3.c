
#include <armor.h>
#include <ansi.h>

inherit MYHEART;

void create()
{
        set_name(HIG "夜叉" NOR, ({ "yecha fu3", "yecha", "fu3" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "paper");
                set("unit", "張");
                set("long", HIG "這是一張道符，上面畫著一個奇特的鬼怪，名曰：夜叉。\n" NOR);
                set("value", 195000);
                set("limit", ([
                        "exp"    :   8000000,
                        "str"    :   60,
                        "dex"    :   40,
                        "con"    :   50,
                ]));
                set("apply_prop/damage", 100);
                set("armor_prop/unarmed_damage", 100);
                set("armor_prop/int", 3);
                set("armor_prop/str", 3);
        }
        setup();
}

int query_autoload()
{
        return 1;
}