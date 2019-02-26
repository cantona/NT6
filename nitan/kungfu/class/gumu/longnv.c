// This program is a part of NITAN MudLIB

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

#include <ansi.h>
#include "gumu.h"

#define YINSUO    "/clone/lonely/yinsuo"
#define XINJING   "/clone/book/gumu"

string ask_yunv();
string ask_zhen();
string ask_me();

void create()
{
        object ob;

        set_name("小龍女", ({ "xiao longnv", "xiao", "longnv" }));
        set("gender", "女性");
        set("age", 22);
        set("long", @LONG
她一生愛穿白衣，當真如風拂玉樹，雪裹瓊苞，
兼之生性清冷，實當得起“冷浸溶溶月”的形
容。
LONG);
        set("attitude", "friendly");
        set("str", 21);
        set("int", 30);
        set("con", 25);
        set("dex", 26);
        set("per", 29);
        set("shen_type", 1);

        set("qi", 5000);
        set("max_qi", 5000);
        set("jing", 6000);
        set("max_jing", 6000);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 100);

        set("combat_exp", 3000000);

        set_skill("force", 620);
        set_skill("suxin-jue", 620);
        set_skill("yunv-xinjing", 620);
        set_skill("sword", 620);
        set_skill("yunv-jian", 620);
        set_skill("quanzhen-jian", 600);
        set_skill("whip", 620);
        set_skill("yinsuo-jinling", 620);
        set_skill("dodge", 600);
        set_skill("yunv-shenfa", 600);
        set_skill("parry", 600);
        set_skill("unarmed", 600);
        set_skill("meinv-quan", 600);
        set_skill("strike", 620);
        set_skill("tianluo-diwang", 620);
        set_skill("zuoyou-hubo", 660);
        set_skill("literate", 600);
        set_skill("throwing", 620);
        set_skill("yufeng-zhen", 620);
        set_skill("hebi-jianzhen", 620);
        set_skill("martial-cognize", 600);
        set_skill("yunv-xinfa", 600);
        set_skill("medical", 600);
        set_skill("qufeng", 600);
        set_skill("array", 600);
        set_skill("taishang-wangqing", 600);

        map_skill("force", "yunv-xinfa");
        map_skill("whip", "yinsuo-jinling");
        map_skill("sword", "yunv-jian");
        map_skill("dodge", "yunv-shenfa");
        map_skill("parry", "meinv-quan");
        map_skill("unarmed", "meinv-quan");
        map_skill("strike", "tianluo-diwang");
        map_skill("throwing", "yufeng-zhen");

        prepare_skill("strike", "tianluo-diwang");
        prepare_skill("unarmed", "meinv-quan");

        create_family("古墓派", 3, "弟子");

        set("yfzhen_count", 3);

        set("inquiry", ([
                "過兒" : "他就在正廳啊。",
                "劍"   : (: ask_me :),
                "玉女劍法" : "玉女劍法和全真劍法合璧，天下無敵！\n",
                "古墓派" : "我的林祖師爺爺本來和重陽先師是一對璧人，可是...\n",
                "玉蜂針"   : (: ask_zhen :),
                "玉女心經祕籍": (: ask_yunv :),
        ]));

        set_temp("apply/attack", 150);
        set_temp("apply/defense", 150);
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 600);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: command("perform strike.wang and unarmed.you") :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: perform_action, "whip.feng twice" :),
        }) );

        set("master_ob",4);
        set("master_ob",3);
        setup();
        if (clonep())
        {
                ob = find_object(YINSUO);
                if (! ob) ob = load_object(YINSUO);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                } else
                {
                        ob = new("/clone/weapon/changbian");
                        ob->move(this_object());
                        ob->wield();
                }
        }
        carry_object(__DIR__"obj/shunvjian")->wield();
        carry_object("/clone/cloth/baipao")->wear();

}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob) )
                return;

        if( query("per", ob)<20 )
        {
                command("say 尊容實在不敢恭維，我看你還是算了吧。\n");
                return;
        }

        command("say 好吧，我就收下你這個徒兒了。\n");
        command("recruit "+query("id", ob));
}

