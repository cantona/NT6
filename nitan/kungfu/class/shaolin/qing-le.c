// Npc: /kungfu/class/shaolin/qing-le.c
// Date: YZC 96/01/19

inherit NPC;

string ask_me_1();
string ask_me_2();

nosave string *check_skill = ({
        "buddhism",
        "dodge",
        "shaolin-shenfa",
        "force",
        "parry",
});

void create()
{
        set_name("清樂比丘", ({
                "qingle biqiu",
                "qingle",
                "biqiu",
        }));
        set("long",
                "他是一位體格強健的壯年僧人，他身得虎背熊腰，全身似乎藴含\n"
                "着無窮勁力。他身穿一襲白布黑邊袈裟，似乎身懷武藝。\n"
        );


        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 30);
        set("shen_type", 1);
        set("str", 17);
        set("int", 24);
        set("con", 20);
        set("dex", 22);
        set("max_qi", 350);
        set("max_jing", 200);
        set("neili", 350);
        set("max_neili", 350);
        set("jiali", 30);
        set("combat_exp", 5000);
        set("score", 100);

        set_skill("force", 30);
        set_skill("shaolin-xinfa", 30);
        set_skill("dodge", 30);
        set_skill("shaolin-shenfa", 30);
        set_skill("claw", 30);
        set_skill("yingzhua-gong", 30);
        set_skill("parry", 30);
        set_skill("buddhism", 30);
        set_skill("literate", 30);

        map_skill("force", "shaolin-xinfa");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("claw", "yingzhua-gong");
        map_skill("parry", "yingzhua-gong");

        prepare_skill("claw", "yingzhua-gong");

        create_family("少林派", 40, "弟子");

        set("inquiry", ([
                "手諭"       : (: ask_me_1 :),
                "七十二絕藝" : (: ask_me_1 :),
                "達摩令" :     (: ask_me_2 :)
        ]));

        set("master_ob",1);
        setup();

        carry_object("/d/shaolin/obj/qing-cloth")->wear();
}


string ask_me_1()
{
        mapping fam, skl; 
        object ob;
        string *sname;
        int i;
        
        if( !(fam=query("family", this_player())) || fam["family_name"] != "少林派" )
                return RANK_D->query_respect(this_player()) + 
                "與本派素無來往，不知此話從何談起？";

        if( query("guilty", this_player())>0 )
                return RANK_D->query_respect(this_player()) + 
                "你累犯數戒，身帶重罪，我如何能給你這手諭！";

        if ( (int)this_player()->query_int() < 30 )
                return RANK_D->query_respect(this_player()) + 
                "資質不夠，不能進入藏經樓。";

        skl = this_player()->query_skills();
        sname  = sort_array( keys(skl), (: strcmp :) );

        for(i=0; i<sizeof(check_skill); i++) {
                if (skl[check_skill[i]] < 100) 
                        return RANK_D->query_respect(this_player()) + 
                               "功力不夠，不夠資格領取手諭。";
        }

        if ( (int)this_player()->query_skill("buddhism",1) < 150 )
                return RANK_D->query_respect(this_player()) + 
                "想學習上乘武功，先要以高深佛法化解它們的戾氣，否則後悔無及。";

        ob = new("/d/shaolin/obj/allow-letter");
        ob->move(this_player());
        message_vision("$N獲得一封手諭。\n",this_player());

        return "好吧，憑這封手諭，你可自由進入藏經閣二樓研習上乘武功。";

}

string ask_me_2()
{
        mapping fam; 
        object ob;
        object me;
        int i;
        
        me = this_player();
        if( !(fam=query("family", me)) || 
            fam["family_name"] != "少林派")
                return RANK_D->query_respect(me) + 
                "與本派素無來往，不知此話從何談起？";

        for(i=0; i< sizeof(check_skill); i++) {
                if (me->query_skill(check_skill[i], 1) < 30)
                return RANK_D->query_respect(me) +
                       "你" + to_chinese(check_skill[i]) +
                       "的功力不夠，不能領取達摩令。";
        }

        ob = new("/d/shaolin/obj/damo-ling");
        ob->move(me);
        message_vision("$N獲得一面達摩令。\n",this_player());

        return "好吧，憑這面達摩令，你可自由向你的師尊挑戰。";

}
