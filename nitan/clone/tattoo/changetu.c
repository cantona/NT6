#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIM "嫦娥仙子圖" NOR, ({ "change tu", "cange", "tu" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一張古舊的圖片，上面繪著些紋樣。");
                set("unit", "張");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "嫦娥奔月的圖樣");
                set("can_tattoo", ({ "臉部"}));
                set("tattoo_type", ({ "容貌" }));
                set("tattoo_per", 5);
                                set("scborn", 1);
        }
}
