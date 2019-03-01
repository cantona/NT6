// longpao.c

#include <ansi.h>
#include <armor.h>
inherit CLOTH;

void create()
{
        set_name(HIR"大紅"NOR HIY"金邊"NOR HIR"滾龍袍"NOR, ({ "longpao" }));
        set("long", "這是一件嶄新大紅金邊滾龍袍，是新郎的專用禮服。\n");
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "件");
    set("armor_prop/armor", 100);
    set("male_only", 1);
        }
        setup();
}
