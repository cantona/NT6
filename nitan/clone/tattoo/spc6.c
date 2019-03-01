#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(NOR + WHT "千手觀音圖" NOR, ({ "guanyin tu", "guanyin", "tu" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一張古舊的圖片，上面繪著些紋樣。");
                set("unit", "張");
                set("value", 16500);
                set("material", "paper");
                set("tattoo_long", "大慈大悲觀世音菩薩，坐八寶蓮花，千支手姿態各異");
                set("can_tattoo", ({ "胸口", "後背", }));
                set("tattoo_type", ({ "悟性" }));
                set("tattoo_int", 4);
                set("tattoo_special", "clever");
                set("tattoo_spcname", "天賦聰穎");
        }
}