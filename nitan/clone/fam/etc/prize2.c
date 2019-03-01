#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "□□士□章" NOR, ({ "chivalry medal", "chivalry", "medal" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "英□女王□□的□章，似乎可以□□好□□。\n" NOR);
                set("unit", "枚");
                set("value", 500000);
        }
        setup();
}