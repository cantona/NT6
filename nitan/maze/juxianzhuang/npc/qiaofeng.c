// Written by Lonely@nitan.org
// xiaofeng.c 蕭峰(喬峰)

#include <ansi.h>
inherit NPC;

string *quest_msg = ({
        "喬峰見到你說道：你實在是一個偉大的朋友！我喬某這輩子，交定你了！\n",
        "喬峰飽經風霜的臉上，泛起一絲難得的笑意。\n",
        "我們現在可以走了，阿朱姑娘深受重傷，暫時就躺在車中。放心，我們一定會勝利的。\n",
        "阿朱，你也一定會沒事的，等你傷好了，我們就去塞外一起牧馬放羊，再也不回來了。\n",
        "走吧！\n"
});

void quest_stage(object ob, int stage);

void create()
{
        set_name("喬峰", ({"qiao feng", "qiao", "feng"}));
        set("gender", "男性");
        set("nickname",HIB"鐵掌降龍"NOR);
        set("age", 28);
        set("long",
                "他就是丐幫前任幫主，因被發現是契丹人而眾叛親離。\n"
                "在江湖上與燕子塢的慕榮復並稱為「北喬峰，南慕榮」。\n"
                "他身穿一件普通的粗布褂子，腰間用一條麻繩隨便一系。\n"
                "他身高六尺有余，體格十分魁梧，長有一張線條粗曠、十\n"
                "分男性化的臉龐，雙目如電，炯炯有神。\n");
        set("attitude", "peaceful");

        set("str", 45);
        set("int", 30);
        set("con", 30);
        set("per", 19);
        set("dex", 30);
        set("chat_chance", 1);
        set("chat_msg", ({
                "蕭峰嘆了口氣道：“唉……想不到我蕭峰大好男兒，居然保護不了一個阿朱！\n",
        }));

        set("qi", 4000000);
        set("max_qi", 4000000);
        set("jing", 1500000);
        set("max_jing", 1500000);
        set("neili", 4000000);
        set("max_neili", 4000000);
        set("jiali", 1000);

        set("combat_exp", 1800000000);
        set("shen", 200000);

        set_skill("force", 1200);             // 基本內功
        set_skill("huntian-qigong", 1200);    // 混天氣功
        set_skill("unarmed", 1200);           // 基本拳腳
        set_skill("xianglong-zhang", 1200);   // 降龍十八掌
        set_skill("dodge", 1200);             // 基本躲閃
        set_skill("xiaoyaoyou", 1200);        // 逍遙遊
        set_skill("parry", 1200);             // 基本招架
        set_skill("begging", 500);            // 叫化絕活
        set_skill("checking", 500);           // 道聽途說

        map_skill("force", "huntian-qigong");
        map_skill("unarmed", "xianglong-zhang");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "xianglong-zhang");

        //set("master_ob", 4);
        set("auto_perform", 1);
        setup();

        carry_object("/clone/misc/cloth")->wear();
}
void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() )
        {
                if( (int)ob->query_temp("juxianzhuang_step") == 11 )
                {
                        call_out("quest_stage", 1, ob, 0);
                        return;
                }

                if( base_name(environment()) == "/maze/juxianzhuang/damen" )
                {
                        this_object()->set_leader(0);
                        message_vision("$n和$N以及阿朱一行來到聚賢莊門前，徐長老迎面上來，出于故人之情，勸$N離開。\n"
                                       "然而$N一心只想為阿朱療傷，就是上刀山下火海也在所不惜。\n"
                                       "$N抱著阿朱直接闖進了聚賢莊。\n",
                                       this_object(), ob);
                        ob->set_temp("juxianzhuang_step", 13);
                        destruct(this_object());
                }
        }
}

void quest_stage(object ob, int stage)
{
        remove_call_out("quest_stage");

        if (! ob || ! present(ob)) return;

        tell_object(ob, HIW + quest_msg[stage] + NOR);
        if (++stage < sizeof(quest_msg))
        {
                call_out( "quest_stage", 1, ob, stage );
                return;
        }
        ob->set_temp("juxianzhuang_step", 12);
        this_object()->set_leader(ob);
        message_vision("$N決定開始跟隨$n一起行動。\n", this_object(), ob);
        return;
}