string ask_yunv()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || 
                fam["family_name"] != "古墓派")
                return RANK_D->query_respect(this_player()) +
                "與本派毫無瓜葛，何以問起本派的心經？";
        if (query("book_count") < 1)
                return "你來晚了，本派的玉女心經已經被人取走了。";
        addn("book_count", -1);
        ob = new("/clone/book/yunvjing1");
        ob->move(this_player());
        return "好吧，這本「玉女心經」你拿回去好好研讀。";
}

string ask_zhen()
{
        object me;
        object ob;
        mapping fam;

        me = this_player();

        if( !(fam=query("family", me)) || fam["family_name"] != "古墓派" )
                return RANK_D->query_respect(me) + "與本派毫無瓜葛，何以問"
                "起本派暗器？\n";

        if (me->query_skill("yufeng-zhen", 1) < 100)
                return RANK_D->query_respect(me) + "的玉蜂針手法火候還不到家"
                "，拿了玉蜂針也沒有什麼用。\n";

        if (query("yfzhen_count") < 1)
                return "你來晚了，我手頭的玉蜂針已經發完了。\n";

        addn("yfzhen_count", -1);

        message_vision(HIY "$N拿出一根玉蜂針遞給$n。\n" NOR, this_object(), me);

        ob = new("/d/gumu/obj/yufeng-zhen");
        ob->move(me, 1);

        return "好吧，這根玉蜂針你先拿去用吧。\n";
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

        case "銀索金鈴" :
                return MASTER_D->give_item(me, this_object(),
                        ([ "item"    : YINSUO,
                           "master"  : 1,
                           "sk1"     : "yinsuo-jinling",
                           "lv1"     : 150, ]));
                break;

        case "千姿百媚" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yunv-jian/mei",
                           "name"    : "千姿百媚",
                           "sk1"     : "yunv-jian",
                           "lv1"     : 35,
                           "dodge"   : 30,
                           "gongxian": 50, ]));
                break;

        case "隔空點穴" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yinsuo-jinling/dian",
                           "name"    : "隔空點穴",
                           "sk1"     : "yinsuo-jinling",
                           "lv1"     : 70,
                           "force"   : 90,
                           "gongxian": 260, ]));
                break;

        case "玉女絕情" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/meinv-quan/jue",
                           "name"    : "玉女絕情",
                           "sk1"     : "meinv-quan",
                           "lv1"     : 35,
                           "dodge"   : 30,
                           "gongxian": 50, ]));
                break;

        case "無影針" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yufeng-zhen/ying",
                           "name"    : "無影針",
                           "sk1"     : "yufeng-zhen",
                           "lv1"     : 90,
                           "force"   : 100,
                           "gongxian": 300, ]));
                break;

        case "雙劍合璧" :
        case "雙劍合壁" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yunv-jian/he",
                           "name"    : "雙劍合壁",
                           "sk1"     : "yunv-jian",
                           "lv1"     : 130,
                           "force"   : 120,
                           "dodge"   : 100,
                           "gongxian": 660, ]));

                break;

        case "連環劍術" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yunv-jian/lian",
                           "name"    : "連環劍術",
                           "sk1"     : "yunv-jian",
                           "lv1"     : 130,
                           "gongxian": 660, ]));

                break;

        case "天羅地網" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tianluo-diwang/wang",
                           "name"    : "天羅地網",
                           "sk1"     : "tianluo-diwang",
                           "lv1"     : 130,
                           "sk2"     : "dodge",
                           "lv2"     : 100,
                           "gongxian": 660, ]));

                break;

        default:
                return 0;
        }
}

string ask_me()
{
        object ob;

        if (query("count") < 1)
                return "現在我手頭也沒有了。";

        addn("count", -1);
        //ob=new("/d/gumu/npc/obj/junzijian");
        ob=new(__DIR__"obj/junzijian");
        ob->move(this_player(), 1);
        return "這柄君子劍就送給你吧。";
}

void reset()
{
        set("yfzhen_count", 4 + random(2));
}

 /*
void unconcious()
{
        die();
}
*/
