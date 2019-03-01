#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(NOR + WHT "赤蛇圖騰" NOR, ({ "chishe tu", "chishe", "tu" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一張古舊的圖片，上面繪着些紋樣。");
                set("unit", "張");
                set("value", 4000);
                set("material", "paper");
                set("tattoo_long", "上古魔獸赤蛇的紋樣");
                set("can_tattoo", ({ "臀部", "左臂", "右臂" }));
                set("tattoo_type", ({ "身法" }));
                set("tattoo_dex", 2);
        }
}