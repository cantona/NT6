#include <ansi.h>
inherit TASK;
void create()
{
    set_name( CYN "衣樣" NOR, ({ "yi yang" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "件");
            set("material", "cloth");
            set("long", "一件用來做衣服的衣樣，上面還有一股淡淡的清香。\n");
          }
    set("owner", "曾柔");
    setup();
}
