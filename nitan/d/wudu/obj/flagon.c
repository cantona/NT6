// flagon.c  酒壺

inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name("酒壺", ({"jiu hu", "hu", "flagon"}));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一個用來裝燒酒的大酒壺。\n");
                set("unit", "個");
                set("value", 100);
                set("max_liquid", 15);
        }

        set("liquid", ([
                "type": "alcohol",
                "name": "燒酒",
                "remaining": 15,
                "drunk_apply": 3,
                "slumber_effect": 100,
        ]));
}