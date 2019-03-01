#include <ansi.h> 
inherit TASK; 
void create() 
{ 
   set_name(HIW"銀鉤" NOR, ({ "yin gou" }) ); 
   set_weight(10); 
   if( clonep() ) 
           destruct(this_object()); 
   else { 
        set("unit", "把"); 
        set("material", "stone"); 
        set("long", "武當七俠中，張翠山的銀鉤。。。\n"); 
         } 
        set("owner", "張翠山"); 
        setup(); 
}
