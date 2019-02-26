// laozi13.c

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name( "道德經「第十三章」", ({ "jing", "daode jing" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
                        CYN "\n"
                        "\n\t\t\t第十三章\n\n"
                        "\t寵辱若驚，貴大患若身。\n"
                        "\t何謂寵辱若驚？寵為下，得之若驚，失之若驚，是謂寵辱若驚。\n"
                        "\t何謂貴大患若身？吾所以有大患者，為吾有身，及吾無身，吾有\n"
                        "何患？\n"
                        "\t故貴以身為天下，若可寄天下；愛以身為天下，若可託天下。\n"
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