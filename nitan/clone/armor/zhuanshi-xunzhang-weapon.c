
#include <armor.h>
#include <ansi.h>

inherit MEDAL2;

void create()
{
        set_name(NOR + WHT "轉世勛章（奔流）" NOR, ({ "benliu xunzhang", "benliu", "xunzhang" }));
        set("long", NOR + WHT "轉世後獲得的勛章，上繪萬水奔流圖，閃閃發亮，甚是精緻。\n" NOR);
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("value", 200000);
                set("material", "bronze");
                set("armor_prop/damage", 500);
                set("armor_prop/str", 10);
                set("armor_prop/scborn", 1);
                set("armor_prop/whip", "apply_armor() * 3");
                set("armor_prop/club", "apply_armor() * 3");
                set("armor_prop/staff", "apply_armor() * 3");
                set("armor_prop/dagger", "apply_armor() * 3");
                set("armor_prop/hammer", "apply_armor() * 3");
                set("armor_prop/axe", "apply_armor() * 3");
                set("special/desc", HIR "用莫邪聖符升級後可鑲嵌提高除刀、劍外的所有兵器技能有效等級。" NOR); 
                set("limit", ([
                        "scborn" : 1, 
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}