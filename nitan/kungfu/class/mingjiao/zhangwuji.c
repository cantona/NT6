// This program is a part of NT MudLIB
// zhangwuji.c

#include <ansi.h>
#include "mingjiao.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

mixed ask_jiuyang();
mixed ask_qiankun();
mixed ask_ling();

string ask_book();
string ask_qishang();

int ask_hu_quest();
int ask_hu();
int ask_hdg();
void destroy(object ob);
void restart(object me, object ob);

void create()
{
        seteuid(getuid());
        set_name("張無忌", ({ "zhang wuji", "zhang", "wuji" }));
        set("long", @LONG
明教教主張無忌，統領天下十萬教眾，豪氣幹雲，叱□千秋，
「九陽神功」、「乾坤大挪移」獨步天下，是江湖中不世出的
少年英雄。
LONG );
        set("title",HIG "明教" HIM " 教主" NOR);
        set("gender", "男性");
        set("age", 20);
        set("no_get", 1);
        set("shen_type",1);
        set("attitude", "friendly");
        set("class", "fighter");

        set("str", 33);
        set("int", 35);
        set("con", 38);
        set("dex", 33);

        set("qi", 5800);
        set("max_qi", 5800);
        set("jing", 2700);
        set("max_jing", 2700);
        set("neili", 8000);
        set("max_neili", 8000);
        set("jiali", 120);
        set("level", 50);
        set("combat_exp", 2900000);
        set("score", 455000);
        set("book_count", 1);

        set_skill("force", 600);
        set_skill("unarmed", 600);
        set_skill("dodge", 600);
        set_skill("parry", 600);
        set_skill("cuff", 600);
        set_skill("sword", 600);
        set_skill("blade", 600);
        set_skill("strike", 600);
        set_skill("claw", 600);
        set_skill("throwing", 600);
        // set_skill("duoming-jinhua", 450);
        set_skill("jiuyang-shengong", 600);
        set_skill("shenghuo-xinfa", 600);
        set_skill("shenghuo-shengong", 600);
        set_skill("lingxu-bu", 600);
        set_skill("shenghuo-bu", 600);
        set_skill("qingfu-shenfa", 600);
        set_skill("qiankun-danuoyi", 600);
        set_skill("qishang-quan", 600);
        set_skill("taiji-quan", 600);
        set_skill("taiji-jian", 600);
        set_skill("taiji-dao", 600);
        set_skill("lieyan-dao", 600);
        set_skill("liehuo-jian", 600);
        // set_skill("yingzhua-shou", 450);
        // set_skill("hanbing-mianzhang", 450);
        set_skill("shenghuo-ling", 600);
        set_skill("guangming-zhang", 600);
        set_skill("medical", 600);
        set_skill("literate", 600);
        set_skill("martial-cognize", 600);
        set_skill("guangming-jing", 600);

        map_skill("force", "jiuyang-shengong");
        map_skill("dodge", "qingfu-shenfa");
        map_skill("unarmed", "jiuyang-shengong");
        map_skill("strike","guangming-zhang");
        map_skill("cuff", "qishang-quan");
        map_skill("sword","shenghuo-ling");
        map_skill("parry","qiankun-danuoyi");
        map_skill("blade","taiji-dao");
        // map_skill("claw", "yingzhua-shou");
        // map_skill("throwing", "duoming-jinhua");
        // map_skill("strike", "hanbing-mianzhang");

        prepare_skill("cuff", "qishang-quan");

        set("inherit_title",HIG"明教"HIY"光明使者"NOR);
        create_family("明教", 34, "教主");

        set("no_teach", ([
                "jiuyang-shengong"  : "這個我可不能傳你。",
                "taiji-jian"        : "你還是找我太師父吧！",
                "taiji-quan"        : "你還是找我太師父吧！",
                "taiji-dao"         : "你還是找我太師父吧！",
                "qishang-quan"      : "想學七傷拳你還是找我義父謝遜吧！",
                "qiankun-danuoyi"   : "乾坤大挪移只有明教教主方能修煉，難道你想做教主？",
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: command("perform sword.hua") :),
                (: command("perform sword.xi") :),
                (: command("perform sword.lian") :),
                (: command("perform sword.can") :),
                (: command("perform cuff.shang") :),
                (: command("perform cuff.fei") :),
                (: command("yun shield") :),
                (: command("yun powerup") :),
                (: command("yun recover") :),
        }) );

        set("chat_chance", 2);
        set("chat_msg",({
                "張無忌憤然說道“大丈夫當以國為家, 捐軀沙場, 抗元大業未成, 同輩仍需努力!”\n",
                "張無忌嘆道“人生失一知己, 生亦何歡, 死亦何憂, 敏兒, 你在哪裡?”\n",
                "張無忌道“我教兄弟聽了: 生于亂世, 當克己為公, 行俠仗義, 盪寇驅魔!”\n",
        }));

        set("inquiry",([
                "明教"     : "你打聽我們明教做什麼？。\n",
                "金毛獅王" : "那是我義父謝大俠的職司。\n",
                "謝遜"     : "他就是我義父的大號。\n",
                "張翠山"   : "你想找我父親有事麼? \n",
                "殷素素"   : "我媽是明尊座下紫微堂主。\n",
                "張三豐"   : "我太師父近來可好? \n",
                "趙敏"     : "人生失一知己, 生亦何歡, 死亦何憂, 敏兒, 你在哪裡?\n",
                "小昭"     : "小昭我可一直念著她的好處。\n",
                "周芷若"   : "找她就去峨嵋山, 別來煩我。\n",
                "九陽秘籍" : (: ask_jiuyang :),
                "鐵燄令"   : (: ask_ling :),
                "乾坤大挪移" : (: ask_qiankun :),
                "鮮于通"   : (: ask_hu_quest :),
                "胡青牛"   : (: ask_hu :),
                "蝴蝶谷"   : (: ask_hdg :),
                "七傷拳經" : (: ask_qishang :),
                "秘籍"     : (: ask_book :),

        ]));
        set_temp("apply/attack", 180);
        set_temp("apply/damage", 180);
        set_temp("apply/unarmed_damage", 180);
        set_temp("apply/armor", 180);

        set("master_ob",5);
        setup();
        carry_object("/clone/cloth/cloth")->wear();
        // carry_object("/clone/weapon/gangjian")->wield();
        carry_object("/clone/book/shenghuo-ling")->wield();
        add_money("silver",70);
}

