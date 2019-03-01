#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIM "地藏轉世圖" NOR, ({ "dizhang tu", "dizhang", "tu" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一張古舊的圖片，上面繪著些紋樣。");
                set("unit", "張");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "地藏王的模樣");
                set("can_tattoo", ({ "後背"}));
                set("tattoo_type", ({ "根骨" }));
                set("tattoo_con", 10);
                                set("tattoo_int", -7);
                                set("scborn", 1);
        }
}
