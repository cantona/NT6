#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIW "開天闢地圖" NOR, ({ "kaitian tu", "kaitian", "tu" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一張古舊的圖片，上面繪着些紋樣。");
                set("unit", "張");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "盤古開天闢地的景象");
                set("can_tattoo", ({ "右臂"}));
                set("tattoo_type", ({ "傷害等級" }));
                                set("tattoo_damage", 100);
                                set("scborn", 1);
        }
}