void init()
{
        object ob;

        ::init();

        if( interactive(this_player()) && query_temp("fighting", this_player()) )
        {
                COMBAT_D->do_attack(this_object(), this_player(), query_temp("weapon") );
                addn_temp("beat_count", 1, this_player());
        }
        if( interactive(ob=this_player()) && !is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting",1,ob);
        }
}

void greeting(object ob)
{
        if (! ob || environment(ob)!=environment()) return;
        if( query("shen", ob)<-50000 )
        {
                command("wield yitian jian");
                command("hit"+query("id", ob));
                command("unwield yitian jian");
        } else
        if( query("shen", ob)<-5000 )
        {
                command("say 魔從心起，于武學不利，其道必誅，勸君放下屠刀，"
                        "立地成佛。");
        } else
        if( query("shen", ob)<-100 )
        {
                command("say 這位朋友，人行江湖，言行當正，切務走進邪魔歪道。");
        } else
        if( query("shen", ob) >= 0 )
        {
                command("say 光明正道任人走，勸君多加保重。");
        } else
        if( query("shen", ob)>50000 )
        {
                command("say 大俠在上，受無忌一禮，大俠它日必為武林翹楚。");
        }
        return;
}

int accept_fight(object ob)
{
        if( query("combat_exp", ob)<30000 && query("shen", ob)>0 )
        {
                message_vision("武林中人最忌爭強鬥狠，你不是我的對手，"
                               "回去吧。\n",ob);
                return 0;
        }
        message_vision("張無忌一拱手說道：這位" + RANK_D->query_respect(ob) +
                       "，在下領教了。\n", ob);
        return 1;
}

void attempt_apprentice(object ob)
{
        object me  = this_object();
        mapping ob_fam;
        mapping my_fam = query("family", me);

        string name, new_name;

        if (! permit_recruit(ob))
                return;

        if( !(ob_fam=query("family", ob)) || ob_fam["family_name"] != "明教" )
        {
                command("say " + RANK_D->query_respect(ob) + "與本教素無來往，不知此話從何談起？");
                return;
        }

        if ( ob_fam["generation"] > my_fam["generation"] + 2)
        {
                command("say " + RANK_D->query_respect(ob) + "，你先去找教內其他兄弟好好學學武功吧。");
                return;
        }

        if( query("shen", ob)<90000 )
        {
                command("say 你行俠仗義的事做得還不夠，還是請回吧。");
                return;
        }

        if( query("combat_exp", ob)<1000000 )
        {
                command("say 你的經驗太少，好好再去江湖闖盪闖盪，可別給我明教丟臉啊 !");
                return;
        }

        command("say 恩，好！本教又培養出一位江湖高手，真是可喜可賀 !");

        command("say 恭喜你榮升為明教光明使者！");
        command("recruit "+query("id", ob));

        return;
}

