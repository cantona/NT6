// This program is a part of NITAN MudLIB
// yue-buqun.c 岳不群

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

#include <ansi.h>
#include "qizong.h"

int  do_xunshan();
void check_weapon();
void unwield_weapon();

string ask_me();
string ask_feng();
string ask_zixia();

// 重載個人鑒定函數，保証做quest的時候是正義的quest
int is_bad() { return 0; }
int is_good() { return 1; }

void create()
{
        set_name("岳不群", ({ "yue buqun", "yue" }) );
        set("title", "華山派掌門");
        set("nickname", HIC "君子劍" NOR);
        set("gender", "男性");
        set("class", "swordsman");
        set("shen_type", 1);
        set("age", 55);
        set("long", "岳不群自幼執掌華山派，乃當今武林中一等一的高手。\n");
        set("attitude", "peaceful");
        set("str", 26);
        set("con", 30);
        set("dex", 30);
        set("int", 28);

        set("max_qi", 5200);
        set("max_jing", 2600);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 80);
        set("level", 30);
        set("combat_exp", 2400000);
        set("xunshan", 1);
        set("apprentice_available", 3);

        set("inquiry", ([
                "劍宗"           : (: ask_me :),
                "氣宗"           : (: ask_me :),
                "巡山"           : (: do_xunshan :),
                "風清揚"         : (: ask_feng :),
                "紫霞秘籍"       : (: ask_zixia :),
                "思過崖"         : "那是本派弟子修行思過之處。\n",
        ]));

        set_skill("cuff", 600);
        set_skill("strike", 600);
        set_skill("sword", 600);
        set_skill("blade", 600);
        set_skill("force", 600);
        set_skill("parry", 600);
        set_skill("dodge", 600);
        set_skill("literate", 600);
        set_skill("huashan-sword", 600);
        set_skill("fanliangyi-dao", 600);
        set_skill("huashan-neigong", 600);
        set_skill("zixia-shengong", 600);
        set_skill("huashan-quan", 600);
        set_skill("huashan-zhang", 600);
        set_skill("poyu-quan", 600);
        set_skill("hunyuan-zhang", 600);
        set_skill("huashan-shenfa", 600);
        set_skill("pixie-jian", 600);
        set_skill("zhengqi-jue", 600);
        set_skill("jianyi", 600);
        set_skill("martial-cognize", 600);

        map_skill("sword", "pixie-jian");
        map_skill("parry", "pixie-jian");
        map_skill("blade", "fanliangyi-dao");
        map_skill("force", "zixia-shengong");
        map_skill("cuff", "poyu-quan");
        map_skill("strike", "hunyuan-zhang");
        map_skill("dodge", "pixie-jian");

        prepare_skill("strike", "hunyuan-zhang");
        prepare_skill("cuff", "poyu-quan");

        set("no_teach", ([
                "pixie-jian"     : "哈哈！那是林家的家傳武功，"
                                   "我怎麼可能會呢？",
        ]));

        set_temp("apply/attack", 220);
        set_temp("apply/dodge", 220);
        set_temp("apply/parry", 200);
        set_temp("apply/damage", 150);
        set_temp("apply/unarmed_damage", 150);
        set_temp("apply/armor", 200);

        create_family("華山派", 13, "掌門");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.duo" :),
                (: perform_action, "sword.pi" :),
                (: perform_action, "sword.gui" :),
                (: perform_action, "strike.wuji" :),
                (: perform_action, "cuff.lei" :),
                (: perform_action, "cuff.po" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: check_weapon :),
        }));

        set("master_ob",4);
        setup();

        set("book_count", 1);
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/misc/pin");
}

void check_weapon()
{
        if (objectp(query_temp("weapon")))
                return;

        command("wield pin");
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: perform_action, "sword.duo" :),
                (: perform_action, "sword.pi" :),
                (: perform_action, "sword.gui" :),
        }));
        set("chat_chance", 120);
        set("chat_msg", ({
                (: unwield_weapon :),
        }));
}

void unwield_weapon()
{
        command("unwield pin");
        delete("chat_chance");
        delete("chat_msg");
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
                (: perform_action, "sword.cimu" :),
                (: perform_action, "sword.pi" :),
                (: perform_action, "sword.gui" :),
                (: check_weapon :),
        }));
}

