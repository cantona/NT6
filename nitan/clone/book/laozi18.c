// laozi18.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name( "道德經「第十八章」", ({ "jing", "daode jing" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
                        CYN "\n"
                        "\n\t\t\t第十八章\n\n"
                        "\t大道廢，有仁義；智慧出，有大偽；六親不和，有孝慈；國家昏\n"
                        "亂，有忠臣。\n"
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