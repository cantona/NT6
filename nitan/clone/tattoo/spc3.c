#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(NOR + WHT "萬佛朝聖圖" NOR, ({ "wanfo tu", "wanfo", "tu" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一張古舊的圖片，上面繪著些紋樣。");
                set("unit", "張");
                set("value", 16500);
                set("material", "paper");
                set("tattoo_long", "無數僧人朝拜佛祖，金光散布，神聖莊嚴");
                set("can_tattoo", ({ "胸口", "後背", }));
                set("tattoo_type", ({ "根骨" }));
                set("tattoo_con", 4);
                set("tattoo_special", "health");
                set("tattoo_spcname", "內斂乾坤");
        }
}