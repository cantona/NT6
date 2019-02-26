// This program is a part of NT MudLIB
// xie.c 謝遜

#include <ansi.h>
#include "mingjiao.h"

inherit NPC;
inherit F_MASTER;

string ask_me();
string ask_dao();
string ask_boat();

void create()
{
        object ob;
        set_name("謝遜",({"xie xun","xie","xun"}));
        set("title", HIG "明教" HIY "金毛獅王" NOR);

        set("long", "他就是明教的四大護法之一的金毛獅王。\n"+
                    "他身材魁偉異常，滿頭金髮散披肩頭。但雙目已瞎。\n"+
                    "在你面前一站，威風凜凜，真如天神一般。\n");
        set("age", 56);
        set("attitude", "peaceful");
        set("shen", -13000);
        set("str", 30);
        set("per", 16);
        set("int", 29);
        set("con", 35);
        set("dex", 27);
        set("max_qi", 2500);
        set("max_jing", 2000);
        set("eff_jingli", 2000);
        set("jiali", 70);
        set("combat_exp", 1350000);
        set("level", 40);

        set_skill("cuff",460);
        set_skill("dodge",460);
        set_skill("force", 460);
        set_skill("blade",460);
        set_skill("hand", 460);
        set_skill("literate",410);
        set_skill("qingfu-shenfa", 460);
        set_skill("qishang-quan",480);
        set_skill("shenghuo-shengong", 460);
        set_skill("pili-shou", 460);
        set_skill("parry", 460);
        set_skill("lieyan-dao",460);
        set_skill("martial-cognize", 300);

        map_skill("force", "shenghuo-shengong");
        map_skill("dodge", "qingfu-shenfa");
        map_skill("cuff", "qishang-quan");
        map_skill("parry", "qishang-quan");
        map_skill("blade", "lieyan-dao");
        map_skill("hand", "pili-shou");

        prepare_skill("cuff","qishang-quan");

        set("chat_chance_combat", 200);
        set("chat_msg_combat", ({
                (: command("perform cuff.shang") :),
                (: command("perform cuff.fei") :),
        }) );

        set("inquiry", ([
                 "張無忌"  : "他是我的義子，我已很久沒有見到他了。",
                 "七傷拳經": (: ask_me :),
                 "屠龍刀": (: ask_dao :),
                 "船"    : (: ask_boat :),
                 "船舶"  : (: ask_boat :),
                 "造船"  : (: ask_boat :),
                 "中原"  : (: ask_boat :),
                 "成昆"  : "他就是我那狗賊師傅，他殺了我一家四口，此仇不共戴天！",
        ]));

        create_family("明教", 36, "護法法王");

        set("master_ob",5);
        setup();

        // carry_object("/d/mingjiao/obj/tulong-dao")->wield();
        carry_object("/clone/weapon/tulongdao")->wield();
        carry_object("/d/mingjiao/obj/xiongpi")->wear();
}

void attempt_apprentice(object ob)
{
        command("say 老夫不收弟子。");
        command("say 這位"+RANK_D->query_respect(ob)+"還是請回吧。");
        return;
}

int recognize_apprentice(object ob, string skill)
{
        if( query("can_learn/xiexun/qishang-quan", ob) && 
            skill == "qishang-quan")
                return 1;

        if( query("can_learn/xiexun/qishang-quan", ob) && 
            skill == "cuff")
                return 1;

        if( query("can_learn/xiexun/qishang-quan", ob) && 
            skill == "hand")
                return 1;

        if( query("can_learn/xiexun/qishang-quan", ob) && 
            skill == "pili-shou")
                return 1;

        if( !query("can_learn/xiexun/qishang-quan", ob) )
                return -1;

        command("say 你到底學不學我的七傷拳？不想學就快滾！");
        return -1;
}

