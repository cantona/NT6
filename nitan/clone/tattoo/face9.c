#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(NOR + WHT "慧眼圖騰" NOR, ({ "huiyan tu", "huiyan", "tu" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一張古舊的圖片，上面繪着些紋樣。");
                set("unit", "張");
                set("value", 1500);
                set("material", "paper");
                set("tattoo_long", "一隻血紅色的眼睛");
                set("can_tattoo", ({ "臉部", "臀部", "左臂", "右臂" }));
                set("tattoo_type", ({ "悟性" }));
                set("tattoo_int", 1);
        }
}