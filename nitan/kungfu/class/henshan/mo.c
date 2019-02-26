#include <ansi.h>
#include "henshan.h"

#define ZHENYUE "/clone/lonely/zhenyue"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

mixed ask_jian();

void create()
{
        object ob;
        set_name("莫大", ({ "mo da", "mo", "da" }));
        set("nickname", HIW "瀟湘夜雨" NOR);
        set("gender", "男性");
        set("class", "swordman");
        set("attitude", "peaceful");
        set("shen_type", 1);

        set("age", 55);
        set("str", 28);
        set("con", 26);
        set("int", 28);
        set("dex", 28);
        set("max_qi", 5000);
        set("max_jing", 7000);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 200);
        set("combat_exp", 7000000);

        set_skill("force", 640);
        set_skill("henshan-xinfa", 640);
        set_skill("zhenyue-jue", 640);
        set_skill("dodge", 640);
        set_skill("henshan-shenfa", 640);
        set_skill("cuff", 640);
        set_skill("henshan-quan", 640);
        set_skill("sword", 660);
        set_skill("henshan-jian", 660);
        set_skill("tianzhu-jian", 660);
        set_skill("zigai-jian", 660);
        set_skill("furong-jian", 660);
        set_skill("shilin-jian", 660);
        set_skill("strike", 640);
        set_skill("biluo-zhang", 640);
        set_skill("liuyun-zhang", 640);
        set_skill("parry", 640);
        set_skill("literate", 640);
        set_skill("tanqin-jifa", 700);
        set_skill("xiaoxiang-yeyu", 700);
        set_skill("martial-cognize", 620);

        map_skill("strike", "liuyun-zhang");
        map_skill("cuff", "henshan-quan");
        map_skill("sword", "shilin-jian");
        map_skill("force", "zhenyue-jue");
        map_skill("dodge", "henshan-shenfa");
        map_skill("parry", "shilin-jian");
        map_skill("tanqin-jifa", "xiaoxiang-yeyu");

        prepare_skill("strike", "liuyun-zhang");

        set("inquiry", ([
                "鎮嶽尚方" : (: ask_jian :),
                "寶劍" : (: ask_jian :),
                "祝融劍法" : "本門劍法之一的祝融劍法，自師尊華山一役後便失傳了。",
        ]));

        create_family("衡山派", 13, "掌門");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.luo" :),
                (: perform_action, "strike.pai" :),
                (: perform_action, "strike.die" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/attack", 100);
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",5);
        setup();

        if (clonep())
        {
                ob = find_object(ZHENYUE);
                if (! ob) ob = load_object(ZHENYUE);
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
        carry_object("/clone/cloth/cloth")->wear();
        set_temp("handing", carry_object("/d/henshan/npc/obj/huqin"));
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<40000 )
        {
                command("say 我衡山劍派乃是堂堂名門正派，對弟子要求嚴格。");
                command("say 你在這俠義與德行方面是否還做得不夠？");
                return;
        }

        if( query("combat_exp", ob)<700000 )
        {
                command("say 你現在經驗尚淺，還是多在江湖上走走吧。");
                return;
        }

        if ((int)ob->query_skill("henshan-jian", 1) < 120)
        {
                command("say 我衡山乃五嶽劍派之一，最為重視劍法。");
                command("say 你的衡山劍法還不夠熟練，下去練練再來吧。");
                return;
        }

        if ((int)ob->query_skill("force") < 180)
        {
                command("say 我衡山劍派雖善用劍，但內功卻是御劍之本。");
                command("say 你是否還應該在內功心法上多下點功夫？");
                return;
        }

        command("nod");
        command("say 念你平時刻苦努力，今日我就收下你吧。");
        command("recruit "+query("id", ob));
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

        case "紫蓋迴翔" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/zigai-jian/hui",
                           "name"    : "紫蓋迴翔",
                           "sk1"     : "zigai-jian",
                           "lv1"     : 120,
                           "force"   : 150,
                           "dodge"   : 120,
                           "gongxian": 200,
                           "shen"    : 15000, ]));
                break;

        case "落英紛飛" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shilin-jian/luo",
                           "name"    : "落英紛飛",
                           "sk1"     : "shilin-jian",
                           "lv1"     : 120,
                           "force"   : 180,
                           "gongxian": 500,
                           "shen"    : 50000, ]));
                break;

        case "流雲疊影" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/liuyun-zhang/die",
                           "name"    : "流雲疊影",
                           "msg1"    : "$N略微點點頭，掌法陡然變快，"
                                       "雙掌不斷拍出，竟似如影如幻，"
                                       "似有三頭六臂，直把你看得眼花"
                                       "繚亂。",
                           "sk1"     : "liuyun-zhang",
                           "lv1"     : 100,
                           "dodge"   : 150,
                           "gongxian": 700,
                           "shen"    : 50000, ]));
                break;

        case "排山倒海" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/liuyun-zhang/pai",
                           "name"    : "排山倒海",
                           "msg1"    : "$N點了點頭，説道：“我給你演"
                                       "示一遍，可看好了。”説完$N便"
                                       "將內力運於掌風之中，雙掌猛然"
                                       "拍出，雄渾有力，氣勢磅礴，毫"
                                       "無滯帶。正是衡山派絕學「排山"
                                       "倒海」。",
                           "sk1"     : "liuyun-zhang",
                           "lv1"     : 140,
                           "force"   : 180,
                           "gongxian": 600,
                           "shen"    : 50000, ]));
                break;

        case "鎮嶽尚方" :
                return MASTER_D->give_item(me, this_object(),
                        ([ "item"    : ZHENYUE,
                           "master"  : 1,
                           "sk1"     : "henshan-jian",
                           "lv1"     : 120,
                           "shen"    : 50000, ]));
                break;
        default:
                return 0;
        }
}

