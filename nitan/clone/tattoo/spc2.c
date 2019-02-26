#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(NOR + WHT "鳳舞九天圖" NOR, ({ "fengwu tu", "fengwu", "tu" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一張古舊的圖片，上面繪着些紋樣。");
                set("unit", "張");
                set("value", 16500);
                set("material", "paper");
                set("tattoo_long", "一隻浴火鳳凰盤旋在雲間，令人稱奇");
                set("can_tattoo", ({ "胸口", "後背", }));
                set("tattoo_type", ({ "悟性" }));
                set("tattoo_int", 4);
                set("tattoo_special", "potential");
                set("tattoo_spcname", "乾坤無量");
        }
}