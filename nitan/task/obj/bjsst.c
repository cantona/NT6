#include <ansi.h>
inherit TASK;
void create()
{
    set_name(WHT"白金絲手套"NOR, ({ "shou tao", "shoutao" }) ); 
    set_weight(1);
    if( clonep() )
       destruct(this_object());
    else {
       set("unit", "雙"); 
       set("material", "steel");
       set("long", "這是一雙白金絲手套，手套乃質地輕薄柔軟，以極細極韌的白金絲織成。\n"); 
    }
    set("owner", "小龍女"); 
    setup();
}
