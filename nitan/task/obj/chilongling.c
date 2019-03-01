#include <ansi.h> 
inherit TASK; 
void create() 
{ 
        set_name( RED "赤龍令" NOR, ({ "chilong ling" }) ); 
        set_weight(50); 
        if( clonep() ) 
                destruct(this_object()); 
        else { 
                set("unit", "把"); 
                set("material", "iron"); 
                set("long", "這就是名震江湖的赤龍令，令牌隱隱透出血紅色的光芒，看上去煞是嚇人。\n"); 
        } 
        set("owner", "無根道長"); 
        setup(); 
} 
