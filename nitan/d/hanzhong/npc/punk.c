// punk.c

inherit NPC;

void create()
{
        set_name("小流氓", ({"punk"}) );
        set("gender", "男性" );
        set("age", 18);
        set("long", "這是一個遊手好閒的小流氓。\n");

        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);
        set("combat_exp", 500);
//      set("shen", -100);
        set("shen_type", -1);
        set("str", 25);
        set("dex", 20);
        set("con", 18);
        set("int", 15);
        set("attitude","heroism");
        setup();
        set("chat_chance", 10);
        set("chat_msg", ({
"流氓罵罵咧咧的説道：這真他媽的邪唬，老子手裏一對天牌，王\n"
"小二這雜種居然就摸出一對至尊來。\n",
"流氓靠着牆角打起瞌睡來了，睡夢中也不知想到了什麼，嘴裏哼\n"
"哼道：我看見你哪雪白的大腿，我就起～了～壞～心～嘍。\n",
"流氓摸了摸自己的口袋，歎了口氣説道：唉，錢都讓王小二騙去\n"
"了，不能去找翠花了。\n",
"流氓嘴角露出一絲邪笑，説道：翠花這娘兒們真夠勁兒，真她奶\n"
"奶的夠～勁～兒!\n",
        }) );
        carry_object(CLOTH_DIR"cloth")->wear();
        add_money("silver", 5);
}
