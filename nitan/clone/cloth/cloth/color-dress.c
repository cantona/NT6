// color-dress.c example cloth

#include <ansi.h>

inherit EQUIP;

void create()
{
        set_name(HIM"五彩繡花裙"NOR, ({"wucai qun", "color-dress", "dress"}));
        set_weight(700);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("value", 2000);
                set("material", "cloth");
                set("armor_type", "cloth");
                set("armor_prop/per", 2);
                set("armor_prop/armor", 3);
                set("female_only", 1);
                set("wear_msg","$N穿上一件$n。\n");
                set("remove_msg","$將$n脱了下來。\n");
        }
}