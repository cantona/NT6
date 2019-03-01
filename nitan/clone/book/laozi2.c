// laozi2.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name( "道德經「第二章」", ({ "jing", "daode jing" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
                        CYN "\n"
                        "\n\t\t\t第二章\n\n"
                        "\t天下皆知美之為美，斯惡已。皆知善之為善，斯不善已。\n"
                        "\t有無相生，難易相成，長短相形，高下相盈，音聲相和，前後相\n"
                        "隨。恆也。\n"
                        "\t是以聖人處無為之事，行不言之教；萬物作而弗始，生而弗有，\n"
                        "為而弗恃，功成而不居。夫唯弗居，是以不去。\n"
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