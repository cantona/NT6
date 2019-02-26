#include <ansi.h> 
inherit TASK; 
void create() 
{ 
        set_name( HIB "家傳匕首" NOR, ({ "bishou" }) ); 
        set_weight(20); 
        if( clonep() ) 
                destruct(this_object()); 
        else { 
                set("unit", "把"); 
                set("material", "iron"); 
                set("long", "這是一把短小鋒利的匕首，匕首柄上刻着一個”康“字，令人難以捉摸。\n"); 
        } 
        set("owner", "楊過"); 
        setup(); 
} 
