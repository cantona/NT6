// laozi8.c
// by Marz

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name( "道德經「第八章」", ({ "jing", "daode jing" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
                        CYN "\n"
                        "\n\t\t\t第八章\n\n"
                        "\t上善若水。水善利萬物而不爭，處眾人之所惡，故幾于道。\n"
                        "\t居善地，心善淵，與善仁，言善信，政善治，事善能，動善時。\n"
                        "夫唯不爭，故無尤。\n"
                        "\n"NOR
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