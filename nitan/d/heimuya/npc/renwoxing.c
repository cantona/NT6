// renwoxing.c

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
int ask_bijian();

void create()
{
        set_name("任我行", ({ "ren woxing", "ren","woxing" }));
        set("title", BLU "日月神教教主"NOR );
        set("long", "只見他一張長長的臉孔，臉色雪白，更無半分血色，眉目清秀，
身材甚高，一頭黑髮，穿的是一襲青衫。\n");
        set("gender", "男性");
        set("class", "scholar");
        set("age", 55);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 30);
        set("per", 27);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        
        set("max_qi", 3000);
        set("max_jing", 1000);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 400);
        set("combat_exp", 2000000);
        set("score", 500000);

        set_skill("literate", 100);
        set_skill("force", 200);
        set_skill("dodge", 200);
        set_skill("unarmed", 200);
        set_skill("parry", 200);
        set_skill("sword", 200);
        set_skill("changquan", 200);
        set_skill("kuihua-xinfa", 200);
        set_skill("lingxu-bu", 200);
        set_skill("damo-jian", 200);
        set_skill("taiji-jian", 200);
        set_skill("huifeng-jian", 200);
        set_skill("taishan-sword", 200);
        set_skill("hengshan-jian", 200);
        set_skill("hengshan-sword", 200);
        set_skill("huashan-sword", 200);
        set_skill("songshan-sword", 200);

        map_skill("dodge", "lingxu-bu");
        map_skill("force", "kuihua-xinfa");
        map_skill("unarmed", "changquan");
        map_skill("sword", "damo-jian");
        map_skill("parry", "damo-jian");

        set("inquiry", ([
                "比劍" :  (: ask_bijian :),
                "劍法" :  (: ask_bijian :),
                "黑木令" : "要拿黑木令？老夫想先看看你的劍法！\n",
        ]) );
         setup();
        carry_object("/d/wudang/obj/bluecloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

int ask_bijian()
{
        object obj, me = this_player(), ob = this_object();
        message_vision("$N躬身説道：“晚輩今日有幸拜見任老前輩，還望多加指教。”\n
$n笑道：“不用客氣，你來解我寂寞，可多謝你啦。”\n", me, ob );
        message_vision("$N道：“不敢。”\n
$n點了點頭，説道：“我只想瞧瞧你的劍法，並非真的過
招，再説，我也未必能勝得了你。”\n\n", me, ob);
        say(HIR"任我行大喝一聲：“少林劍法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行歎了口氣，説道：“才一招。”\n");
                return 1;
        }
        command("enable sword taiji-jian");
        say(HIR"任我行大喝一聲：“武當劍法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行歎了口氣，説道：“才兩招。”\n");
                return 1;
        }
        command("enable sword huifeng-jian");
        say(HIR"任我行大喝一聲：“峨嵋劍法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行歎了口氣，説道：“才三招。”\n");
                return 1;
        }
        command("enable sword songshan-sword");
        say(HIR"任我行大喝一聲：“嵩山劍法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行歎了口氣，説道：“才四招。”\n");
                return 1;
        }
        command("enable sword taishan-sword");
        say(HIR"任我行大喝一聲：“泰山劍法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行歎了口氣，説道：“才五招。”\n");
                return 1;
        }
        command("enable sword huashan-sword");
        say(HIR"任我行大喝一聲：“華山劍法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行歎了口氣，説道：“才六招。”\n");
                return 1;
        }
        command("enable sword hengshan-sword");
        say(HIR"任我行大喝一聲：“衡山劍法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行歎了口氣，説道：“才七招。”\n");
                return 1;
        }
        command("enable sword hengshan-jian");
        say(HIR"任我行大喝一聲：“恆山劍法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行歎了口氣，説道：“還是沒過八招。”\n");
                return 1;
        }

        obj = new("/d/heimuya/obj/heimu-ling");
        obj -> move(me);
        say("任我行説道：“這位" + RANK_D->query_respect(me)+"不錯，我就送你一塊黑木令吧。”\n");
        return 1;
}
