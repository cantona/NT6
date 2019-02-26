// zixia_book.c  紫霞祕芨
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(MAG"紫霞密芨"NOR, ({ "zixia_book", "book" }));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
//                set("no_drop",1);
                set("long",
HIM"天下武功，以練氣為正。浩然正氣，原為天授，惟常人不善
養之，反以性伐氣。武夫之患，在性暴、性驕、性酷、性賊。
暴則神擾而氣亂，驕則真離而氣浮，酷則喪仁而氣失，賊則
心狠而氣促。此四事者，皆是截氣之刀鋸。舍爾四性，返諸
柔善，制汝暴酷，養汝正氣，鳴天鼓，飲玉漿，蕩華池，叩
金樑，據而行之，當有小成。\n"NOR);
                set("value", 1000);
                set("material", "paper");
                set("skill", ([
                        "name":         "zixia-shengong",        // name of the skill
                        "family_name" : "華山派",
                        "exp_required": 50000,                // minimum combat experience required
                                                                // to learn this skill.
                        "jing_cost" :   30,
                        "difficulty":   30,                        // the base int to learn this skill
                                                                // modify is gin_cost's (difficulty - int)*5%
                        "max_skill":    99,                        // the maximum level you can learn
                        "min_skill":    0                        // the maximum level you can learn
                                                                // from this object.
                ]) );
        }
}
int query_autoload() { return 1; }
