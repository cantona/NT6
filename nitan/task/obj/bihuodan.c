#include <ansi.h>  
inherit TASK; 
void create()  
{
   set_name(HIR"碧火彈" NOR, ({ "bihuo dan" }) );  
   set_weight(10); 
   if( clonep() ) 
           destruct(this_object());  
   else { 
        set("unit", "顆");  
        set("material", "stone");
        set("long", "看起這麼陰險的東西，肯定是星宿摘星子的碧火彈了。。。\n");  
         }
         set("owner", "摘星子");  
         setup();
}
