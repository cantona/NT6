#include <ansi.h>
inherit TASK;
void create()
{
        set_name(HIG"方丈手諭"NOR,({ "shouyu" }) );
        set_weight(100);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "紙");
                set("material", "paper");
                set("long", "這是一張空白的方丈專用手諭箋。\n");
        }
        set("owner", "玄慈大師");
        setup();
}  
