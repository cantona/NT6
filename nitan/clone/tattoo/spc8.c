#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(NOR + WHT "后羿射日圖" NOR, ({ "houyi tu", "houyi", "tu" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一張古舊的圖片，上面繪着些紋樣。");
                set("unit", "張");
                set("value", 16500);
                set("material", "paper");
                set("tattoo_long", "后羿彎弓搭箭，九個太陽盤旋在空中");
                set("can_tattoo", ({ "胸口", "後背", }));
                set("tattoo_type", ({ "身法" }));
                set("tattoo_dex", 4);
                set("tattoo_special", "accuracy");
                set("tattoo_spcname", "精準射擊");
        }
}