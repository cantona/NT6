// xiangke.c

inherit NPC;
void create()
{
        set_name("香客", ({ "xiang ke", "ke" }) );
        set("gender", (random(2)? "女性":"男性") );
        set("age", random(40)+10);
        set("long", "一個上山遊玩的香客。\n");
        set("combat_exp", 5+random(5000));
        set("chat_chance", 70);
        set("chat_msg", ({
                (: random_move :),
                "香客指著周圍的景色嘆道：真美呀．．\n",
                "香客道：不愧為一座名山．．，還美過五岳呀！\n",
                "香客對你說道：你也是來遊山的？\n",
                "香客對你說道：你看這兒多美呀！\n",
                "香客對你說道：我真的被這兒陶醉了！\n",
        }) );

        set("attitude", "friendly");
        setup();
        carry_object(CLOTH_DIR"cloth")->wear();
}
