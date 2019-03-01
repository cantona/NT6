#include <ansi.h>
inherit TASK;
void create()
{
    set_name(HIW"大刀"NOR, ({ "da dao" }) );
    set_weight(10);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "柄");
            set("material", "iron");
            set("long", "一柄普通大刀，除了刀身比一般的略厚外，沒有什麼特別的了。\n");
          }
    set("owner", "茅十八");
    setup();
}
