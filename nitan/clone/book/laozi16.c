// laozi16.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name( "道德經「第十六章」", ({ "jing", "daode jing" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
                        CYN "\n"
                        "\n\t\t\t第十六\n\n"
                        "\t致虛極，守靜篤。\n"
                        "\t萬物並作，吾以觀復。\n"
                        "\t夫物芸芸，各復歸其根。歸根曰靜，靜曰覆命。覆命曰常，知常\n"
                        "曰明。不知常，妄作兇。\n"
                        "\t知常容，容乃公，公乃全，全乃天，天乃道，道乃久，沒身不殆。\n"
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