#include <ansi.h>
inherit TASK;
void create()
{
    set_name("烤鴨秘方", ({ "kaoya mifang", "mifang" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "一本這是北京最著名的全聚得程老板的烤鴨秘方。\n");
          }
    set("owner", "程老板");
    setup();
}
