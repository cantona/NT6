#include <weapon.h>
#include <ansi.h>
inherit TASK;
void create()
{
        set_name(MAG"閹刀"NOR, ({ "yan dao", "dao" }) );
        set_weight(4000);
        if( clonep() )
            destruct(this_object());
        else {
                set("unit", "柄");
                set("jungle",1);
                set("material", "iron");
                set("long", "這是一把專門閹割太監的閹刀。\n");
                set("wield_msg", "$N抽出一把黑油油的$n握在手中。\n");
                set("unequip_msg", "$N將手中的$n插入腰間。\n");
        }
        set("owner", "海公公");
        setup();
} 
