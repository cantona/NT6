#include <ansi.h>
inherit TASK;
void create()
{
    set_name(HIW"狂生曲譜"NOR, ({ "ksqupu" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "一本狂生曲曲譜。\n");
          }
    set("owner", "黃藥師");
    setup();
}
