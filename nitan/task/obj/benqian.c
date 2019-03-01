#include <ansi.h> 
inherit TASK; 
void create() 
{
    set_name(HIR"翻本的本錢"NOR, ({ "benqian" }) ); 
    set_weight(1); 
    if( clonep() ) 
            destruct(this_object()); 
    else { 
            set("unit", "張"); 
            set("material", "paper"); 
            set("long", "一張賭客翻本的本錢。\n"); 
          } 
          set("owner", "賭客"); 
          setup();
}
