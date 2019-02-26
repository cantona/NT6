
#include <armor.h>
#include <ansi.h>

inherit MEDAL2;

void create()
{
        set_name(HIY "轉世勛章（乾坤）" NOR, ({ "qiankun xunzhang", "qiankun", "xunzhang" }));
        set("long", HIY "轉世後獲得的勛章，上繪乾坤圖，閃閃發亮，甚是精緻。\n" NOR);
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("value", 200000);
                set("material", "bronze");
                set("armor_prop/damage", 500);
                set("armor_prop/con", 10);
                set("armor_prop/scborn", 1);
                set("armor_prop/force", "apply_armor() * 3");
                set("special/desc", HIR "用莫邪聖符升級後可鑲嵌提高有效內功等級。" NOR); 
                set("limit", ([
                        "scborn" : 1, 
                ]));
        }
        setup();
}        

int query_autoload()
{
        return 1;
}