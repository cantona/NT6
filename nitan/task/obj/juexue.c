#include <ansi.h> 
inherit TASK; 
void create()  
{
    set_name(MAG"武林絕學"NOR, ({ "wulin juexue" }) );  
    set_weight(10);  
        set_weight(10);  
         if( clonep() )  
                 destruct(this_object());  
   else {  
             set("unit", "本");  
             set("material", "book");
             set("long", "一本武林絕學。\n");  
      } 
      set("owner", "北醜");  
      setup(); 
}
