// yangdt.c

inherit ITEM;
void create()
{
        set_name("陽頂天遺骨", ({ "corpse" }) );
        set_weight(30000);
        set_max_encumbrance(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "具" );
                set("long", "這是一具明教前任教主陽頂的遺骨。他英雄一世，現在是什麼都不知道了。\n");
                set("no_get", "就讓他在這裏好好的安息吧。\n");
        }
        setup();
}
