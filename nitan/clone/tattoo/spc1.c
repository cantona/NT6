#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(NOR + WHT "九宵紋□圖" NOR, ({ "wenlong tu", "wenlong", "tu" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一張古舊的圖片，上面繪著些紋樣。");
                set("unit", "張");
                set("value", 16500);
                set("material", "paper");
                set("tattoo_long", "九條蛟□，相互盤繞纏縛，栩栩如生");
                set("can_tattoo", ({ "胸口", "後背", }));
                set("tattoo_type", ({ "膂力" }));
                set("tattoo_str", 4);
                set("tattoo_special", "power");
                set("tattoo_spcname", "天神降世");
        }
}