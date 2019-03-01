//Edited by fandog, 02/15/2000

inherit NPC;

void create()
{
        set_name("桃紅",({ "tao hong", "hong" }) );
        set("gender", "女性" );
        set("age", 25);
        set("long", 
"一位年輕女人，卻象是個丐婦。她蓬頭垢面，容色憔悴，衣襟上滿是污穢油膩。\n");
        set_temp("apply/defense", 5);
        set("combat_exp", 70);
        set("shen_type", 1);
        set("str", 14);
        set("per", 28);
        set("dex", 15);
        set("con", 16);
        set("int", 15);
        set("attitude", "friendly");
        set("chat_chance", 5);
        set("chat_msg", ({
                "桃紅垂淚道：我也不知道老爺為什麼忽然不喜歡我了。\n",
                "桃紅抹了抹眼淚，黯然道：那個湖南佬……那個姓狄的事，又不是我不好。\n",
                "桃紅喃喃道：老爺晚上見鬼，要砌牆，怎麼怪得我？又……又不是我瞎說。\n",
        }) );

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}
