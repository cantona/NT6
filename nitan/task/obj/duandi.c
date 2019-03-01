#include <ansi.h>
inherit TASK;
void create()
{
    set_name(WHT"白玉短笛"NOR, ({ "duan di", "di",}));
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "只");
            set("material", "stone");
            set("long", WHT"這玉笛短得出奇，只不來七寸來長、通體潔白，晶瑩可愛。\n" NOR);
          }
    set("owner", "採花子");
    setup();
}