string ask_me()
{
        mapping fam;
        object me = this_player();

        if( !(fam=query("family", me)) || fam["family_name"] != "明教" )
                return "七傷拳經？沒聽説過。";

        if (fam["master_name"] != "張無忌")
                return RANK_D->query_respect(me) + "還是請回吧，你説的是崆峒派的絕技，我怎麼會知道？";

        if( query("can_lean/xiexun/qishang-quan", me) )
                return "我不是答應傳了你這拳經了嗎？怎麼還要問！";

        if( !query_temp("marks/七傷", me) )
                return "我這七傷拳經除了我義子，不傳外人！";

        command("consider");
        command("say 無忌這孩子，怎麼可將七傷拳傳予他人呢！");
        command("say 也罷，無忌既然讓你來到這裏，我就傳了你吧。");
        set("can_learn/xiexun/qishang-quan", 1, me);
        delete_temp("marks/七傷", me);
        command("whisper"+query("id", me)+"五行之氣調陰陽，損心傷肺摧肝腸，藏離精失意恍惚，三焦齊逆兮魂魄飛揚！");
        return "你學完了就可以回去吧。";
}

string ask_boat()
{
        object me = this_player();

        if( !query("can_learn/xiexun/qishang-quan", me) )
                return "船？這極北冰火島離開中原萬里，哪來的船舶？";

        command("say 當年我幫義弟義妹他們在後山叢林中砍伐(chop)樹木，然後才搬到海邊造船(make)。");
        return "也不知道現在他們和我那無忌孩兒都怎麼樣了。";
}

string ask_dao()
{
        mapping fam;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "明教" )
                return RANK_D->query_respect(this_player())+"與本教素無來往，不知此話從何談起？";

        if (present("tulong dao", this_object()))
        {
                command("wield dao");
                command("say 武林至尊，寶刀屠龍，號令天下，莫敢不從，倚天不出，誰與爭鋒。");
                write("\n謝遜棒着屠龍寶刀，低頭冥思刀口之祕。\n\n");
                set_temp("xie_tld", 1, this_player());
                return "不尋到寶刀中之祕，我之大仇如何得報？唉......";
        } else
                return "武林至尊，寶刀屠龍，號令天下，莫敢不從！";
}

int accept_object(object who, object ob)
{
        object obj;
        object me = this_object();

        if ((! ob->is_head() && ! ob->is_corpse()) ||
            !stringp(query("owner_id", ob)) || 
          query("owner_id", ob) != "cheng kun" )
        {
                command("say 老夫對這樣東西沒什麼興趣……");
                return 0;
        }

        command("say 啊……成昆的人頭！ 成昆的人頭！");
        command("chat 哈哈哈！……成昆的人頭！ 成昆的人頭！");
        call_out("destroy", 1, ob);

        if( query("killed_by", ob) != query("id", who) )
        {
                command("say 但他好像不是你殺的吧？你是怎麼得到這塊人頭的？");
                return 1;
        }
          if( query_temp("xie_tld", who) && present("tulong dao",me) )
        {
                command("say 你讓我大仇得報，這把刀就算我的謝禮，只可惜不能手刃了那惡賊。");
                command("unwield dao");
                  command("give tulong dao to "+query("id", who));
                delete_temp("xie_tld", who);
                return 1;
        } else
        {
                command("say 你讓我大仇得報，我這裏只有我的金毛送給你了，只可惜不能手刃了那惡賊。");
                obj = new ("/d/mingjiao/obj/jinmao");
                obj->move(this_player());
                return 1;
        }
}

void destroy(object ob)
{
        destruct(ob);
        return;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "天地混元" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/pili-shou/hun",
                           "name"    : "天地混元",
                           "sk1"     : "pili-shou",
                           "lv1"     : 140,
                           "force"   : 240,
                           "gongxian": 550,
                           "shen"    : 48000, ]));
                break;

        case "魂魄飛揚" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/qishang-quan/fei",
                           "name"    : "魂魄飛揚",
                           "sk1"     : "qishang-quan",
                           "lv1"     : 140,
                           "neili"   : 2000,
                           "gongxian": 800,
                           "shen"    : 100000, ]));
                break;

        case "傷字訣" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/qishang-quan/shang",
                           "name"    : "傷字訣",
                           "sk1"     : "qishang-quan",
                           "lv1"     : 160,
                           "neili"   : 2200,
                           "gongxian": 800,
                           "shen"    : 100000, ]));
                break;

        case "天地混元" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/pili-shou/hun",
                           "name"    : "天地混元",
                           "sk1"     : "pili-shou",
                           "lv1"     : 160,
                           "neili"   : 2200,
                           "gongxian": 800,
                           "shen"    : 100000, ]));
                break;

        default:
                return 0;
        }
}
