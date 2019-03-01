#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIW "長生決" NOR, ({ "changsheng jue", "book", "jue" }));
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這便是四大奇書之一的長生決，傳說可以修煉至高無上的武學。\n");
                set("value", 300);
                set("material", "paper");
                set("skill", ([
                        "name": "changsheng-jue",        // name of the skill
                        "exp_required": 100000,      // minimum combat experience required
                        "jing_cost":    50,     // jing cost every time study this
                        "difficulty":   50,     // the base int to learn this skill
                        "max_skill":    250      // the maximum level you can learn
                ]) );
        }
}

