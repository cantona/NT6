inherit ITEM;
inherit F_FOOD;

void create()
{
     set_name("桃花糕", ({ "gao" }));
    set_weight(1000);
    if( clonep() )
            set_default_object(__FILE__);
    else {
          set("long", "這是一塊粉紅色的點心，做成了桃花狀，引人食慾大增。\n");
          set("unit", "塊");
          set("value", 50);
          set("food_remaining", 6);
          set("food_supply", 100);
     }
}
