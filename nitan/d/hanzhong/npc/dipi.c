// dipi.c

inherit NPC;

void create()
{
        set_name("地痞", ({"dipi"}) );
        set("gender", "男性" );
        set("age", 20);
        set("long", "這是一個喝的醉醺醺的地痞。\n");

        set_temp("apply/attack", 15);
        set_temp("apply/defense", 15);
        set("combat_exp", 750);
        set("shen_type", -1);
        set("str", 25);
        set("dex", 20);
        set("con", 18);
        set("int", 15);
        set("attitude","heroism");
        setup();
        set("chat_chance", 5);
        set("chat_msg", ({
"地痞迷迷糊糊的喊道：哥倆兒好啊，五魁手啊～～～\n",
"地痞靠在牆角，發出了陣陣的鼾聲。\n",
        }) );
        carry_object(CLOTH_DIR"cloth")->wear();
        add_money("silver",8);
}
