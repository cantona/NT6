// Written by Lonely@nitan.org
// xiaofeng.c 蕭峯(喬峯)

#include <ansi.h>
inherit NPC;

string *quest_msg = ({
        "蕭峯見到你説道：我聽説你的大名已久，今日一見當真是名不虛傳！\n",
        "段老伯如此信任於我，我卻沒有保護好阿朱，讓她受了重傷。\n",
        "現在阿朱的傷勢只有薛神醫才能醫治，天可憐見，薛神醫正好就在這聚賢莊上。\n",
        "蕭峯和你一見如故，無所不言，大有相見恨晚之意。\n",
        "蕭峯接着説道：我若悄悄潛入聚賢莊，將薛神醫擄走，治療阿朱之傷，當然是最穩妥的辦法。\n",
        "但喬峯是頂天立地的漢子，其能做這種偷偷摸摸之事。\n",
        "我想先讓聚賢莊上的人知道我要來，然後堂堂正正的帶着阿朱進入聚賢莊，求薛神醫醫治。\n",
        "那時候即使喬峯這條性命不在，阿朱也必然能得到薛神醫的治療。\n",
        "鮑千靈、祁六、向望海三人現在就恰好在聚賢莊，幫我擊敗這三人，他們明天應該就會把我來到的消息告訴遊氏兄弟和薛神醫。\n"
});

int do_report(string arg);
void quest_stage(object ob, int stage);

void create()
{
        set_name("蕭峯", ({"xiao feng", "xiao", "feng"}));
        set("gender", "男性");
        set("nickname",HIB"鐵掌降龍"NOR);
        set("age", 28);
        set("long",
                "他就是丐幫前任幫主，因被發現是契丹人而眾叛親離。\n"
                "在江湖上與燕子塢的慕榮復並稱為「北喬峯，南慕榮」。\n"
                "他身穿一件普通的粗布褂子，腰間用一條麻繩隨便一系。\n"
                "他身高六尺有餘，體格十分魁梧，長有一張線條粗曠、十\n"
                "分男性化的臉龐，雙目如電，炯炯有神。\n");
        set("attitude", "peaceful");

        set("str", 45);
        set("int", 30);
        set("con", 30);
        set("per",19);
        set("dex", 30);
        set("chat_chance", 1);
        set("chat_msg", ({
                "蕭峯歎了口氣道：“唉……想不到我蕭峯大好男兒，居然保護不了一個阿朱！\n",
        }));

        set("qi", 4000);
        set("max_qi", 4000);
        set("jing", 1500);
        set("max_jing", 1500);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 100);

        set("combat_exp", 180000);
        set("shen", 20000);

        set_skill("force", 120);             // 基本內功
        set_skill("huntian-qigong", 120);    // 混天氣功
        set_skill("unarmed", 120);           // 基本拳腳
        set_skill("xianglong-zhang", 120);   // 降龍十八掌
        set_skill("dodge", 120);             // 基本躲閃
        set_skill("xiaoyaoyou", 120);        // 逍遙遊
        set_skill("parry", 120);             // 基本招架
        set_skill("begging", 50);            // 叫化絕活
        set_skill("checking", 50);           // 道聽途説

        map_skill("force", "huntian-qigong");
        map_skill("unarmed", "xianglong-zhang");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "xianglong-zhang");

        //set("master_ob", 4);
        setup();

        carry_object("/clone/misc/cloth")->wear();
}
void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() )
        {
                if( (int)ob->query_temp("juxianzhuang_step") == 6 )
                {
                        call_out("quest_stage", 0, ob, 0);
                        return;
                }

                if( (int)ob->query_temp("juxianzhuang_step") == 10 )
                {
                        call_out("greeting", 1, ob);
                        return;
                }
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;

        say( "蕭峯説道：你已經打敗鮑千靈、祁六、向望海他們三個人了嗎(report)？\n" );
        add_action("do_report", "report");
}

void quest_stage(object ob, int stage)
{
        if (! ob || ! present(ob)) return;

        tell_object(ob, HIW + quest_msg[stage] + NOR);
        if (++stage < sizeof(quest_msg))
        {
                call_out( "quest_stage", 1, ob, stage );
                return;
        }
        ob->set_temp("juxianzhuang_step", 7);
}

int do_report(string arg)
{
        object me;

        me = this_player();

        if( (int)me->query_temp("juxianzhuang_step") != 10 )
                return 0;

        tell_object(me, HIW "蕭峯説道：你的幫助，喬某感激不盡。那明天一早，我們就在洛陽城東橋相見！\n" NOR );
        me->set_temp("juxianzhuang_step", 11);
        destruct(this_object());
        return 1;
}
