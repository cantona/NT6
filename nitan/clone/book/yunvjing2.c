// yunvjing2.c 玉女心經下

#include <ansi.h>
inherit ITEM;
inherit F_UNIQUE;

void create()
{
        set_name(HIM "玉女心經下冊" NOR, ({ "jing2", }));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一本寫在薄絹上的書。封面上寫着 玉女心經「下」。\n");
                set("value", 0);
                set("material", "silk");
                set("skill", ([
                        "name":       "yunv-xinfa",
                        "family_name" : "古墓派",
                        "exp_required" : 65000,
                        "jing_cost":  42,
                        "difficulty": 32,
                        "max_skill":  100
                ]) );
        }
}