void attempt_apprentice(object ob)
{
        if( query("apprentice_available") ) {
                if( find_call_out("do_recruit") != -1 )
                        command("say 慢著，一個一個來。");
                else
                        call_out("do_recruit", 2, ob);
        } else {
                command("say 老夫今天已經收了三個弟子，不想再收徒了。");
        }
}

void do_recruit(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("family/family_name", ob) == "華山劍宗" )
        {
                command("say 你既然你已經拜了劍宗，那麼有何必來拜我呢！");
                return;
        }

        if( query("gender", ob) == "女性" )
        {
                command("say 我不收女徒弟，你還是去找我師妹吧！");
                return;
        }

        if( query("shen", ob)<20000 )
        {
                command("say 你行俠仗義的事還做得不夠，我還不能收你！");
                return;
        }

        if (ob->query_skill("huashan-neigong", 1) < 140)
        {
                command("say 我華山派以修氣為主，你連本門內功都還不熟練，我不能收你！");
                return;
        }

        if (ob->query_skill("huashan-sword", 1) < 140)
        {
                command("say 你華山劍法還不夠熟練，下去多練習練習再來找我吧！");
                return;
        }

        command("say 好，好，好，很好。");
        command("say 今日我便收下你了，以後定要多行俠仗義，光大我華山派！");
        command("recruit "+query("id", ob));
        if( query("class", ob) != "swordsman" )
                set("class", "swordsman", ob);

}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
        addn("apprentice_availavble", -1);
}

void reset()
{
        set("apprentice_available", 3);
}

int do_xunshan()
{
        object me = this_player();
        string date;

        date = NATURE_D->game_time();
        sscanf(date, "%s日%*s刻", date);

        if( query_temp("xunshan", me) )
        {
               if( !query_temp("xunshan/chaoyang", me) )
               {
                        message_vision("$N對著$n說：你朝陽峰沒去看看？"
                                       "這算巡的什麼山？\n", this_object(), me);
                        return 1;
               }
               if( !query_temp("xunshan/lianhua", me) )
               {
                        message_vision("$N對著$n說：你蓮花峰沒去看看？"
                                       "這算巡的什麼山？\n", this_object(), me);
                        return 1;
               }
               if( !query_temp("xunshan/yuntai", me) )
               {
                        message_vision("$N對著$n說：你雲台峰沒去看看？這算"
                                       "巡的什麼山？\n", this_object(), me);
                        return 1;
               }
               if( !query_temp("xunshan/sheshen", me) )
               {
                        message_vision("$N對著$n說：你怎麼沒去舍身崖？這算"
                                       "巡的什麼山？\n", this_object(), me);
                        return 1;
               }
               if( !query_temp("xunshan/siguo", me) )
               {
                        message_vision("$N對著$n說：你到了思過崖去了？這算"
                                       "巡的什麼山？\n", this_object(), me);
                        return 1;
               }
               if( !query_temp("xunshan/yunu", me) )
               {
                        message_vision("$N對著$n說：你到玉女峰後面華山小築"
                                       "去看過了？這算巡的什麼山？\n",
                                       this_object(), me);
                        return 1;
                }
                message_vision("$N對著$n說：不錯，辛苦了。你這就去"
                               "休息去吧。\n", this_object(), me);
                delete_temp("xunshan", me);
                addn("combat_exp", 100+random(100), me);
               addn("family/gongji", 8+random(4), me);
                  if( query("potential", me)>me->query_potential_limit() )
                addn("potential", 1, me);
else
                addn("potential", 40+random(20), me);
                return 1;
        }
        else
        {
               if (query("xunshan") == date)
               {
                        message_vision("$N對著$n說：今天已經有人巡山"
                                     "去了。你明天再來吧。\n", this_object(), me);
                        return 1;
               }
               if( query("family/family_name", me) != "華山派" )
               {
                        message_vision("$N對著$n大喝一聲：本派弟子才能"
                                     "巡山。你是哪來的姦細？\n", this_object(), me);
                        return 1;
               }
               else
               {
                        set("xunshan", date);
                        message_vision("$N對著$n說：本派弟子例當巡山。你，很好，很"
                                       "好！今天就去巡山吧。\n",
                                       this_object(), me);
                        set_temp("xunshan/start", 1, me);
                        set_temp("xunshan/time", time(), me);
                        return 1;
               }
        }
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

        case "奪命連環三仙劍" :
                /*
                if( query("max_neili", me)>100000 || me->query_skill("force")>405 )
                {
                      command("shake");
                      command("say 劍宗以劍術為主，氣為次！你的內功修為已入了氣宗歧途，再不能修煉劍宗劍術。");
                      return 1;
                }
                */
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huashan-sword/xian",
                           "name"    : "奪命連環三仙劍",
                           "sk1"     : "huashan-sword",
                           "lv1"     : 160,
                           "gongxian": 1000,
                           "sk2"     : "dodge",
                           "lv2"     : 160, ]));
                break;

        case "華岳三神峰" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/fanliangyi-dao/sanshen",
                           "name"    : "華岳三神峰",
                           "sk1"     : "fanliangyi-dao",
                           "lv1"     : 100,
                           "sk2"     : "force",
                           "lv2"     : 140,
                           "neili"   : 2000,
                           "gongxian": 1000,
                           "shen"    : 24000, ]));
                break;

        case "混元無極" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/hunyuan-zhang/wuji",
                           "name"    : "混元無極",
                           "sk1"     : "hunyuan-zhang",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 600,
                           "neili"   : 1400,
                           "shen"    : 28000, ]));
                break;

        case "封閉手" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/poyu-quan/feng",
                           "name"    : "封閉手",
                           "sk1"     : "poyu-quan",
                           "lv1"     : 60,
                           "force"   : 150,
                           "gongxian": 400,
                           "shen"    : 30000, ]));
                break;

        case "雷動九天" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/poyu-quan/lei",
                           "name"    : "雷動九天",
                           "sk1"     : "poyu-quan",
                           "lv1"     : 120,
                           "gongxian": 400,
                           "shen"    : 40000, ]));
                break;

        case "破石一擊" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/poyu-quan/po",
                           "name"    : "破石一擊",
                           "sk1"     : "poyu-quan",
                           "lv1"     : 140,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 600,
                           "shen"    : 60000, ]));
                break;

        case "劍掌五連環" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huashan-sword/lian",
                           "name"    : "劍掌五連環",
                           "sk1"     : "huashan-sword",
                           "lv1"     : 140,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 600,
                           "shen"    : 60000, ]));
                break;

        case "截手式" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huashan-sword/jie",
                           "name"    : "截手式",
                           "sk1"     : "huashan-sword",
                           "lv1"     : 140,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 600,
                           "shen"    : 60000, ]));
                break;

        case "劍芒" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huashan-sword/mang",
                           "name"    : "劍芒",
                           "sk1"     : "huashan-sword",
                           "lv1"     : 140,
                           "sk2"     : "sword",
                           "lv2"     : 120,
                           "gongxian": 600,
                           "shen"    : 60000, ]));
                break;

        default:
                return 0;
        }
}

