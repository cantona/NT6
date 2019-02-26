#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(NOR + WHT "顓頊圖騰" NOR, ({ "zhuanxu tu", "zhuanxu", "tu" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一張古舊的圖片，上面繪着些紋樣。");
                set("unit", "張");
                set("value", 4000);
                set("material", "paper");
                set("tattoo_long", "上古魔神顓頊的紋樣");
                set("can_tattoo", ({ "臀部", "左臂", "右臂" }));
                set("tattoo_type", ({ "膂力" }));
                set("tattoo_str", 2);
        }
}