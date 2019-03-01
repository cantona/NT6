#include <ansi.h>
#include "songshan.h"

#define CANYANG "/clone/lonely/canyang"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;
string ask_book();
string ask_book1();
void create()
{
        object ob;

        set_name("左冷禪", ({ "zuo lengchan", "zuo" }) );
        set("title", HIR"五岳劍派盟主"HIY"嵩山派第十三代掌門"NOR);
        set("gender", "男性");
        set("class", "swordsman");
        set("age", 55);
        set("attitude", "peaceful");
        set("str", 36);
        set("con", 33);
        set("dex", 30);
        set("int", 28);

        set("max_qi",5500);
        set("max_jing",2200);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 220);
        set("combat_exp", 1850000);
        set("shen_type", -1);

        set_skill("cuff", 600);
        set_skill("strike", 600);
        set_skill("sword", 600);
        set_skill("force", 600);
        set_skill("parry", 600);
        set_skill("dodge", 600);
        set_skill("lingxu-bu", 600);
        set_skill("songshan-jian", 600);
        set_skill("lingyun-jian", 600);
        set_skill("chuanyue-jian", 600);
        set_skill("jiuqu-jian", 600);
        set_skill("poyang-jian", 600);
        set_skill("songshan-xinfa", 600);
        set_skill("hanbing-zhenqi", 600);
        set_skill("hanbing-zhang", 600);
        set_skill("songshan-zhang", 600);
        set_skill("songshan-quan", 600);
        set_skill("literate", 600);
        set_skill("martial-cognize", 600);

        map_skill("force", "hanbing-zhenqi");
        map_skill("sword", "poyang-jian");
        map_skill("parry", "poyang-jian");
        map_skill("strike", "hanbing-zhang");
        map_skill("cuff", "songshan-quan");
        map_skill("dodge", "lingxu-bu");

        prepare_skill("strike", "hanbing-zhang");
        set("inquiry",([
                "秘籍"       : (: ask_book :),
                "掌譜"       : (: ask_book :),
                "大嵩陽掌譜" : (: ask_book :),
                "劍譜"       : (: ask_book1 :),
                "嵩山劍譜"   : (: ask_book1 :),
        ]));
        create_family("嵩山派", 13, "掌門");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.long" :),
                (: perform_action, "sword.xian" :),
                (: perform_action, "strike.heng" :),
                (: perform_action, "strike.han" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "freezing" :)
        }));

        set_temp("apply/attack", 100);
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob", 5);
        setup();

        if (clonep())
        {
                ob = find_object(CANYANG);
                if (! ob) ob = load_object(CANYANG);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                } else
                {
                        ob = new("/clone/weapon/changjian");
                        ob->move(this_object());
                        ob->wield();
                }
        }
        carry_object(__DIR__"obj/yellow-cloth")->wear();
}


void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)>-30000 )
        {
                command("say 我最看不慣你們這些狹義之士，你還是請回吧！");
                return;
        }

        if( query("combat_exp", ob)<360000 )
        {
                command("say 你現在經驗尚淺，還是多在江湖上走走吧。");
                return;
        }

        if ((int)ob->query_skill("songshan-jian", 1) < 160)
        {
                command("say 我嵩山劍派乃五岳劍派之一，最為重視劍法。");
                command("say 你的嵩山劍法還不夠熟練，下去練練再來吧。");
                return;
        }

        if ((int)ob->query_skill("songshan-xinfa", 1) < 160)
        {
                command("say 我嵩山劍派雖善用劍，但內功卻是御劍之本。");
                command("say 你是否還應該在嵩山心法上多下點功夫？");
                return;
        }

        command("haha");
        command("say 孺子可教，孺子可教。今日我就收下你吧。");
        command("say 你以後定要勤練武，揚我嵩山派雄風。");
        command("recruit "+query("id", ob));
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

        case "踏雪無痕" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/hanbing-zhang/heng",
                           "name"    : "踏雪無痕",
                           "sk1"     : "hanbing-zhang",
                           "lv1"     : 100,
                           "force"   : 160,
                           "gongxian": 550,
                           "shen"    : -32000, ]));
                break;

        case "極天寒掌" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/hanbing-zhang/han",
                           "name"    : "極天寒掌",
                           "sk1"     : "hanbing-zhang",
                           "lv1"     : 120,
                           "force"   : 200,
                           "gongxian": 750,
                           "shen"    : -48000, ]));
                break;

        case "神光再現" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/poyang-jian/xian",
                           "name"    : "神光再現",
                           "sk1"     : "poyang-jian",
                           "lv1"     : 100,
                           "dodge"   : 140,
                           "gongxian": 650,
                           "shen"    : -54000, ]));
                break;

        case "天外玉龍" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/poyang-jian/long",
                           "name"    : "天外玉龍",
                           "sk1"     : "poyang-jian",
                           "lv1"     : 120,
                           "force"   : 180,
                           "gongxian": 900,
                           "shen"    : -72000, ]));
                break;


        case "寒冰真氣" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/hanbing-zhenqi/freezing",
                           "name"    : "寒冰真氣",
                           "sk1"     : "hanbing-zhenqi",
                           "lv1"     : 80,
                           "force"   : 140,
                           "gongxian": 1500,
                           "shen"    : -93000, ]));
                break;

        case "殘陽寶劍" :
                return MASTER_D->give_item(me, this_object(),
                        ([ "item"    : CANYANG,
                           "master"  : 1,
                           "sk1"     : "songshan-jian",
                           "lv1"     : 120,
                           "gongxian": 500,
                           "shen"    : -20000, ]));
                break;
        default:
                return 0;
        }
}

string ask_book()
{
        object ob;

        if( query("family/family_name", this_player()) != "嵩山派" )
                return RANK_D->query_respect(this_player()) +
                "與本派毫無瓜葛，我派的武功典籍可不能交給你。";
        if (query("book_count") < 1) return "你來晚了，本派的秘籍不在此處。";
        addn("book_count", -1);
        ob = new("/clone/book/songyang-zhangpu");
        ob->move(this_player());
        command("rumor"+query("name", this_player())+"拿到大嵩陽掌譜啦。\n");
        return "好吧，這本「大嵩陽掌譜」你拿回去好好鑽研。";
}

string ask_book1()
{
        object ob;

        if( query("family/family_name", this_player()) != "嵩山派" )
                return RANK_D->query_respect(this_player()) +
                "與本派毫無瓜葛，我派的武功典籍可不能交給你。";
        if (query("book_count1") < 1) return "你來晚了，本派的秘籍不在此處。";
        addn("book_count1", -1);
        ob = new("/clone/book/sword_book4");
        ob->move(this_player());
        command("rumor"+query("name", this_player())+"拿到嵩山劍譜啦。\n");
        return "好吧，這本「嵩山劍譜」你拿回去好好鑽研。";
}