string ask_me()
{
        object me = this_player();
        mapping myfam;
        myfam=query("family", me);

        if (! myfam || myfam["family_name"] != "華山派")
                return "咱們豪無淵源，你問這事幹嘛？\n";

        message_sort(HIW "\n$N" HIW "指著身後的匾額，語重心長地說道："
                     "“華山不幸曾分為氣劍二宗。咱們氣宗奉氣為主，以劍"
                     "為輔，以氣運劍，無堅不摧。而氣宗則倒行逆施重劍"
                     "輕氣。二宗各持己見，終于水火不容，同門操戈！華"
                     "山因此式微。你即入我門，盼你能潔身自愛，重振華"
                     "山！記得當年匾額上寫的是「劍氣沖霄」，結果劍宗"
                     "雖劍路縱橫，變化無方，可仍然敗在我宗「紫霞神功」"
                     "之下，數十年來不復再現，實異不勝正也。”\n" NOR,
                     this_object(), me);
        return "切記！切記！\n";
}

string ask_feng()
{
        say("岳不群的臉色突然便得很難看，皺著眉頭。\n");
        return "他是本門的一個前輩，一向不過問本門事務，我也不清楚他的下落。\n";
}

string ask_zixia()
{
        mapping fam;
        object me;

        me = this_player();
        fam=query("family", me);

        if (! fam || fam["family_name"] != "華山派")
                return RANK_D->query_respect(me) + "與本派素無來往，不知此話從何談起？\n";

        set_temp("hs/askzixia", 1, me);
        return "紫霞秘籍乃我華山至寶，前段時間不知道流落何處了。你去問問你二師兄吧。\n" ;
}

/*
void unconcious()
{
        die();
}

*/
