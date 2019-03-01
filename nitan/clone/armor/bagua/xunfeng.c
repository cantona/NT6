
#include <ansi.h>
#include <armor.h>

inherit SURCOAT;

void create()
{
        set_name(HIY "八卦巽風翼" NOR, ({ "xunfeng yi", "xunfeng", "yi" }));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY"炎黃風雨十年紀念套裝之：八卦巽風翼\n" NOR);
                set("unit", "件");
                set("value", 100);
                set("armor_prop/huibi", 1000);
                set("armor_prop/T_bagua", 1); // 套裝計數標志
        }
        setup();
}

int query_autoload()
{
        return 1;
}