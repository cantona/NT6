#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(NOR + WHT "冥皇煉獄圖" NOR, ({ "lianyu tu", "lianyu", "tu" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一張古舊的圖片，上面繪着些紋樣。");
                set("unit", "張");
                set("value", 16500);
                set("material", "paper");
                set("tattoo_long", "七重冥王站立於煉獄白骨堆之上，無數冤魂圍繞其身");
                set("can_tattoo", ({ "胸口", "後背", }));
                set("tattoo_type", ({ "膂力", "身法" }));
                set("tattoo_str", 2);
                set("tattoo_dex", 2);
                set("tattoo_special", "hatred");
                set("tattoo_spcname", "殺氣沖霄");
        }
}