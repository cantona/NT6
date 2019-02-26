#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(NOR + WHT "托塔天王圖" NOR, ({ "tianwang tu", "tianwang", "tu" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一張古舊的圖片，上面繪着些紋樣。");
                set("unit", "張");
                set("value", 16500);
                set("material", "paper");
                set("tattoo_long", "托塔天王，站立於南天門之下，神威凜凜");
                set("can_tattoo", ({ "胸口", "後背", }));
                set("tattoo_type", ({ "膂力" }));
                set("tattoo_str", 4);
                set("tattoo_special", "ironskin");
                set("tattoo_spcname", "銅皮鐵骨");
        }
}