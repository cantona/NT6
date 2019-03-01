#include <ansi.h> 
inherit TASK; 
void create()  
{ 
    set_name(HIB"聖火令"NOR, ({ "ling", "shenghuo ling" }) );  
    set_weight(1);
    if( clonep() ) 
            destruct(this_object());  
    else { 
          set("unit", "個");  
          set("material", "dagger"); 
            set("long", "明教丟失的聖火令牌。\n"); 
          } 
          set("owner", "接引使");
          setup();
} 
