#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIW "夜叉魑魅圖" NOR, ({ "yecha tu", "yecha", "tu" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一張古舊的圖片，上面繪著些紋樣。");
                set("unit", "張");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "夜叉和魑魅模樣");
                set("can_tattoo", ({ "後背"}));
                set("tattoo_type", ({ "臂力" }));
                set("tattoo_str", 10);
                                set("tattoo_dex", -8);
                                set("scborn", 1);
        }
}
