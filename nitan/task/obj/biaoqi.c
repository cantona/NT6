#include <ansi.h>
inherit TASK;
void create()
{
    set_name(HIR"鏢旗"NOR, ({ "biaoqi" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "張");
            set("material", "paper");
            set("long", "一張林家鏢局的鏢旗\n");
          }
    set("owner", "林震南");
    setup();
}
