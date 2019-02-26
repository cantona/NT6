
#include <armor.h>
#include <ansi.h>

inherit MYHEART2;

void create()
{
        set_name(NOR + YEL "黃符紙" NOR, ({ "huangfu zhi", "huangfu", "zhi" }) );
        set_weight(1);
        if( clonep())
                set_default_object(__FILE__);
        else {
                set("material", "paper");
                set("unit", "張");
                set("long", NOR + YEL "一張泛黃的符紙，上面用紅色的顏料繪着各種奇怪的符號。\n" NOR);
                set("value", 1000000);
                set("limit", ([
                        "exp"    :   2000000,
                ]));                
                set("armor_prop/qy", 5);

        }
        setup();
}

int query_autoload()
{
        return 1;
}