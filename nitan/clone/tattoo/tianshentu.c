#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIY "真龍天神圖" NOR, ({ "tianshen tu", "tianshen", "tu" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一張古舊的圖片，上面繪着些紋樣。");
                set("unit", "張");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "真龍天神的模樣");
                set("can_tattoo", ({ "臉部"}));
                set("tattoo_type", ({ "容貌" }));
                set("tattoo_per", 5);
                                set("scborn", 1);
        }
}
