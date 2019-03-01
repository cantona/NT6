#include <ansi.h>
inherit TASK;
void create()
{
    set_name(HIR"攝心訣"NOR, ({ "shexin jue" }) );
    set_weight(10);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "丐幫長老彭有敬的攝心訣，裡面記錄的無功據說可以控制別人的心智。\n");
          }
    set("owner", "彭有敬");
    setup();
}