int accept_object(object who, object ob)
{
        int r;
        object me;
        mapping fam;

        me = this_object();
        fam=query("family", who);

        if (playerp(ob))
                return 0;

        if (r = ::accept_object(who, ob))
                return r;

          if( query("id", ob) == "jin mao" )
        {
                tell_object(who, GRN "張無忌激動地說道：你找到我的義父了。\n" NOR);
                if( !query_temp("marks/義父", who) )
                        set_temp("marks/義父", 1, who);
                remove_call_out("destrory");
                call_out("destrory", 1, ob);
                return 1;
        }
          if( query("id", ob) == "shenghuo ling" )
        {
                if (! (fam) || fam["family_name"] != "明教")
                {
                        command("thank"+query("id", who));
                        command("say 多謝你為本教找回了聖物，不知我應該怎麼謝謝你？\n");
                        call_out("destroy", 1, ob);
                        return 1;
                }
                if (fam["family_name"] == "明教"
                     && (fam["master_name"] != "張無忌" || query_temp("mj_jiaozhu", who)) )
                {
                        command("nod"+query("id", who));
                        command("say 你為本教找回了聖物，這筆功勞不小啊！\n");
                        call_out("destroy", 1, ob);
                        addn("shen", 2000, who);
                        addn("combat_exp", 100+random(50), who);
                        tell_object(who,HIW"你被獎勵了一些正神和經驗值。\n"NOR);
                        return 1;
                }
                if( query("mj_jiaozhu", me) )
                {
                        command("pat"+query("id", who));
                        command("say 不錯不錯，但有人已經比你先找到了。\n");
                        return 0;
                }
                command("ah"+query("id", who));
                command("say 你竟找回了本教聖物，不愧是我的弟子！");
                command("say 上代陽教主有遺命，尋回聖物者當可修習本教神功，你去秘道中試試吧。");
                set_temp("mj_jiaozhu", 1, who);
                set("mj_jiaozhu", 1, me);
                call_out("destroy", 1,  ob);
                remove_call_out("restart");
                call_out("restart", 3600, me, ob);
                return 1;
        } else
                return 0;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "歷練" :
        case "歷煉" :
        case "鍛煉" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "烈火三絕劍" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/liehuo-jian/jue",
                           "name"    : "烈火三絕劍",
                           "sk1"     : "liehuo-jian",
                           "lv1"     : 100,
                           "neili"   : 1000,
                           "gongxian": 400,
                           "shen"    : 50000, ]));
                break;

        case "吸燄令" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shenghuo-ling/xi",
                           "name"    : "吸燄令",
                           "sk1"     : "shenghuo-ling",
                           "lv1"     : 140,
                           "neili"   : 2000,
                           "gongxian": 800,
                           "shen"    : 100000, ]));
                break;

        case "斂心令" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shenghuo-ling/lian",
                           "name"    : "斂心令",
                           "sk1"     : "shenghuo-ling",
                           "lv1"     : 160,
                           "neili"   : 2200,
                           "gongxian": 800,
                           "shen"    : 100000, ]));
                break;
        case "光華令" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shenghuo-ling/hua",
                           "name"    : "光華令",
                           "sk1"     : "shenghuo-ling",
                           "lv1"     : 160,
                           "neili"   : 2400,
                           "gongxian": 900,
                           "shen"    : 80000, ]));
                break;
        case "殘血令" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shenghuo-ling/can",
                           "name"    : "殘血令",
                           "sk1"     : "shenghuo-ling",
                           "lv1"     : 220,
                           "neili"   : 5000,
                           "force"   : 350,
                           "gongxian": 1000,
                           "shen"    : 100000, ]));
                break;
        case "九曦混陽" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyang-shengong/jiu",
                           "name"    : "九曦混陽",
                           "sk1"     : "jiuyang-shengong",
                           "lv1"     : 220,
                           "neili"   : 5000,
                           "force"   : 350,
                           "gongxian": 1000,
                           "shen"    : 100000, ]));
                break;
        case "混沌一陽" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyang-shengong/hun",
                           "name"    : "混沌一陽",
                           "sk1"     : "jiuyang-shengong",
                           "lv1"     : 220,
                           "neili"   : 5000,
                           "force"   : 350,
                           "gongxian": 1000,
                           "shen"    : 100000, ]));
                break;
        case "驕陽劈天" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyang-shengong/pi",
                           "name"    : "驕陽劈天",
                           "sk1"     : "jiuyang-shengong",
                           "lv1"     : 220,
                           "neili"   : 5000,
                           "force"   : 350,
                           "gongxian": 1000,
                           "shen"    : 100000, ]));
                break;
        case "金陽破嶺" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyang-shengong/po",
                           "name"    : "金陽破嶺",
                           "sk1"     : "jiuyang-shengong",
                           "lv1"     : 220,
                           "neili"   : 5000,
                           "force"   : 350,
                           "gongxian": 1000,
                           "shen"    : 100000, ]));
                break;
        case "魔光日無極" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyang-shengong/ri",
                           "name"    : "魔光日無極",
                           "sk1"     : "jiuyang-shengong",
                           "lv1"     : 220,
                           "neili"   : 5000,
                           "force"   : 350,
                           "gongxian": 1000,
                           "shen"    : 100000, ]));
                break;
        case "駕御兵器" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_learn/jiuyang-shengong/enable_weapon",
                           "name"    : "駕御兵器",
                           "sk1"     : "jiuyang-shengong",
                           "lv1"     : 220,
                           "neili"   : 5000,
                           "force"   : 350,
                           "gongxian": 1000,
                           "shen"    : 100000, ]));
                break;
        case "大挪移" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/qiankun-danuoyi/yi",
                           "name"    : "大挪移",
                           "sk1"     : "qiankun-danuoyi",
                           "lv1"     : 200,
                           "neili"   : 5000,
                           "force"   : 200,
                           "gongxian": 1000,
                           "shen"    : 100000, ]));
                break;
        case "挪轉乾坤" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/qiankun-danuoyi/nuozhuan",
                           "name"    : "挪轉乾坤",
                           "sk1"     : "qiankun-danuoyi",
                           "lv1"     : 1000,
                           "neili"   : 5000,
                           "force"   : 1000,
                           "gongxian": 3000,
                           "reborn"  : 1,
                           "shen"    : 100000, ]));
                break;
        default:
                return 0;
        }
}

