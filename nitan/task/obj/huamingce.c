#include <ansi.h>
inherit TASK;
void create()
{
    set_name( MAG "花名冊" NOR, ({ "hua mingce", "mingce" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "一本紅花會的花名冊，上面記錄了所有紅花會好漢的名單。\n這個東西要是被官府得到了可不得了。\n");
          }
    set("owner", "陳家洛");
    setup();
}
