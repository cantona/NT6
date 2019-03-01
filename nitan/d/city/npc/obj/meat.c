//meat.c
//By Dumbness@HUAXIA 2003-5-9 13:16

inherit ITEM;
inherit F_FOOD;
void create()
{
        set_name("烤肉", ({"kaorou", "rou", "fried meat", "meat" }) );
        set_weight(350);
        if( clonep() )
                set_default_object(__FILE__);
        else 
        {
                set("long", "一串烹飪好的香噴噴的烤肉，已經看不出是用什麼做的了，只聞到一股股的香氣撲鼻而來。\n");
                set("unit", "串");
                set("food_remaining", 10);
                set("food_supply", 50); 
                set("material", "bone");
        }
        setup();
}
