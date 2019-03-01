#include <ansi.h>
inherit TASK;
void create()
{
    set_name( CYN "帳本" NOR, ({ "zhang ben" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "一本厚厚的賬本，裡面密密麻麻的記錄著一大堆帳目。\n");
          }
    set("owner", "楊永福");
    setup();
}
