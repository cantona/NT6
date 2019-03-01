// nverhong.c 女兒紅

inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name("女兒紅", ({"nver hong", "wine"}));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一壇上好的女兒紅,醇香誘人.\n");
                set("unit", "壇");
                set("value", 500);
                set("max_liquid", 15);
        }

        // because a container can contain different liquid
        // we set it to contain wine at the beginning
        set("liquid", ([
                "type": "alcohol",
                "name" : "女兒紅酒",
                "remaining": 3,
                "drunk_supply": 6,
        ]));
}
