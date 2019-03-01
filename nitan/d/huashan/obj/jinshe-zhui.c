// jinshe-zhui.c
 
#include <weapon.h>
#include <ansi.h>
 
inherit THROWING;
 
void create()
{
        set_name(YEL"金蛇錐"NOR, ({ "jinshe zhui", "zhui" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", 
"金蛇錐是黃金所鑄，燦爛生光。長約二寸八分，打成昂首吐舌的蛇
形，蛇舌尖端分成雙叉，每一叉都是一個倒刺。\n");
                set("unit", "把");
                set("value", 0);
                set("base_unit", "枚");
                set("base_weight", 10);
                set("base_value", 0);
        }
        set_amount(15);
        init_throwing(35);
        setup();
}