mixed ask_jiuyang()
{
        mapping fam;
        object ob;
        object me = this_player();

        if( !(fam=query("family", this_player())) || fam["family_name"] != "明教" )
                return RANK_D->query_respect(this_player()) + "與本教素無來往，不知此話從何談起？";

        if( !query_temp("marks/義父", this_player()) )
                return "你如果能幫我找到我的義父謝遜，那還可以考慮！";

        if( query("jiuyang/zhang", me) )
                return "你知道“經在油中”此話的含義了麼？";

        set("jiuyang/zhang", 1, me);
        return "想當年太師傅在少林曾聽聞昆侖派“昆侖三聖”何足道帶話到少林說“經在油中”，\n"+
               "不知道此話有何含義。";
}

/*
mixed ask_ling()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player()) )
                || fam["family_name"] != "明教")
                return RANK_D->query_respect(this_player()) +
                       "與本教素無來往，要這個是何居心？\n";

        if (this_player()->query_skill("shenghuo-ling", 1) < 100)
                return "你的聖火令法造詣太淺，要去也沒用的！\n";

        if (this_player()->query_skill("qiankun-danuoyi", 1) < 100)
                return "你的乾坤大挪移心法造詣太淺，聖火令給你我可不太放心！\n";

   ob = new("/d/mingjiao/obj/tieyanling");
        ob->move(this_player());
        message_vision("$N要得一面鐵燄令。\n",this_player());

        return "好吧，憑這面鐵燄令，你可自由向你的尊長挑戰。";
}
*/
mixed ask_ling()
{
        mapping family, skl;
        string *sname;
        object ob;
        int i;

        if( !(family=query("family", this_player())) || family["family_name"] != "明教" )
                return RANK_D->query_respect(this_player()) + "與本教素無來往，不知此話從何談起？";

        skl = this_player()->query_skills();
        sname  = sort_array( keys(skl), (: strcmp :) );

        for(i=0; i<sizeof(skl); i++)
        {
                if (skl[sname[i]] < 30)
                return RANK_D->query_respect(this_player()) +
                "功力不夠，不能領取鐵燄令。";
        }

        ob = new("d/mingjiao/obj/tieyanling");
        ob->move(this_player());
        message_vision("$N要得一面鐵燄令。\n",this_player());

        return "好吧，憑這面鐵燄令，你可自由向你的尊長挑戰。";

}

