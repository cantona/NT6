// wineskin.c  酒袋

inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name("酒壺", ({"jiuhu", "hu"}));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一個用來裝酒的酒壺，大概裝得八、九兩的酒。\n");
                set("unit", "個");
                set("value", 20);
                set("max_liquid", 15);
        }
          set("liquid",([
                "type": "alcohol",
                "name": "燒刀子",
                "remaining": 15,
                "drunk_supply": 15,
        ]));
}

