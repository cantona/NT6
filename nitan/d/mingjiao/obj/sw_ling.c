#include <ansi.h>
inherit ITEM;
void create()
{
    set_name("守衛書", ({ "shouwei shu", "shu" }) );
       set_weight(1000);
       if( clonep() )
               set_default_object(__FILE__);
       else {
               set("unit", "片");
                set("long", "這是一片用竹片所制的令牌，是明教守衛弟子的身份証明。\n");
               set("value", 20);
               set("material", "bamboo");          
       }
       setup();
}