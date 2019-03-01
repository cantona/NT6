#include <ansi.h>
inherit TASK;
void create()
{
    set_name("皇帝密旨", ({ "mizhao" }) );
    set_weight(10);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "張");
            set("material", "paper");
            set("long", "一張折的很好的紙條，紙身上好像還蓋了大印。\n");
          }
    set("owner", "李可秀");
    setup();
}
