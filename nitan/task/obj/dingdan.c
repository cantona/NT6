inherit TASK;
#include <ansi.h>
void create()
{
    set_name( HIM"客户定單" NOR, ({ "dingdan" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "張");
            set("material", "paper");
            set("long", "一張詳細的定單，記載着麗春院的預定情況。\n");
        }
    set("owner", "韋春芳");
    setup(); 
}
