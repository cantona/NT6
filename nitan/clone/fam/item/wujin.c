#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + YEL "烏金礦" NOR, ({"wujin kuang", "wujin", "kuang"}));
        set_weight(1800);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", YEL "這是一塊極為罕見的烏金礦石，堅如玄鐵，珍貴無比。\n" NOR);
                set("unit", "塊");
                set("value", 8000);
                set("item_origin", 1);
                set("material_attrib", "stone");
                set("material_name", NOR + YEL "烏金礦" NOR);
                set("can_make", ({ "劍", "刀", "錘", "短兵", "簫" }));
                set("power_point", 50);
        }
}

int query_autoload()
{
        return 1;
}
