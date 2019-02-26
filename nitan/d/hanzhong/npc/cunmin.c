// cunmin.c

inherit NPC;

void create()
{
        set_name("村民", ({ "cun min", "min" }) );
        set("gender", "男性" );
        set("age", 30);
        set("long", "一個魁梧的莊稼漢子。\n");
        set("attitude", "friendly");
        set("combat_exp", 500);
        set("shen", 100);
        set("shen_type", 1);
        set("str", 22);
        set("dex", 18);
        set("con", 18);
        set("int", 13);
        setup();
        set("chat_chance", 15);
        set("chat_msg", ({
"村民道：多虧全真教的道爺們，這山上咬莊稼的獾子全讓他們給趕跑了。\n",
"村民突然滿臉恍然的神色：今年的收成不錯，我得跟全真教的道爺們送點
兒去，請他們嚐嚐鮮。\n",
        }) );
        carry_object(CLOTH_DIR"cloth")->wear();
        add_money("coin",100);
}
