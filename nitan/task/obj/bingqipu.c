#include <ansi.h>
inherit TASK;
void create()
{
    set_name( HIG "兵器譜" NOR, ({ "bingqipu" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "記載各種兵器的一本奇書，不過你覺得它的封面也太厚了，厚的不象話。\n");
          }
    set("owner", "史鬆");
    setup();
}
