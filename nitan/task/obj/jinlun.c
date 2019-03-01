#include <ansi.h> 
inherit TASK; 
void create() 
{ 
    set_name(HIY"金輪"NOR, ({ "jin lun" }) ); 
    set_weight(1); 
    if( clonep() ) 
            destruct(this_object()); 
    else { 
            set("unit", "把"); 
            set("material", "stone"); 
            set("long", "金輪法王的隨身兵器。\n"); 
    } 
    set("owner", "金輪法王"); 
    setup();  
}
