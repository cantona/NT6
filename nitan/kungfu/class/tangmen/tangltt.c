// tangltt

#include <ansi.h>
#include "tangmen.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

int do_pull();
string ask_me();
void close(object room);

void create()
{
        set_name("唐老太太", ({ "tang laotai", "tang" }));
        set("nickname", HIW "霹靂夫人" NOR);
        set("long",
                "她就是唐門第二代掌門唐老太太，在她的經營下，\n"
                "唐門在江湖中聲名更加顯赫。\n"
                "她大約七十有餘，一頭銀髮，紅光滿面。\n");
        set("gender", "女性");
        set("age", 72);
        set("class", "tangmen");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 28);
        set("max_qi", 8000);
        set("max_jingli", 1500);
        set("max_douzhi", 500);
        set("douzhi", 500);
        set("neili", 4000);
        set("max_neili", 4000);
        set("yanli",200);
        set("jiali", 100);
        set("combat_exp", 800000);
        set("level", 15);
        set("shen",3000);
        set("score", 7000);

        set_skill("force", 380);
        set_skill("throwing", 380);
        set_skill("dodge", 380);
        set_skill("parry", 380);
        set_skill("literate", 380);
        set_skill("hand", 380);
        set_skill("sword", 380);
        set_skill("boyun-suowu", 380);
        set_skill("biyun-xinfa", 380);
        set_skill("qiulin-shiye", 380);
        set_skill("wuzhan-mei", 380);
        set_skill("poison", 380);
        set_skill("medical", 280);
        set_skill("medical", 380);
        set_skill("tangmen-throwing", 380);
        set_skill("tangmen-poison", 380);
        set_skill("tangmen-medical", 380);

        map_skill("force", "biyun-xinfa");
        map_skill("throwing", "tangmen-throwing");
        map_skill("dodge", "qiulin-shiye");
        map_skill("parry", "wuzhan-mei");
        map_skill("sword", "wuzhan-mei");
        map_skill("hand", "boyun-suowu");
        map_skill("poison", "tangmen-poison");
        map_skill("medical", "tangmen-medical");

        prepare_skill("hand", "boyun-suowu");

        create_family("唐門世家", 2, "掌門");
        set("inquiry", ([
                "唐老爺子" : (:do_pull:),
                "大鬧唐門" : (: ask_me :)
        ]));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob", 4);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/d/tangmen/obj/feidao")->wield();
        carry_object("/d/tangmen/obj/fhshi")->wield();
        carry_object("/d/tangmen/obj/tiejili")->wield();
        carry_object("/d/tangmen/obj/feidao")->wield();
        carry_object("/d/tangmen/obj/fhshi")->wield();
        carry_object("/d/tangmen/obj/tiejili")->wield();
        carry_object("/d/tangmen/obj/qinglianzi")->wield();
        carry_object("/d/tangmen/obj/qinglianzi")->wield();
        set_temp("handing", carry_object("/d/tangmen/obj/jili"));
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

/*
        if( (query("family/family_name", ob) != "唐門世家" && member_array("唐門世家", query("reborn/fams", ob)) == -1) || 
             query("combat_exp", ob)<600000 )
        {
                command("say 你還是先拜唐缺為師，學些唐門的基本工夫吧以及提升你的戰鬥經驗吧！\n");
                return;
        }
*/

        if ((int)ob->query_skill("biyun-xinfa", 1) < 150)
        {
                command("say 唐門雖然以暗器為主，但還是要輔以內力。");
                command("say " + RANK_D->query_respect(ob) +
                        "是否還應該在碧雲心法上多下點功夫？");
                return;
        }
        if( query("dex", ob)<30 )
        {
                command("say “你的身法太差了，不要誤了自己啊！”\n");
                return;
        }
        if( query("int", ob)<28){
                command("say 唐門歷來注重弟子的文學修為。");
                command("say 本派功夫要能熟練運用，必須能體會其中所含深遠意境，悟性差了是不行的。");
                command("say " + RANK_D->query_respect(ob) + "的悟性還大有潛力可挖，還是請回吧。");
                return;
        }
        if( query("str", ob)<30){
                command("say " + RANK_D->query_respect(ob) + "的先天膂力不夠，還是請回吧。");
                return;
        }

        command("say 好吧，從今天起你就是我的關門弟子了。\n");
        command("recruit "+query("id", ob));
}

