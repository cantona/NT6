#include <ansi.h>
inherit ITEM;
void create()
{
       set_name("鐵燄令", ({ "tieyan ling", "ling" }) );
       set_weight(1000);
       if( clonep() )
               set_default_object(__FILE__);
       else {
               set("unit", "片");
               set("long", "這是一片用鐵令牌，成火燄形狀。\n");
               set("value", 20);
               set("no_drop",1);
               set("no_get",1);
               set("no_steal",1);
               set("material", "iron");          
       }
       setup();
}
