// This program is a part of NT MudLIB 
 
#include <ansi.h>
#include <weapon.h>
inherit HAMMER;
 
void create()
{
        set_name(HIY "神" HIW "之" HIM "祝福" NOR HIC "鐵錘" NOR, ({ "zhufu hammer", "hammer", "chui" }) );
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", HIY "這便是神之祝福鐵錘。\n" NOR);
                set("value", 3000); 
                set("no_sell", "這樣東西不能賣。\n");
                set("rigidity",8000);   
                set("material", "tian jing");
                set("no_pawn", 1);
        }
        
        set("quality_level", 2); 
        init_hammer(500);
        setup();
}



