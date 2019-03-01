
#include <armor.h>
#include <ansi.h>

inherit MYHEART2;

void create()
{
        set_name(HIM "櫻花符" NOR, ({ "yinghua fu", "yinghua", "fu" }) );
        set_weight(1);
        if( clonep())
                set_default_object(__FILE__);
        else {
                set("material", "paper");
                set("unit", "張");
                set("long", HIM "一張粉紅色的靈符，上面繪有扶桑櫻花的圖畫。\n" NOR);
                set("value", 1000000);
                set("limit", ([
                        "exp"    :   2000000,
                ]));                
                set("armor_prop/qy", 1);

        }
        setup();
}

int query_autoload()
{
        return 1;
}