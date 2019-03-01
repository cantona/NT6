// This program is a part of NT MudLIB

#include <ansi.h>
#include "xiaoyao.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;
inherit F_QUESTER;

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
string ask_me();
string ask_book();
int ask_job();
int ask_fail();

void create()
{
        set_name("蘇星河", ({"su xinghe", "su", "xinghe"}));
        set("gender", "男性" );
        set("nickname", HIW "聰辯老人" NOR);
        set("long", @LONG
此人就是號稱聰辯老人的蘇星河，據說他能言
善辯，是武林中頗為傳神的一位智者，而他的
武功也是無人能知。
LONG );
        set("class", "scholar");
        set("age", 60);
        set("str", 29);
        set("con", 30);
        set("int", 45);
        set("dex", 37);
        set("level", 20);
        set("combat_exp", 2000000);
        set("attitude", "peaceful");

        set("max_qi", 5000);
        set("max_jing", 3000);
        set("neili", 5500);
        set("max_neili", 5500);
        set("jiali", 120);

        set_skill("force", 260);
        set_skill("xiaowuxiang", 240);
        set_skill("dodge", 240);
        set_skill("feiyan-zoubi", 240);
        set_skill("strike", 240);
        // set_skill("panyang-zhang", 240);
        set_skill("liuyang-zhang", 240);
        set_skill("hand", 240);
        set_skill("qingyun-shou", 240);
        set_skill("zhemei-shou", 240);
        set_skill("parry", 240);
        set_skill("blade", 240);
        set_skill("ruyi-dao", 240);
        set_skill("literate", 280);
        set_skill("medical", 260);
        set_skill("xiaoyao-qixue", 260);
        set_skill("mathematics", 240);
        set_skill("qimen-wuxing", 240);
        set_skill("drawing",   240);
        set_skill("chuixiao-jifa", 240);
        set_skill("tanqin-jifa", 240);
        set_skill("chess", 280);
        set_skill("calligraphy", 240);
        set_skill("martial-cognize", 240);

        map_skill("force", "xiaowuxiang");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("hand", "zhemei-shou");
        map_skill("strike", "liuyang-zhang");
        map_skill("parry", "zhemei-jian");
        map_skill("blade", "ruyi-dao");
        map_skill("medical", "xiaoyao-qixue");

        prepare_skill("hand", "zhemei-shou");
        prepare_skill("strike", "liuyang-zhang");

        set("no_teach", ([
                "zhemei-shou"   : "逍遙折梅手乃本門神功，只能由掌門人傳授。",
                // "liuyang-zhang" : "這天山六陽掌向來只能由逍遙派掌門傳功，我不便教授。",
        ]));

        create_family("逍遙派", 2, "掌門弟子");

        set("inquiry", ([
                "捕風捉影" : (: ask_skill1 :),
                // "攀陽邀月" : (: ask_skill2 :),
                "如意六刀" : (: ask_skill3 :),
                "秘密地道" : (: ask_me :),
                "秘籍"     : (: ask_book :),
                "任務" : (: ask_job() :),
                "job" : (: ask_job() :),
                "失敗" : (: ask_fail() :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.zhe" :),
                (: perform_action, "hand.hai" :),
                (: perform_action, "strike.huan" :),
                (: perform_action, "strike.zhong" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }));

        set("coagents", ({
                ([ "startroom" : "/d/xiaoyao/shishi",
                   "id"        : "wuya zi" ]),
        }));

        set("guarder", ([
                "refuse_other": CYN "$N" CYN "對$n" CYN "冷喝道："
                                "閣下請留步，此處乃本門禁地，旁人"
                                "不得入內。" NOR,
                "refuse_carry": CYN "$N" CYN "對$n" CYN "喝道：你"
                                "背負的是什麼人，還不快快給我放下"
                                "！" NOR,
        ]));

        set("master_ob", 4);
        setup();
        carry_object("/clone/cloth/cloth")->wear();
}


void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if (ob->query_int() < 30)
        {
                command("say " + RANK_D->query_respect(ob) + "是否還應該在學"
                        "問上多下點功夫，笨人可逍遙不了！");
                return;
        }

        if( query("combat_exp", ob)<200000 )
        {
                command("say 你現在經驗尚淺，不能領會高深的武功，先鍛煉要緊。");
                return;
        }

        if (ob->query_skill("force", 1) < 100)
        {
                command("sigh");
                command("say 我們逍遙派的武功都要以內功為基礎，你先把"
                        "基礎內功學紮實吧。");
                return;
        }

        if (ob->query_skill("xiaowuxiang", 1) < 100)
        {
                command("sigh");
                command("say 你連本門的入門心法都沒有學好，還想學本門"
                        "的上乘武學？");
                return;
        }

        command("say 好吧，我就收下你了，今後要多加努力啊！");
        command("recruit "+query("id", ob));
}

int permit_pass(object me, string dir)
{
        if (! ::permit_pass(me, dir))
                return 0;

       if( query("family/master_id", me) == "wuyazi" )
                return 1;

        if( query("combat_exp", me)<300000 )
        {
                command("say 你這種身手不要去那裡，好好學我們逍遙派武功。");
                return 0;
        }

        if (me->query_skill("xiaowuxiang", 1) < 120)
        {
                command("say 連我們逍遙心法都學不好，亂走什麼？");
                return 0;
        }

        command("sigh");
        command("say 去吧，去吧！有緣者事竟成。");
        return 1;
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/qingyun-shou/zhuo", me) )
                return "我不是已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素無瓜葛，何出此言？";

        if (me->query_skill("qingyun-shou", 1) < 1)
                return "你連青雲手都未曾學過，何來絕招？";

        if( query("family/gongji", me)<50 )
                return "你雖在我逍遙門下，卻甚無作為，這招我先不忙傳你。";

        if (me->query_skill("force") < 100)
                return "你的內功火候不足，學不成這招。";

        if (me->query_skill("qingyun-shou", 1) < 50)
                return "你的青雲手火候未到，還得多練習練習。";

        message_vision(HIY "$n" HIY "點了點頭，伸手將$N" HIY "招至"
                       "身邊，在耳旁低聲細說良久，$N" HIY "聽"
                       "後會\n心的一笑，看來大有所悟。\n" NOR, me,
                       this_object());

        command("nod");
        command("say 明白了？");
        tell_object(me, HIC "你學會了「捕風捉影」。\n" NOR);

        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("qingyun-shou"))
                me->improve_skill("qingyun-shou", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/qingyun-shou/zhuo", 1, me);
        addn("family/gongji", -50, me);
        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/panyang-zhang/pan", me) )
                return "我不是已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素無瓜葛，何出此言？";

        if (me->query_skill("panyang-zhang", 1) < 1)
                return "你連攀陽掌都未曾學過，何來絕招？";

        if( query("family/gongji", me)<100 )
                return "你雖在我逍遙門下，卻甚無作為，這招我先不忙傳你。";

        if (me->query_skill("force") < 100)
                return "你的內功火候不足，學不成這招。";

        if (me->query_skill("panyang-zhang", 1) < 60)
                return "你的攀陽掌火候未到，還得多練習練習。";

        message_vision(HIY "$n" HIY "略微點了點頭，說道：“我給你演示"
                      "一遍，可瞧仔細了！”隨即\n一聲清嘯，雙掌紛飛貫"
                      "出，掌影重重疊疊虛實難辨，全全籠罩$N" HIY "全身"
                      "。\n" NOR, me, this_object());

        command("nod");
        command("say 看清楚了就自己下去練吧。");
        tell_object(me, HIC "你學會了「攀陽邀月」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("panyang-zhang"))
                me->improve_skill("panyang-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/panyang-zhang/pan", 1, me);
        addn("family/gongji", -100, me);
        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/ruyi-dao/ruyi", me) )
                return "我不是已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素無瓜葛，何出此言？";

        if (me->query_skill("ruyi-dao", 1) < 1)
                return "你連如意刀法都未曾學過，何來絕招？";

        if( query("family/gongji", me)<200 )
                return "你雖在我逍遙門下，卻甚無作為，這招我先不忙傳你。";

        if (me->query_skill("force") < 150)
                return "你的內功火候不足，學不成這招。";

        if (me->query_skill("ruyi-dao", 1) < 100)
                return "你的如意刀法火候未到，還得多練習練習。";

        message_vision(HIY "$n" HIY "點點頭，微笑著示意讚許，伸手將$N"
                       HIY "招到身前，低聲在$N" HIY "耳旁嘀\n咕了半天"
                       "。不時還拔出腰刀揮舞幾下，似乎是一種頗為神妙的"
                       "刀訣。\n" NOR, me, this_object());

        command("smile");
        command("say 這招很簡單，只需稍加練習便成。");
        tell_object(me, HIC "你學會了「如意六刀」。\n" NOR);

        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("ruyi-dao"))
                me->improve_skill("ruyi-dao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/ruyi-dao/ruyi", 1, me);
        addn("family/gongji", -200, me);
        return 1;
}

string ask_book()
{
        object me,ob;
        mapping fam;

        ob = this_player();
        if( !(fam=query("family", ob) )
                || fam["family_name"] != "逍遙派")
        {
                return "想要秘籍就得加入逍遙派。";
        }

        command("sigh");
        return "本派的武功秘籍藏在一個很秘密的地方，我也沒去過。";
}
string ask_me()
{
        object me,ob;
        mapping fam;

        ob = this_player();
        if( !(fam=query("family", ob) )
                || fam["family_name"] != "逍遙派")
        {
                return "想要知道密道就得加入逍遙派。";
        }

        command("sigh");
        return "本派的密道在華山之上，很是艱險。你有興趣可以去看看。";
}

int ask_job()
{

        object me = this_player();
        object ob;
        mapping quest;
        mapping skl;
        string *sname, place;
        int i, skill = 0;
        quest = ("/d/xiaoyao/npc/lagjob")->query_quest();

        skl = me->query_skills();
        if ( !skl ) {
                tell_object(me, "你去學一些本事先吧！\n");
                return 1;
                }
        sname  = sort_array( keys(skl), (: strcmp :) );
        for(i=0; i<sizeof(skl); i++)
                if (skl[sname[i]] >= skill && sname[i] != "literate" && sname[i] != "taoism")

                        skill = skl[sname[i]];

        if (skill < 80) skill = 80;


        if( query("family/family_name", me) != "逍遙派" )
           {
                      message_vision("$N對著$n大喝一聲：本派弟子才能做任務。你是哪來的姦細？\n", this_object(), me);
                      return 1;
            }

        if( query("combat_exp", me)<100000){
                command("say " + RANK_D->query_respect(me) + "找本派的掌門信物是很難的，你還是練高經驗再來吧");
                return 1;
}
        if ((int)me->query_condition("menpai_busy"))
            {
                      message_vision("$N對著$n搖了搖頭說：你辦事不利,等會再來!\n", this_object(), me);
                      return 1;
            }

        if( query("potential", me)<200 || query("combat_exp", me)<300){
                command("say 你連本錢都沒有，我怎麼放心要你去找本派的掌門信物？");
                return 1;
        }

        if( query("kill_xiaoyao", me) == 1){

                command("kick"+query("id", me));
                command("say 我不是給了你任務了嗎？");
                return 1;
                }
        else {
                command("nod"+query("id", me));
                command("say " + RANK_D->query_respect(me) + "能為逍遙派出力，真是太好了。");
                command("say"+query("id", me)+"七寶指環在在『"+quest["short"]+"』出現，快去吧！\n"NOR);
                set("kill_xiaoyao", 1, me);
                set("task_time", time()+300, me);
                ob = new("/d/xiaoyao/npc/qiangdao",1);
                if( query("combat_exp", me)>2000000){
                ob = new("/d/xiaoyao/npc/qiangdao2",1);
                }
                ob->move(quest["place"]);
                set_temp("owner/id",query("id",  me), ob);
                set("combat_exp",query("combat_exp",  me), ob);
                set("max_force",query("max_force",  me), ob);
/*
                set("eff_kee",query("max_kee",  me), ob);
                set("max_kee",query("max_kee",  me), ob);
                set("kee",query("max_kee",  me), ob);
*/
                ob->set_skill("dodge", skill);
                ob->set_skill("force", skill);
                ob->set_skill("parry", skill);

                set("force_factor", random(10), ob);
                return 1;
               }
}


int ask_fail()
{
        object me = this_player();

        if( query("kill_xiaoyao", me) == 1){
                command("sigh");
                command("say 你這身手也來找本派的七寶指環,扣你50點POT.");
                addn("potential", -50, me);
               delete("kill_xiaoyao", me);
                me->apply_condition("menpai_busy",10);
//                call_out("delete", 1);
                return 1;
                }
}

int accept_object(object me, object obj)
{
        int r;
   object ob=this_object();
        if (r = ::accept_object(me, obj))
                return r;
   if(!me || environment(me) != environment()) return 0;
   if(!objectp(obj)) return 0;
   if(!present(obj, me)) return notify_fail("你沒有這件東西。");
   if(userp(obj) || obj->is_item_make()){
       command("consider"+query("id", me));
       command("say 你拿個快死的人來騙我？");
       return 0;
       }
   if( query("id", obj) == "zhihuan" && query("kill_xiaoyao", me) == 1 )
   {
       command("nod"+query("id", me));
       command("say 幹得好！\n");
       remove_call_out("destroying");
       call_out("destroying", 5, obj, ob, me);
       return 1;
       }

   if( query("money_id", obj)){
       command("pat"+query("id", me));
       command("say 我要錢幹什麼?");
       return 0;
       }
   if( query("kill_xiaoyao", me) == 0){
       command("hehe"+query("id", me));
       command("say 不錯啊，但這活我沒叫你幹啊。");
       return 1;
       }
   else return 0;
}

void destroying(object obj, object ob, object me)
{
   object n_money;
   int kar, exp, pot, gj;
   kar=random(query("kar", me))*15;
   exp = 100 + kar;
   pot = random(exp-80);  //   pot = random(exp)-80;
   gj = random(8)+4;

   if(obj) destruct(obj);

   if(!ob) return;
   if(!me || environment(me) != environment()){
      command("say 咦，人呢？");
      return;
      }
   command("pat"+query("id", me));
   message_vision(HIY"$N對$n說道：你這次做得極為出色！我就指點你兩手功夫吧.\n"NOR,ob, me);
                  message_vision(HIC "\n由于$N成功的找回七寶指環，被獎勵：\n"
                + chinese_number(exp / 3) + "點實戰經驗，\n"
               + chinese_number(pot / 2) + "點潛能，\n"
                + chinese_number(gj) + "點功績作為答謝。\n" NOR, me);
                addn("combat_exp", exp/3, me);
                addn("family/gongji", gj, me);
                if( query("potential", me)>me->query_potential_limit() )
                        addn("potential", pot/2, me);
                else
                        addn("potential", 1, me);
                delete("kill_xiaoyao", me);
        return;
}



/*
void unconcious()
{
        die();
}
*/
