// item: /d/xingxiu/npc/obj/hu.c
// Jay 3/17/96

inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name("馬奶酒壺", ({"hu", "bottle"}));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一個用來裝馬奶酒的大酒壺，大概裝得八、九升的酒。\n");
                set("unit", "只");
                set("value", 100);
                set("max_liquid", 15);
        }
        set("liquid", ([
                "type": "alcohol",
                "name": "馬奶酒",
                "remaining": 15,
                "drunk_supply": 6,
        ]));
}