int do_pull()
{
        object me, room;
        me = this_player();
        room = environment(this_object());
        message_vision(YEL"\n唐老太太一轉身在牀頭扳動了一下。\n只聽“滋滋”幾聲輕響牀腳的地面移開了一個洞口。\n"NOR, me);
        set("exits/down", "/d/tangmen/didao1", room);
        remove_call_out("close");
        call_out("close", 3, environment(this_object()));
        return 1;
}

void close(object room)
{
        message("vision",HIR"身後傳來一聲輕響，想是暗門又被關上了。\n"NOR, this_player());
        delete("exits/down", room);
}

string ask_me()
{
        object me;
        me = this_player();
        if( query_temp("marks/鬧", me) )
        {
                command("say 你想幫唐方那個死丫頭打探消息嗎？看我不劈了你");
                command("hit"+query("id", me));
                return "看來老太婆非得教訓你一下不可。\n";
        }
        if( query_temp("marks/蕭", me) )
        {
                command("angry"+query("id", this_player()));
                command("say 難道你想像蕭秋水一樣來個大鬧唐門嗎？\n");
                command("heng"+query("id", this_player()));
                command("say 唐方那個死丫頭！\n");
                set_temp("marks/鬧", 1, this_player());
                delete_temp("marks/蕭", me);
                return"蕭秋水已被我關起來了！她別想再見到這個混小子了！\n";
        }
        else
        {
                return "瓜娃子，你説啥子？老太婆聽不懂哦！\n";
        }


}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "歷練" :
        case "歷煉" :
        case "鍛鍊" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "唐花" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tangmen-throwing/hua",
                           "name"    : "唐花",
                           "sk1"     : "tangmen-throwing",
                           "lv1"     : 180,
                            "gongxian": 1000,
                           "sk2"     : "boyun-suowu",
                           "lv2"     : 180,
                           "shen"    : 100000, ]));
                break;

        case "隨風而舞" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/qiulin-shiye/wu",
                           "name"    : "隨風而舞",
                           "sk1"     : "qiulin-shiye",
                           "lv1"     : 100,
                            "gongxian": 100,
                           ]));
                break;

        case "雲霧暗點" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/boyun-suowu/dian",
                           "name"    : "雲霧暗點",
                           "sk1"     : "boyun-suowu",
                           "lv1"     : 120,
                           "sk2"     : "biyun-xinfa",
                           "lv2"     : 120,
                            "gongxian": 600,
                           "neili"   : 1400, ]));
                break;

        case "迴夢" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/boyun-suowu/meng",
                           "name"    : "迴夢",
                           "sk1"     : "boyun-suowu",
                           "lv1"     : 160,
                           "sk2"     : "biyun-xinfa",
                           "lv2"     : 160,
                            "gongxian": 1400,
                           ]));
                break;

        case "流花掠影" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/wuzhan-mei/liu",
                           "name"    : "流花掠影",
                           "sk1"     : "wuzhan-mei",
                           "lv1"     : 120,
                            "gongxian": 400,
                           "shen"    : 4000, ]));
                break;

        case "七子剛鏢" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tangmen-throwing/biao",
                           "name"    : "七子剛鏢",
                           "sk1"     : "tangmen-throwing",
                           "lv1"     : 140,
                           "sk2"     : "biyun-xinfa",
                           "lv2"     : 120,
                            "gongxian": 600,
                           "shen"    : 60000, ]));
                break;

        case "心有千結" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tangmen-throwing/qian",
                           "name"    : "心有千結",
                           "sk1"     : "tangmen-throwing",
                           "lv1"     : 140,
                           "sk2"     : "biyun-xinfa",
                           "lv2"     : 120,
                            "gongxian": 600,
                           "shen"    : 60000, ]));
                break;

        case "散花天女" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tangmen-throwing/san",
                           "name"    : "散花天女",
                           "sk1"     : "tangmen-throwing",
                           "lv1"     : 140,
                           "sk2"     : "biyun-xinfa",
                           "lv2"     : 120,
                            "gongxian": 600,
                           "shen"    : 60000, ]));
                break;

           case "一花一世界" : 
                   return MASTER_D->teach_pfm(me, this_object(), 
                           ([ "perform" : "can_perform/tangmen-throwing/shijie", 
                              "name"    : "一花一世界", 
                              "sk1"     : "tangmen-throwing", 
                              "lv1"     : 800, 
                              "sk2"     : "biyun-xinfa", 
                              "lv2"     : 800, 
                              "gongxian": 3000,
                              "reborn"  : 1, 
                              "shen"    : 60000, ])); 
                break; 

        default:
                return 0;
        }
}
