// This program is a part of NT MudLIB

#include <ansi.h>
#include "taohua.h"
#include "game.h"

inherit NPC;
inherit F_NOCLONE;

string ask_chicken();
int ask_jiuyin();
int ask_game();

void create()
{
        set_name("黃蓉", ({"huang rong", "huang", "rong"}));
        set("title", "東海桃花島主之女");
        set("nickname", HIY "丐幫前任幫主" NOR);
        set("gender", "女性");
        set("age", 28);
        set("long", "這便是桃花島島主的獨生女兒。由于島主夫人\n"
                    "早死，島主對這個女兒備加疼愛。她生性跳脫\n"
                    "飛揚，喜歡四處亂跑。\n");
        set("attitude", "peaceful");
        set("class", "scholar");
        set("str", 28);
        set("int", 40);
        set("con", 30);
        set("dex", 30);
        set("qi", 4800);
        set("max_qi", 4800);
        set("jing", 3500);
        set("max_jing", 3500);
        set("neili", 5500);
        set("max_neili", 5500);
        set("jiali", 200);
        set("level", 20);
        set("combat_exp", 3000000);

        set_skill("force", 240);
        set_skill("bibo-shengong", 240);
        set_skill("hand", 240);
        set_skill("strike", 240);
        set_skill("luoying-shenzhang", 240);
        set_skill("dodge", 240);
        set_skill("luoying-shenfa", 240);
        set_skill("parry", 220);
        set_skill("sword", 220);
        set_skill("luoying-shenjian", 220);
        set_skill("yuxiao-jianfa", 220);
        set_skill("lanhua-shou", 240);
        set_skill("staff", 240);
        set_skill("dagou-bang", 240);
        set_skill("unarmed", 200);
        set_skill("xiaoyaoyou", 200);
        set_skill("throwing", 200);
        set_skill("mantianhuayu", 200);
        set_skill("qimen-wuxing", 280);
        set_skill("count", 280);
        set_skill("literate", 280);
        set_skill("mathematics", 280);
        set_skill("cooking", 280);
        set_skill("martial-cognize", 220);

        map_skill("force", "bibo-shengong");
        map_skill("hand", "lanhua-shou");
        map_skill("dodge", "luoying-shenfa");
        map_skill("parry", "lanhua-shou");
        map_skill("staff", "dagou-bang");
        map_skill("sword", "yuxiao-jian");
        map_skill("strike", "xiaoyaoyou");
        map_skill("throwing", "mantianhuayu");

        prepare_skill("hand", "lanhua-shou");
        prepare_skill("strike", "xiaoyaoyou");

        create_family("桃花島", 2, "愛女");

        set("inquiry", ([
                "九陰真經經義" : (: ask_jiuyin :),
                "遊戲"   : (: ask_game :),
                "叫化雞" : (: ask_chicken :),

        ]) );

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.fu" :),
                (: perform_action, "hand.fei" :),
                (: perform_action, "strike.zhuan" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob", 4);
        setup();
        carry_object("/clone/unique/ruanwei-jia")->wear();
        carry_object("/d/taohua/obj/shudai")->wear();
        set("startroom", "/d/wuguan/guofu_huayuan");
        check_clone();
}

void attempt_apprentice(object ob)
{
        command("say 現在國難當頭，我哪裡有時間收徒啊。");
        return;
}

string ask_chicken()
{
        if( query_temp("marks/雞", this_player()) )
                return "你這個人怎麼這麼煩？老說車□轆話！\n";
        else
        {
                say("蓉兒神往地說：叫化雞可是杭州著名特產，我爹當年費了好大的勁才搞到了制作\n"
                    "它的秘方。你問它來幹什麼？\n");

                set_temp("marks/雞", 1, this_player());

                return "你可以出去了。\n";
        }
}
int ask_jiuyin()
{
        object me = this_player();

        if( query("family/family_name", me) == "白駝山派" && !query("reserve", me )
                 && query("family/master_id", me) == "ouyang feng" )
        {
                if( query("combat_exp", me)>500000 && present("mask_jiuyin",me) )
                {
                        destruct( present("mask_jiuyin", me) );
                        message_vision(HIY "黃蓉眼中閃過一絲狡黠的神色：“你想知道真經的解釋麼？好吧，我說給你聽便是。”\n", me);
                        message_vision("說罷，接過$N手中的經書，輕輕念了起來：\n", me);
                        message_vision("“「忽不爾，肯星多得，斯根六補」這是「善用觀相，運作十二種息」的意思。\n", me);
                        message_vision("「吉爾文花思，哈虎」嗯....這個該作「能癒諸患，漸入神通」解...”\n", me);
                        message_vision(HIG "$N大為興奮，忙凝神傾聽，內息早于不知不覺中按照黃蓉所解之法四處遊走......\n", me);
                        message_vision("$N的神智漸漸迷糊起來，忽而抓耳撓腮，忽而側頭苦思，種種怪狀，令人不解。\n", me);
                        message_vision("突然間，$N反手啪啪啪連打自己三個耳光，雙手撐地，倒立了起來，全身真氣逆遊亂走 \n"NOR, me);
                        if (random(5) == 3)
                        {
                                tell_object(me,"過了半晌，你只覺得全身經脈運行方式大為異常，略一提氣，發現陰維，陽維，陰嶠， \n");
                                tell_object(me,"陽嶠四脈頗有逆行之勢，不由得又驚又喜。\n");
                                set("reserve", 1, me);
                                addn("eff_jing", -100, me);
                                addn("max_neili", -2, me);
                        } else {
                                tell_object(me,"過了半晌，你心中一團亂麻，渾身乏力，頭痛欲裂。一聲嘶吼，暈了過去...\n");
                                addn("eff_jing", -100, me);
                                addn("max_neili", -2, me);
                                me->unconcious();
                        }
                        return 1;
                } else  return notify_fail("黃蓉白了你一眼：“就你這點微末道行，想學九陰真經？也不怕被人笑掉大牙麼？”\n");
        } else return 0;
}

int ask_game()
{
        object me = this_player();
        object ob = this_object();

        if( query_temp("match_game/playing", me)){
                write("你已經在玩遊戲了。\n");
                return 1;
        }
/*if( query_temp("match_game/lost", me)){
                message_vision( "$n仰起頭不屑的對$N說道：你太笨了，我才不跟你玩呢。\n", me, ob );
                return 1;
        }*/
        if( query_temp("match_game/win", me)){
                message_vision( "$n點了點頭道：好吧！上次僥幸讓你贏了，這回你就沒這麼好運氣了。\n", me, ob );
                delete_temp("match_game/win", me);
        }
        else
                message_vision( "$n眉頭一揚，對$N說到：好啊，看看你到底有多聰明。\n", me, ob );
        return play_game(me,ob);
}
