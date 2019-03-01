#include <ansi.h>
inherit TASK;
void create()
{
    set_name(CYN"可蘭經"NOR, ({ "kelan jing", "jing"}));
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "一本可蘭經，是伊斯蘭教信徒的必備之物。\n");
          }
    set("owner", "霍青桐");
    setup();
}
