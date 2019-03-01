
#include <armor.h>
#include <ansi.h>

inherit MEDAL;

void create()
{
        set_name(HIM "炎黃紀念勛章" NOR, ({ "jinian medal" }));
        set("long", HIM "這是一枚炎黃官方贈送的紀念勛章，贈予那些對炎黃發展做出貢獻的玩家。\n" NOR);
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/damage", 100);
                set("armor_prop/con", 3);
                set("armor_prop/dex", 3);
                set("armor_prop/str", 3);
                set("armor_prop/int", 3);

        }
        setup();
}        

int query_autoload()
{
        return 1;
}