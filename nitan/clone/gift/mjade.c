// mjade.c 神之翡翠

#include <ansi.h>
#include <armor.h>

inherit HEAD;

int is_enchase_ob(){ return 1; }

void create()
{
        set_name(HIG "神之翡翠" NOR, ({ "magic jade" }) );
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIG "一顆煥發著奇異的光彩的翡翠，"
                    "給人以不同尋常的感覺。\n" NOR);
                set("value", 200000);
                set("unit", "顆");
                set("can_be_enchased", 1);
                set("magic/type", "cold");
                set("magic/power", 15 + random(16));
                set("armor_prop/per", 8);
                set("no_identify", 1);
                set("wear_msg", HIC "$N" HIC "輕輕地把$n"
                    HIC "戴在頭上。\n" NOR);
                set("remove_msg", HIC "$N" HIC "輕輕地把$n"
                    HIC "從頭上摘了下來。\n" NOR);
        }
        setup();
}
