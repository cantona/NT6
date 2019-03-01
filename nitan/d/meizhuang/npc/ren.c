// renwoxing.c

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
int ask_bijian();

void create()
{
        set_name("任我行", ({ "ren woxing", "ren","woxing" }));
        set("title", HIR "日月神教上任教主" NOR);
        set("long", "這便是日月神教上任教主任我行。只見\n"
                    "他一張長長的臉孔，臉色雪白，更無半\n"
                    "分血色。他眉目清秀，身材甚高，一頭\n"
                    "黑發，穿的是一襲青衫。\n");
        set("gender", "男性");
        set("class", "scholar");
        set("age", 55);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        
        set("max_qi", 8000);
        set("max_jing", 6000);
        set("neili", 10000);
        set("max_neili", 10000);
        set("jiali", 500);
        set("combat_exp", 4000000);
        set("score", 50000);

        set_temp("apply/attack", 1000);

        set_skill("literate", 250);
        set_skill("force", 400);
        set_skill("dodge", 360);
        set_skill("unarmed", 360);
        set_skill("parry", 360);
        set_skill("sword", 360);
        set_skill("changquan", 360);
        set_skill("xixing-dafa", 400);
        set_skill("lingxu-bu", 360);
        set_skill("damo-jian", 360);
        set_skill("taiji-jian", 360);
        set_skill("huifeng-jian", 360);
        set_skill("taishan-sword", 360);
        set_skill("hengshan-jian", 360);
        set_skill("hengshan-sword", 360);
        set_skill("huashan-sword", 360);
        set_skill("songshan-sword", 360);

        map_skill("dodge", "lingxu-bu");
        map_skill("force", "xixing-dafa");
        map_skill("unarmed", "changquan");
        map_skill("sword", "damo-jian");
        map_skill("parry", "taiji-jian");

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
        object weapon, obj;
        object me = this_player(), ob = this_object();

        if( query_temp("want_bijian", me) )
        {
                command("say 你這人這麼那麼不爽快？要比就趕緊開始吧！");
                        return 1;
        }

        if( query("skybook/xiaoao/bijian", me) )
        {
                command("say 我們已經比試過了，沒必要再戰一場。");
                        return 1;
        }

        if( query_temp("bijian_fail", me) )
        {
                command("say 你已經輸了，再比下去也沒什麼結果。");
                        return 1;
        }

        if( query("combat_exp", me)<1500000 )
        {
                command("heng");
                command("say 你還不配和我比劍！");
                        return 1;
        }

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
        {
                command("say 你不拿劍我還和你比什麼？");
                        return 1;
        }

        message_vision(CYN "$N" CYN "躬身說道：晚輩今日有幸拜見"
                       "任老前輩，還望多加指教。\n$n" CYN "笑道"
                       "：不用客氣，你來解我寂寞，可多謝你啦。"
                       "\n" NOR, me, ob );

        message_vision(CYN "$N" CYN "微笑道：不敢，還請老前輩賜"
                       "教！\n$n" CYN "點了點頭，說道：我只想"
                       "瞧瞧你的劍法，並非真的過招，再說，我也未"
                       "必能勝得了你。\n" NOR, me, ob);
        tell_object(me, HIR "你願意和(accept)任我行開始比劍嗎？\n" NOR);
        set_temp("want_bijian", 1, me);
        add_action("do_accept", "accept");
        return 1;
}

