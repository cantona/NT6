#include <ansi.h>
inherit ITEM;
void create()
{
       set_name("巡邏令", ({ "xunluo ling", "ling" }) );
       set_weight(1000);
       if( clonep() )
               set_default_object(__FILE__);
       else {
               set("unit", "片");
               set("long", "這是一片用竹片所制的令牌，是明教巡邏弟子的身份證明。\n");
               set("value", 20);
               set("material", "bamboo");          
       }
       setup();
}