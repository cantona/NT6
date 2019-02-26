#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(NOR + WHT "玄蛇圖騰" NOR, ({ "xuanshe tu", "xuanshe", "tu" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一張古舊的圖片，上面繪着些紋樣。");
                set("unit", "張");
                set("value", 9000);
                set("material", "paper");
                set("tattoo_long", "神獸玄蛇的紋樣");
                set("can_tattoo", ({ "胸口", "後背", "左臂", "右臂" }));
                set("tattoo_type", ({ "根骨", "悟性" }));
                set("tattoo_con", 2);
                set("tattoo_int", 1);
        }
}