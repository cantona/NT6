// puercha.c

inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name("茶壺", ({"chahu", "hu", "bottle"}));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一個用來裝茶的大茶壺，大概裝得八、九杯的茶。\n");
                set("unit", "個");
                set("value", 150);
                set("max_liquid", 15);
        }

        // because a container can contain different liquid
        // we set it to contain wine at the beginning
        set("liquid", ([
                "type": "water",
                "name": "雲南普洱茶",
                "remaining": 15,
                "drunk_apply": 5,
        ]));
}