/*
void unconcious()
{
        die();
}
*/

mixed ask_jian()
{
        object me;
        object ob;
        object owner;
        object *oblist;
        object temp;
        int i;

        me = this_player();
        if( query("shen", me)<0 )
        {
                if( query("family/family_name", me) == "衡山派" )
                        message_vision(CYN "$N" CYN "大怒，對$n" CYN "道：“你身為衡山弟子，"
                                       "反而誤入魔道，還不快快醒轉？”\n" NOR,
                                       this_object(), me);
                else
                        message_vision(CYN "$N" CYN "大怒，對$n" CYN "喝道：“好一個邪魔外"
                                       "道，居然敢窺我鎮嶽尚方？”\n" NOR,
                                       this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) != "衡山派" )
                return "鎮嶽尚方是我護身之寶，你打聽它幹什麼？";

        if( query("family/master_id", me) != query("id") )
                return "只有我的弟子才能用鎮嶽尚方，你還是請回吧。";

        if( query("shen", me)<60000 )
                return "你行俠仗義的事情做得不夠，我不能把鎮嶽尚方交給你。";
                                if (present("zhenyue shangfang",me))
                                                                return "鎮嶽尚方不是在你的手中麼，怎麼反而來找我呢？";

        ob=new("/clone/weapon/treasure/zhenyue");
        if ( temp=ob->violate_unique())
        {
                destruct(ob);
                ob=temp;
                owner = environment(ob);
                  if (owner == me)
                         return "鎮嶽尚方不是在你的手中麼，怎麼反而來找我呢？";
        if ( owner->is_character() && owner!= this_object())
           {
                if( query("family/family_name", owner) == query("family/family_name") )
                        return "鎮嶽尚方現在在"+query("name", owner)+
                               "手中，你要想用就去找他吧。";
                else
                        return "本派至寶鎮嶽尚方現在落在"+query("name", owner)+
                               "手中，你快去殺了他把劍拿回來。";
                 }
         }

                                ob->move(this_object());
        message_vision(CYN "$N" CYN "點點頭道：“好，你用這鎮嶽尚方要多作一些行"
                       "俠仗義的事情！”\n" NOR, this_object(), me);
        command("givezhenyueshangfangto"+query("id", me));
        addn("count",-1);
        return 1;
}
