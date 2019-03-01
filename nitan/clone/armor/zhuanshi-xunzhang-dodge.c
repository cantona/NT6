
#include <armor.h>
#include <ansi.h>

inherit MEDAL2;

void create()
{
        set_name(HIW "轉世勛章（無極）" NOR, ({ "wuji xunzhang", "wuji", "xunzhang" }));
        set("long", HIW "轉世後獲得的勛章，上繪天地無極圖，閃閃發亮，甚是精致。\n" NOR);
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("value", 200000);
                set("material", "bronze");
                set("armor_prop/damage", 500);
                set("armor_prop/dex", 10);
                set("armor_prop/int", 10);
                set("armor_prop/scborn", 1);
                set("armor_prop/dodge", "apply_armor() * 2");
                set("armor_prop/parry", "apply_armor() * 2");
                set("special/desc", HIR "用莫邪聖符升級後可鑲嵌提高有效輕功及有效招架等級。" NOR); 
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