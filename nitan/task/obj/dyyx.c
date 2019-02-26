#include <ansi.h>
inherit TASK;
void create()
{
    set_name( HIW "大燕玉璽" NOR, ({ "dayan yuxi", "yuxi" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "個");
            set("material", "stone");
            set("long", "一個玉璽，上面刻着大燕國號，看起來有些年代了。\n");
          }
    set("owner", "慕容博");
    setup();
}
