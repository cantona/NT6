// xu.c

#include <ansi.h>;
inherit NPC;

string *quest_msg1 = ({
        "徐長老説道：久仰少俠大名，今日一見果然名不虛傳，失敬失敬！\n",
        "這次的武林大會，唉，我該從何説起呢，家門不幸啊！\n",
        "其實這本是我們丐幫自己的事情，我也不相信這這殺父、殺母、殺師的惡行，會是喬峯所為，可是……\n",
        "徐驚雷看着你迷惑的表情，繼續説道。\n",
        "現在鐵證如山，喬峯這番邦賊子，在契丹人身份被揭穿，叛出丐幫之後，殺害了自己的義父義母，\n"
        "又殺害了自己的授業恩師玄苦大師，犯下了彌天大罪！他妄圖掩飾自己的契丹人身份，誰料卻越抹越黑！\n",
        "雖然喬峯這廝為丐幫也曾立下汗馬功勞，但國家大義所在，丐幫也難以迴護於他。\n",
        "遊氏兄弟和薛神醫召開武林大會，就是為了聚眾討伐喬峯。羣龍無首，大家都希望可以請到江湖上德高\n"
        "望重的前輩或者是朝廷的人來做大家的領袖，畢竟這已經不是普通的家恨，還有國仇了……\n",
        "我們商議之後，覺得大理鎮南王段正淳就是最合適的人選。我知道你和他很是熟悉，希望你能出面，請他來主持這次武林大會。\n",
});

string *quest_msg2 = ({
        "徐長老説道：想不到鎮南王竟置民族大義於不顧，真是令人痛心啊。\n",
        "這也難怪，鎮南王是大理人，不會了解契丹人對大宋造成了多麼深重的傷害。\n",
        "喬峯殺父、殺母、殺師三件大罪，我雖沒有親眼見到，但少林寺守律僧的話，難道會是假的？\n",
        "罷了，罷了，既然段王爺説的這麼明白了，我們也不好強人所難。\n",
        "説到少林寺，再麻煩你去一趟少林寺，邀請少林寺玄慈方丈參加聚賢莊大會吧。\n",
        "我知道，玄慈方丈心裏有一些難解的結，他是不會來參加武林大會的，但如果能請到玄難大師、玄寂\n"
        "大師來聚賢莊，也能讓天下英雄有個主心骨了。畢竟，天下武功出少林嘛。\n",
});

int ask_juxianzhuang();
int do_report();

void create()
{
        set_name("徐長老", ({"xu zhanglao", "xu", "zhanglao"}));
        set("gender", "男性");
        set("age", 85);
        set("long", "白鬚飄動，穿着一身補丁累累的鶉衣，是個年紀極高的老丐。\n");
        set("title", "丐幫九袋長老");
        set("attitude", "peaceful");
        set("class", "beggar");
         set("beggarlvl", 9);
        set("no_get", "1");

        set("str", 24);
        set("int", 20);
        set("con", 24);
        set("dex", 20);

        set("qi", 900000);
        set("max_qi", 900000);
        set("jing", 100000);
        set("max_jing", 10000);
        set("neili", 1500000);
        set("max_neili", 1500000);
        set("jiali", 1000);

        set("combat_exp", 100000000);
        set("score", 20000);

        set_skill("force", 950);            // 基本內功
        set_skill("huntian-qigong", 900);   // 混天氣功
        set_skill("hand", 900);             // 基本手法
        set_skill("suohou-hand", 850);      // 鎖喉擒拿手
        set_skill("staff", 900);            // 基本杖法
        set_skill("fengmo-zhang", 850);     // 瘋魔杖法
        set_skill("dodge", 900);            // 基本躲閃
        set_skill("xiaoyaoyou", 950);       // 逍遙遊
        set_skill("parry", 850);            // 基本招架
        set_skill("staff", 900);            // 基本棍杖
        set_skill("strike",850);  // 基本掌法
        set_skill("lianhua-zhang",850); // 蓮花掌
        set_skill("xianglong-zhang",850);

        map_skill("strike","lianhua-zhang");
        prepare_skill("strike","lianhua-zhang");

        map_skill("force", "huntian-qigong");
        map_skill("staff", "fengmo-zhang");
        map_skill("parry", "fengmo-zhang");
        map_skill("hand", "suohou-hand");
        map_skill("dodge", "xiaoyaoyou");
        prepare_skill("hand", "suohou-hand");

        set("inquiry", ([
                "英雄貼": (: ask_juxianzhuang :),
                "武林大會": (: ask_juxianzhuang :),
        ]) );

        //set("party/party_name", HIC"丐幫"NOR);
        //set("party/rank", RED"九袋長老"NOR);
        //set("party/level", 9);
        create_family("丐幫", 18, "長老");

        setup();

        carry_object("/clone/cloth/cloth")->wear();
        carry_object(WEAPON_DIR"gangzhang")->wield();
}

void init()
{
        object ob;
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() &&
            ob->query_temp("juxianzhuang_step") == 5 ) {
                add_action("do_report", "report");
        }
}

int ask_juxianzhuang()
{
        object me = this_player();

        if( (int)me->query_temp("juxianzhuang_step") != 1 )
        {
                tell_object(me, "徐長老看了看你，又搖了搖頭。\n");
                return 1;
        }

        call_out("quest_stage", 0, me, 0);
        return 1;
}

void quest_stage(object ob, int stage)
{

        if (! ob || ! present(ob)) return;

        tell_object(ob, HIW + quest_msg1[stage] + NOR);
        if (++stage < sizeof(quest_msg1))
        {
                call_out( "quest_stage", 1, ob, stage );
                return;
        }
        ob->set_temp("juxianzhuang_step", 2);
}

void quest_stage2(object ob, int stage)
{

        if (! ob || ! present(ob)) return;

        tell_object(ob, HIW + quest_msg2[stage] + NOR);
        if (++stage < sizeof(quest_msg2))
        {
                call_out( "quest_stage2", 1, ob, stage );
                return;
        }
        ob->set_temp("juxianzhuang_step", 4);
}

int do_report()
{
        object me, ob;

        me = this_player();
        ob = this_object();

        if( (int)me->query_temp("juxianzhuang_step") != 5 )
                return 0;

        message_vision("$n詳細地向$N彙報了去少林寺請玄慈方丈的經過。\n", ob, me);

        command("say 既然玄難大師和玄寂大師兩位高僧要來聚賢莊，那天下英雄就不會羣龍無首了。\n");
        command("say 多謝你了，你近日如果無事，可以和聚賢莊內的英雄們結交一下。\n");
        me->set_temp("juxianzhuang_step", 6);
        return 1;
}

int accept_object(object me, object ob)
{
        if( ob->query("id") != "letter" )
                return 0;

        if( !ob->query("send_to")
        ||  ob->query("send_to") != query("id")
        ||  !ob->query("send_from")
        ||  ob->query("send_from") != me->query("id") )
        {
                return 0;
        }

        if( (int)me->query_temp("juxianzhuang_step") != 3 )
                return 0;

        call_out("quest_stage2", 0, me, 0);
        destruct(ob);
        return 1;
}
