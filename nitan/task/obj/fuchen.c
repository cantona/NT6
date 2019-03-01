#include <ansi.h>
inherit TASK;
void create()
{
    set_name(HIW"塵拂" NOR, ({ "chenfu" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "支");
            set("material", "paper");
            set("long", "一支普通的塵拂\n");
          }
    set("owner", "滅絕師太");
    setup();
}
