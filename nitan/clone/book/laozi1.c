// laozi1.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name( "道德經「第一章」", ({ "jing", "daode jing" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
                        CYN
                        "\n\t\t\t第一章\n\n"
                        "\n\t道可道，非常道。名可名，非常名。\n"
                        "\t無名天地之始；有名萬物之母。\n"
                        "\t故常無，欲以觀其妙；常有，欲以觀其徼。\n"
                        "\t此兩者，同出而異名，同謂之玄。玄之又玄，眾妙之門。\n\n"
                        NOR
                );
                set("value", 500);
                set("material", "paper");
                set("skill", ([
                        "name"        : "taoism",
                        "exp_required":        0,
                        "jing_cost"   : 10,
                        "difficulty"  : 15,
                        "max_skill"   : 29,
                ]) );
        }
}