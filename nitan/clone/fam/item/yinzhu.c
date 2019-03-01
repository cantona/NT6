#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + HIW "銀蛛絲" NOR, ({"yinzhu si", "yinzhu", "si"}));
        set_weight(800);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "大雪山銀蛛所產的絲，強韌堅固，極為珍貴。\n" NOR);
                set("unit", "卷");
                set("value", 10000);
                set("item_origin", 1);
                set("material_attrib", "stone");
                set("material_name", NOR + HIW "銀蛛絲" NOR);
                set("can_make", ({ "護甲", "戰衣", "腰帶", "護腕", "靴子", "鞭" }));
                set("power_point", 70);
        }
}

int query_autoload()
{
        return 1;
}
