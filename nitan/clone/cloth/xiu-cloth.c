// xiu-cloth.c example cloth

#include <ansi.h>

inherit EQUIP;

void create()
{
        set_name( HIM "淡煙秀才裝" NOR, ({ "xiucai zhuang", "xiucai", "zhuang" }) );
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("value", 1000);
                set("material", "cloth");
                set("armor_type", "cloth");
                set("armor_prop/armor", 2);
                set("wear_msg","$N穿上一件$n。\n");
                set("remove_msg","$N將$n脱了下來。\n");
        }

        setup();
}