// shagu.c

inherit NPC;

void create()
{
        set_name("傻姑", ({"sha gu","shagu"}) );
        set("gender", "女性" );
        set("age", 21);
        set("long", "這是一個傻乎乎的小姑娘。\n");

        set("combat_exp", 150000);
        set("shen", 0);
        set("shen_type", 0);
        set("str", 32);
        set("dex", 18);
        set("con", 18);
        set("int", 10);
        set("max_qi", 900);
        set("max_jing", 720);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 20);

        set_skill("force", 60);
        set_skill("bibo-shengong", 60);
        set_skill("dodge", 60);
        set_skill("anying-fuxiang", 65);
        set_skill("parry", 60);
        set_skill("strike", 80);
        set_skill("luoying-shenzhang", 80);
        set_skill("qimen-wuxing", 30);

        map_skill("force", "bibo-shengong");
        map_skill("dodge", "anying-fuxiang");
        map_skill("strike", "luoying-shenzhang");
        map_skill("parry", "luoying-shenzhang");
        prepare_skill("strike", "luoying-shenzhang");

        set("rank_info/respect", "小姑娘");
        set("inquiry", ([
                "name": "他們都叫我做傻姑。",
                "rumors": "楊兄弟打了姑姑一掌，楊兄弟就死了。",
                "here": "這裏是牛家村。",
                "姑姑": "那個傻小子叫她做蓉兒。",
                "師公": "師公教我打拳玩。",
        ]) );
        setup();
        set("chat_chance", 10);
        set("chat_msg", ({
        "傻姑唱道：搖搖搖，搖到外婆橋，外婆叫我好寶寶....\n",
        "傻姑唸叨説：師公説道，左三掌，右三叉，壞人打我就打他。\n",
        "傻姑忽然指着你的鼻子哈哈大笑，你覺得莫名其妙。\n",
        "傻姑喊道：楊家兄弟，不是我害的你，你可別來找我。\n",
        "傻姑靠在牆角，發出了陣陣的鼾聲。\n",
        }) );
        carry_object("/clone/misc/cloth")->wear();
}

int accept_object(object who, object ob)
{
        object money;

        if (ob->id("zhangfa tujie")) 
        {
                if( query_temp("shagu_silver", who)){
                        tell_object(who, "傻姑接過圖解，倒着看了半天，不明所以，大怒之下，將圖解撕得稀爛！\n");
                        destruct(ob);
                        return notify_fail("");
                }
                else {
                        if (query_temp("silver_give")) {
                                tell_object(who, "傻姑接過圖解，倒着看了半天，不明所以，只好又還了給你。\n");
                                return notify_fail("");
                        }
                        else {
                                tell_object(who, "傻姑接過圖解，倒着看了半天，不明所以，只好又還了給你。\n");
                                tell_object(who, "傻姑説道：還不如我這個亮晶晶好玩呢！你看看。\n");
                                tell_object(who, "傻姑給你一些銀子。\n");
                                money = new("/clone/money/silver.c");
                                money->set_amount(15);
                                money->move(who);
                                set_temp("shagu_silver", 1, who);
                                set_temp("silver_give", 1);
                                return notify_fail("");
                        }
                }
        }
        return 0;
}
