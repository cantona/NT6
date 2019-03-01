// This program is a part of NITAN MudLIB
// limochou.c

#include <ansi.h>
#include "gumu.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

string ask_zhen();
int ask_me();

void create()
{
        object ob;
        set_name("李莫愁", ({ "li mochou", "li", "mochou" }));
        set("long", @LONG
她生得極為美貌，但冰冷的目光讓人不寒而立。
LONG);
        set("nickname", HIM "赤練仙子" NOR);
        set("gender", "女性");
        set("rank_info/respect", "道姑");
        set("age", 27);
        set("attitude","heroism");
        set("str", 30);
        set("dex", 35);
        set("con", 17);
        set("int", 25);
        set("shen_type", -1);

        create_family("古墓派", 3, "弟子");

        set_skill("unarmed", 220);
        set_skill("force", 220);
        set_skill("suxin-jue", 220);
        set_skill("yunv-xinjing", 220);
        set_skill("dodge", 220);
        set_skill("yunv-shenfa", 220);
        set_skill("qixing-bu", 220);
        set_skill("whip", 240);
        set_skill("yunzhou-fufa", 240);
        set_skill("sanwu-shou", 240);
        set_skill("strike", 220);
        set_skill("chilian-shenzhang", 220);
        set_skill("wudu-shenzhang", 220);
        set_skill("sword", 220);
        set_skill("yunv-jian", 220);
        set_skill("unarmed", 220);
        set_skill("meinv-quan", 220);
        set_skill("throwing", 240);
        set_skill("bingpo-shenzhen", 240);
        set_skill("literate", 220);
        set_skill("martial-cognize", 220);

        set("jiali", 150);

        map_skill("force", "yunv-xinjing");
        map_skill("strike", "wudu-shenzhang");
        map_skill("whip", "sanwu-shou");
        map_skill("dodge", "qixing-bu");
        map_skill("parry", "wudu-shenzhang");
        map_skill("sword", "yunv-jian");
        map_skill("throwing", "bingpo-shenzhen");
        map_skill("unarmed", "meinv-quan");
        set("combat_exp", 400000);

        set("max_qi", 6900);
        set("max_jing", 1400);
        set("neili", 5000);
        set("max_neili", 5000);

        prepare_skill("strike", "wudu-shenzhang");
        prepare_skill("unarmed", "meinv-quan");

        set("bingpo-zhen", 3);

        set("inquiry", ([
                "name" : "站遠點！",
                "here" : "我不是本地人，不知道。",
                "情" : "你如何能理解其中相思之苦、惆悵之意？",
                "陸展元" : "你問那個薄情的小畜生做什麼？",
                "何沅君" : (: ask_me :),
                "小龍女"     : "那是我的師妹。你問她想幹什麼？",
                "林朝英"     : "那是我的師祖，不該你問的你別問，小心我宰了你。",
                "冰魄銀針"   : (: ask_zhen :),
        ]));

        set_temp("apply/attack", 150);
        set_temp("apply/defense", 150);
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);
        set("chat_chance", 10);
        set("chat_msg", ({
                "李莫愁縱聲而歌，音調凄婉，歌道：「問世間，情是何物，直教生死相許？」\n",
                "李莫愁歌道：「天南地北雙飛客，老翅幾回寒暑？」\n",
                "李莫愁唱道：「歡樂趣，離別苦，就中更有痴兒女。」\n",
                "李莫愁唱道：「君應有語，渺萬裡層雲，千山暮雪，只影向誰去？」\n",
                "李莫愁詞意悲切，聲調更是哀怨，唱道：「橫汾路，寂寞當年簫鼓。荒煙依舊平楚。」\n",
                "李莫愁歌道：「招魂些何嗟及，山鬼自啼風雨。」\n",
                "李莫愁唱道：「天也妒，未信與，鶯兒燕子俱黃土。」\n",
                "李莫愁唱道：「千秋萬古，為留待騷人，狂歌痛飲，來訪雁丘處。」\n",
        }) );
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.huan" :),
                (: perform_action, "strike.shi" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set("master_ob",3);
        setup();
        carry_object("/d/quanzhou/obj/fuchen");
        carry_object("/d/wudang/obj/greenrobe")->wear();
        ob = new(__DIR__"obj/yinzhen");
        ob->set_amount(10);
        ob->move(this_object());
}

int do_look(string target)
{
        object me;

        me = this_player();

        if (! id(target))
                return notify_fail("你要看什麼？");

        if( query("gender", me) != "女性" )
        {
                message_vision(HIR "李莫愁大怒，喝道：我最恨你們這"
                               "些薄情的臭男人，去死吧！\n" NOR, me);
                kill_ob(this_player());
        }
        return 1;
}