int do_accept()
{
        int eff;
        object weapon, obj;
        object me = this_player(), ob = this_object();
        eff=query("max_qi", me)/3;

        if( query_temp("want_bijian", me) )
        {
                if( !objectp(weapon=query_temp("weapon", me)) || 
                     query("skill_type", weapon) != "sword" )
                  {
                        command("say 他奶奶的，你把劍取了這算什麼意思？");
                        return 1;
                  }

                say (CYN "\n任我行哈哈一笑，說道：那我就開始進招了。\n" NOR + HIW
                     "\n只見任我行說罷身形一展，一道劍光由他處凌厲閃出。\n" NOR,
                     me, ob);

                say (HIW "\n任我行大喝一聲：看好了，我這第一招乃少林派達摩劍法"
                         "！\n" NOR);
                COMBAT_D->do_attack(ob, me, query_temp("weapon"));
                if( query("qi", me)<eff || !present(me,environment()) )
                {
                        say(CYN "任我行嘆了口氣，說道：才一招。\n" NOR);
                        delete_temp("want_bijian", me);
                        set_temp("bijian_fail", 1, me);
                        return 1;
                }

                command("enable sword taiji-jian");
                say(HIW "\n任我行大喝一聲：第二招！武當派太極劍法！\n" NOR);
                COMBAT_D->do_attack(ob, me, query_temp("weapon"));
                if( query("qi", me)<eff || !present(me,environment()) )
                {
                        say(CYN "任我行嘆了口氣，說道：才兩招。\n" NOR);
                        delete_temp("want_bijian", me);
                        set_temp("bijian_fail", 1, me);
                        return 1;
                }

                command("enable sword huifeng-jian");
                say(HIW "\n任我行大喝一聲：第三招！峨嵋派回風拂柳劍法！\n" NOR);
                COMBAT_D->do_attack(ob, me, query_temp("weapon"));
                if( query("qi", me)<eff || !present(me,environment()) )
                {
                        say(CYN "任我行嘆了口氣，說道：才三招。\n" NOR);
                        delete_temp("want_bijian", me);
                        set_temp("bijian_fail", 1, me);
                        return 1;
                }

                command("enable sword songshan-sword");
                say(HIW "\n任我行大喝一聲：第四招！嵩山劍法之天外玉龍！\n" NOR);
                COMBAT_D->do_attack(ob, me, query_temp("weapon"));
                if( query("qi", me)<eff || !present(me,environment()) )
                {
                        say(CYN "任我行嘆了口氣，說道：才四招。\n" NOR);
                        delete_temp("want_bijian", me);
                        set_temp("bijian_fail", 1, me);
                        return 1;
                }

                command("enable sword taishan-sword");
                say(HIW "\n任我行大喝一聲：第五招！泰山派十八盤劍法！\n" NOR);
                COMBAT_D->do_attack(ob, me, query_temp("weapon"));
                if( query("qi", me)<eff || !present(me,environment()) )
                {
                        say(CYN "任我行嘆了口氣，說道：才五招。\n" NOR);
                        delete_temp("want_bijian", me);
                        set_temp("bijian_fail", 1, me);
                        return 1;
                }

                command("enable sword huashan-sword");
                say(HIW "\n任我行大喝一聲：第六招！華山劍宗奪命連環三仙劍！\n" NOR);
                COMBAT_D->do_attack(ob, me, query_temp("weapon"));
                if( query("qi", me)<eff || !present(me,environment()) )
                {
                        say(CYN "任我行嘆了口氣，說道：才六招。\n" NOR);
                        delete_temp("want_bijian", me);
                        set_temp("bijian_fail", 1, me);
                        return 1;
                }

                command("enable sword hengshan-sword");
                say(HIW "\n任我行大喝一聲：第七招！衡山劍法之一劍落九雁！\n" NOR);
                COMBAT_D->do_attack(ob, me, query_temp("weapon"));
                if( query("qi", me)<eff || !present(me,environment()) )
                {
                        say(CYN "任我行嘆了口氣，說道：才七招。\n" NOR);
                        delete_temp("want_bijian", me);
                        set_temp("bijian_fail", 1, me);
                        return 1;
                }

                command("enable sword hengshan-jian");
                say(HIW "\n任我行大喝一聲：小心了，我這最後一招乃恆山派萬花劍法！\n" NOR);
                COMBAT_D->do_attack(ob, me, query_temp("weapon"));
                if( query("qi", me)<eff || !present(me,environment()) )
                {
                        say(CYN "任我行嘆了口氣，說道：還是沒過第八招。\n" NOR);
                        delete_temp("want_bijian", me);
                        set_temp("bijian_fail", 1, me);
                        return 1;
                }

                obj = new("/d/heimuya/obj/heimu-ling");
                obj->move(me);
                say(CYN "\n任我行哈哈大笑說道：閣下果然武藝超群，再來接我這路劍法！\n\n" NOR);

                message_vision(HIR "說完任我行一聲長嘯，木劍倏地劈出。$N" HIR "當即斜劍"
                               "刺出，逼得他收劍回擋。任\n我行連連呼喝，竟似發瘋一般。呼"
                               "喝越急，出劍也是越快。$N" HIR "覺得每一聲斷喝\n都令他雙"
                               "耳嗡嗡作響，心煩意亂。突然之間，任我行石破天驚般一聲狂嘯"
                               "。$N" HIR "\n耳中嗡的一響，耳鼓都似震破，腦中一陣暈眩，登"
                               "時人事不知，昏倒在地……\n" NOR, me, ob );
                delete_temp("want_bijian", me);
                set("skybook/xiaoao/bijian", 1, me);
                me->unconcious();
        }
        return 1;
}
