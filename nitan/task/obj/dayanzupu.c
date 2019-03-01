#include <ansi.h>
inherit TASK;
void create()
{
    set_name(YEL"大燕族譜"NOR, ({ "dayan zupu", "zu pu" }) );
    set_weight(10);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "一本很老舊的書，上面寫著“大燕族譜”。\n");
          }
    set("owner", "慕容復");
    setup();
}
