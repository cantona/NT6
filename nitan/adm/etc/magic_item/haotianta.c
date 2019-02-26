// 上古十大神器之 昊天塔
// Create by Rcwiz for Hero.cn 2003/09

#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(HIM + "昊天塔" NOR, ({ "haotian ta", "haotian", "ta" }) );
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "個");
                set("long", HIM "這是一個擁有吸星換月之力的寶塔，不時地從中投射出\n"
                                "奇異的光芒。\n"                                
                                "當你打通十二重天達到天外天后，能借用該塔之力進入來世。\n" NOR);

        }
        setup();
}