mixed ask_qiankun()
{
        object obj,me;
        me = this_player();

        if (this_player()->query_skill("shenghuo-shengong", 1)<100)
        {
                command("say " + RANK_D->query_respect(me) + "似乎聖火神功修為還不夠。");
                return 1;
        }
        if( query("combat_exp", this_player())<800000 )
        {
                command("say " + RANK_D->query_respect(me) + "似乎實戰經驗還不夠。");
                return 1;
        }
        if (this_player()->query_skill("force", 1) < 100)
        {
                command("say " + RANK_D->query_respect(me) + "似乎基本內功修為還不夠。");
                return 1;
        }
              if( query_temp("marks/挪移", this_player()) )
              {
                command("say 你不是剛剛才問過嗎？");
                return 1;
        }
        else
        {
                command("say 好吧，我就準許你進入秘室修煉乾坤大挪移。以後你要發揚光大明教。");
                // command("say 你到張中前輩那裡去就說是我準許的。");
                command("pat"+query("id", me));
                command("addoil"+query("id", me));
                set_temp("marks/挪移", 1, this_player());
                return 1;
        }

}

int ask_hu_quest()
{
        object me = this_player();
        if( query_temp("hu/quest1", me) != 2 )
        {
                command("say 怎麼突然提起他做什麼？");
                return 1;
        } else
        {
                command("say 原來胡先生還健在？");
                command("jump");
                command("say 我幫胡先生狠狠的罵了這個家伙一頓，而且他也自己中了自己的毒死了。");
                command("say 胡先生若是能親自看到，想必會很高興。");
                set_temp("hu/quest1", 3, me);
                return 1;
        }
}

int ask_hu()
{
        object me = this_player();

        if( !query_temp("hu/quest2", me) )
        {
                command("say 胡青牛先生號稱蝶谷醫仙，醫術一流，不過脾氣有點怪。");
                return 1;
        } else
        {
                command("ah");
                command("say 真是對不住，最近明教將要起事，我實在抽不出身。");
                command("say 麻煩了你三番兩此幫忙胡先生送口信。");
                command("say 請告訴他，無忌安好，並且請他小心身子。");
                command("say 這個鐵炎令你拿去，讓胡先生看看吧。");
                me->apply_condition("hu_quest", 5);
                new("/d/mingjiao/obj/tieyan")->move(me);
                return 1;
        }
}

int ask_hdg()
{
        object me = this_player();
        command("say 蝴蝶谷是胡青牛神醫的居所。");
        command("say 那在長江南岸附近，跟著蝴蝶就能找到了。");
        set_temp("hdg", 1, me);
        return 1;
}

string ask_qishang()
{
        mapping fam;
        object me = this_player();

        fam=query("family", me);
        if (! fam || fam["family_name"] != "明教" || fam["master_name"] != "張無忌")
                return "嗯....這我可不清楚，你最好問問別人吧。";

        if( query("can_perform/xiexun/qishang", me) )
                return "咦，義父不是已經把七傷拳的拳理教了你嗎？\n";

        if( query_temp("marks/七傷", me) )
                return "咦，我不是叫你出海去拜訪我義父謝獅王了嗎？\n";

        // me->set("luopan/bhd");
        set_temp("marks/七傷", 1, me);

        command("hmm");
        command("whisper"+query("id", me)+"我義父在極北冰火島上，大概位于黃道帶以北九百五十、以東二百個距離的地方。");
        // new("/d/mingjiao/obj/luopan")->move(this_object());
        // command("give luo pan to " + me->query("id"));
        return "這七傷拳，是當年我義父親自傳我的絕技，你如果真有信心和毅力，就出海去拜訪我義父吧！\n";
}

string ask_book()
{
        mapping fam;
        object me = this_player();

        fam=query("family", me);
        if (! fam || fam["family_name"] != "明教" || fam["master_name"] != "張無忌")
                return "我有一本太極拳經，是當年我武當的太師父送給我的。";

        set_temp("marks/秘1", 1, me);
        return "我有一本太極拳經，是當年我武當的太師父送給我的，現我交張散人了。";
}

void destroy(object ob)
{
        if (ob) destruct(ob);
}

void restart(object me, object ob)
{
        if( query("mj_jiaozhu", me) )
                delete("mj_jiaozhu", me);

        if (ob) destruct(ob);
}

/*
void unconcious()
{
        die();
}
*/