int ask_me()
{
        object me;

        me = this_player();
        message("vision", HIY"李莫愁冷笑一聲：『我這就送你去見她』\n李莫愁決心殺死" + me->name() +"\n" NOR, environment(), this_object() );
        kill_ob(this_player());
        return 1;
}

void attempt_apprentice(object ob)
{
        object me = this_player();

        if (! permit_recruit(ob) )
                return;

        if( query("per", ob)<20 )
        {
                command("say 尊容實在不敢恭維，恐怕學不了玉女心法。\n");
        }

        if( query("shen", me)>-70000 )
        {
                command("heng");
                command("say 我李莫愁可不收心慈手軟的人做徒弟。");
                return;
        }

        if( query("combat_exp", me)<400000 )
        {
                command("heng");
                command("say 你這點能力怎能繼承我的衣砵？");
                return;
        }
        if ((int)me->query_skill("force") < 160)
        {
                command("say 要學我五毒神掌，得先將內功練紮實。");
                return;
        }

        if ((int)me->query_skill("strike", 1) < 120)
        {
                command("say 要學我的五毒神掌，需要精湛的掌法作基礎，"
                        "我看你在那上面下的工夫還不夠啊。");
                return;
        }

        command("nod");
        command("say 好吧，我就收下你這個徒弟了。");
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

        case "風魔舞" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yunzhou-fufa/feng",
                           "name"    : "風魔舞",
                           "sk1"     : "yunzhou-fufa",
                           "lv1"     : 50,
                           "gongxian": 50,
                           "shen"    : -75000, ]));
                break;

        case "寒冰針" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bingpo-shenzhen/bing",
                           "name"    : "寒冰針",
                           "sk1"     : "bingpo-shenzhen",
                           "lv1"     : 110,
                           "force"   : 140,
                           "gongxian": 400,
                           "shen"    : -80000, ]));
                break;

        case "無所不為" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/sanwu-shou/wei",
                           "name"    : "無所不為",
                           "sk1"     : "sanwu-shou",
                           "lv1"     : 60,
                           "gongxian": 300,
                           "shen"    : -80000, ]));
                break;

        case "赤心連環決" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/chilian-shenzhang/lian",
                           "name"    : "赤心連環決",
                           "sk1"     : "chilian-shenzhang",
                           "lv1"     : 110,
                           "force"   : 140,
                           "gongxian": 400,
                           "shen"    : -85000, ]));
                break;

        case "千幻神訣" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/wudu-shenzhang/huan",
                           "name"    : "千幻神訣",
                           "sk1"     : "wudu-shenzhang",
                           "lv1"     : 90,
                           "dodge"   : 140,
                           "gongxian": 500,
                           "shen"    : -90000, ]));
                break;

        case "無所不至" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/sanwu-shou/zhi",
                           "name"    : "無所不至",
                           "sk1"     : "sanwu-shou",
                           "lv1"     : 90,
                           "dodge"   : 100,
                           "gongxian": 400,
                           "shen"    : -95000, ]));
                break;

        case "無孔不入" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/sanwu-shou/kong",
                           "name"    : "無孔不入",
                           "sk1"     : "sanwu-shou",
                           "lv1"     : 120,
                           "force"   : 160,
                           "gongxian": 600,
                           "shen"    : -110000, ]));
                break;

        case "萬毒噬心" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/wudu-shenzhang/shi",
                           "name"    : "萬毒噬心",
                           "sk1"     : "wudu-shenzhang",
                           "lv1"     : 140,
                           "force"   : 180,
                           "gongxian": 800,
                           "shen"    : -120000, ]));
                break;
        default:
                return 0;
        }
}

string ask_zhen()
{
        object me;
        object ob;
        mapping fam;

        me = this_player();

        if( query("family/master_name", me) != "李莫愁" )
                return RANK_D->query_respect(me) + "與我毫無瓜葛，何以問"
                "起我的暗器？\n";

        if (me->query_skill("bingpo-zhen", 1) < 100)
                return RANK_D->query_respect(me) + "的冰魄神針手法火候還不到家"
                "，拿了冰魄銀針也沒有什麼用。\n";

        if (query("bingpo-zhen") < 1)
                return "你來晚了，我手頭的冰魄銀針已經發完了。\n";

        addn("bingpo-zhen", -1);

        message_vision(HIY "$N拿出一根" HIW "冰魄銀針" HIY "遞給$n。\n" NOR, this_object(), me);

        ob = new("/d/gumu/obj/bingpo-zhen");
        ob->move(me, 1);

        return "好吧，這根冰魄銀針你先拿去用吧。\n";
}

void reset()
{
        set("bingpo-zhen", 4 + random(2));
}
