// yunvjing1.c 玉女心經上

#include <ansi.h>
inherit ITEM;
inherit F_UNIQUE;

void create()
{
        set_name(HIM "玉女心經上冊" NOR, ({ "jing1", }));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
            set("unit", "本");
            set("long", "這是一本寫在薄絹上的書。封面上寫著 玉女心經「上」。\n");
                set("value", 0);
                set("material", "silk");
                set("skill", ([
                        "name":       "yunv-xinfa",
	    	            "family_name" : "古墓派",
                        "exp_required" : 30000,
                        "jing_cost":  40,
                        "difficulty": 30,
                        "max_skill":  60
                ]) );
        }
}