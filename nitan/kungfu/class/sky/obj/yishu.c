#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(WHT "嶽山遺書" NOR, ({ "yishu", "shu", "book" }));
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這便是當年「霸刀」嶽山臨死前的遺書，上面記載了他對刀法的體會。\n");
                set("value", 100);
                set("material", "paper");
                set("skill", ([
                        "name": "badao-daofa",        // name of the skill
                        "exp_required": 500000,      // minimum combat experience required
                        "jing_cost":    80,     // jing cost every time study this
                        "difficulty":   80,     // the base int to learn this skill
                        "max_skill":    150      // the maximum level you can learn
                ]) );
        }
}

