#include <ansi.h> 
inherit TASK; 
void create() 
{ 
        set_name( HIB "鬼刀" NOR, ({ "gui dao" }) ); 
        set_weight(40); 
        if( clonep() ) 
                destruct(this_object()); 
        else { 
                set("unit", "把"); 
                set("material", "iron"); 
                set("long", "這是一把詭異的彎刀，刀身細長，刀背寬厚，刀柄怪異。\n"); 
        } 
        set("owner", "王五"); 
        setup(); 
} 
