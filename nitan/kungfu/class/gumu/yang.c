// yang.c 楊過

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_GUARDER;

#include <ansi.h>
#include "gumu.h"

string ask_yunv();
int not_to_learn_ss(object ob);
mixed teach_sad();
string ask_sword();
int ask_youju();
mixed ask_me();
string ask_nuhai();

void create()
{
        set_name("楊過", ({"yang guo", "yang"}));
        set("gender", "男性");
        set("age", 26);
        set("long", @LONG
他看上去眉目之間有一股清秀之氣，然而隱隱約約卻讓人感到一陣哀傷之情，
左袖空蕩蕩的，顯然已是殘疾。
LONG );
        set("attitude", "friendly");

        set("str", 35);
        set("int", 36);
        set("con", 34);
        set("dex", 32);

        set("qi", 7800);
        set("max_qi", 7800);
        set("jing", 6900);
        set("max_jing", 6900);
        set("neili", 8500);
        set("max_neili", 8500);
        set("jiali", 120);
        set("no_get", 1);

        set("combat_exp", 5750000);

        set("couple/id", "xiao longnv");
        set("couple/name", "小龍女");

        set_skill("force", 690);
        set_skill("yunv-xinfa", 690);
        set_skill("surge-force", 690);
        set_skill("sword", 680);
        set_skill("yunv-jian", 680);
        set_skill("quanzhen-jian", 680);
        set_skill("xuantie-jian", 680);
        set_skill("dodge", 650);
        set_skill("yunv-shenfa", 650);
        set_skill("parry", 680);
        set_skill("unarmed", 680);
        set_skill("meinv-quan", 670);
        set_skill("strike", 680);
        set_skill("sad-strike", 680);
        set_skill("fireice-strike", 680);
        set_skill("tianluo-diwang", 660);
        set_skill("literate", 600);
        set_skill("taoism", 600);
        set_skill("medical", 680);
        set_skill("array", 680);
        set_skill("yunv-xinjing", 680);
        set_skill("throwing", 640);
        set_skill("yufeng-zhen", 640);
        set_skill("hebi-jianzhen", 640);
        set_skill("martial-cognize", 600);

        map_skill("force", "surge-force");
        map_skill("sword", "xuantie-jian");
        map_skill("dodge", "yunv-shenfa");
        map_skill("parry", "sad-strike");
        map_skill("unarmed", "sad-strike");
        map_skill("strike", "tianluo-diwang");

        prepare_skill("unarmed", "sad-strike");

        create_family("古墓派", 3, "弟子");

        set("inquiry", ([
                "王重陽" : "嘿...嘿！",
                "郭靖"   : "他可真是真正的大俠。",
                "黃蓉"   : "黃師叔麼...真不好説啊。",
                "小龍女" : "你打聽我妻子幹什麼？",
                "楊康"   : "算了，不替他也罷。",
                "玉蜂針" : "我手頭可沒有，很久沒有用它了。",
                "黯然銷魂掌" : (: teach_sad :),
                "玄鐵劍法"   : "那是獨孤前輩所創絕學，在下有幸到是習得！\n",
                "玄鐵劍" :   (: ask_sword :),
                "玄鐵劍法" : (: ask_sword :),
                "古墓幽居" : (: ask_youju :),
                "怒海狂濤"   : (: ask_nuhai :),
        ]));

        set("guarder", ([
                "refuse_home" : "$N對$n冷冷道：滾！",
                "refuse_other": "$N對$n道：後面是古墓弟子練功的地方，你少要打擾！",
                "refuse_carry": "$N對$n喝道：把你身上得人給我撂下！",
        ]));

        set("no_teach/sad_strike", (: not_to_learn_ss :));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.wang" :),
                (: perform_action, "unarmed.xiao" :),
                (: perform_action, "unarmed.tuo" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/attack", 150);
        set_temp("apply/defense", 150);
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",5);
        setup();

        carry_object("/clone/cloth/qingyi")->wear();
}

void init()
{
        ::init();
        add_action("do_yuanyi", "yuanyi");
}

int recognize_apprentice(object ob, string skill)
{
        if( query("family/family_name", ob) == query("family/family_name") )
        {
                if (query_skill(skill, 1) < 1 ||
                    SKILL_D(skill)->type() != "martial")
                        return 0;

                if( query("int", ob)<24 )
                {
                        command("say 你這人資質不佳，我教起來太累。");
                        return -1;
                }

                return 1;
        }

        if (skill == "unarmed" &&
            this_player()->query_skill("sad-strike", 1) > 0 &&
            this_player()->query_skill(skill, 1) < 200)
                return 1;

        if (skill != "sad-strike")
        {
                command("say 你還是找你的師傅去學習吧！");
                return 0;
        }

        if (not_to_learn_ss(ob))
                return -1;

        if (this_player()->query_skill(skill, 1) > 600)
                return 0;

        return 1;
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if (ob->query_int() < 32)
        {
                command("say 你的資質不夠，難以領會上乘武功。");
                return;
        }

        if ((int)ob->query_skill("force") < 150)
        {
                command("say 想拜我為師麼？你把內功練好了再來吧！");
                return;
        }

        if( query("max_neili", ob)<1000 )
        {
                command("say 你把內力鍛鍊好了再來也不遲啊！");
                return;
        }

        command("say 好吧，看你也是性情中人，我就收下你這個徒弟了。");
        command("recruit "+query("id", ob));
}

string ask_sword()
{
        object ob = this_player();
        mapping fam=query("family", ob);
        if (! fam || fam["family_name"] != "古墓派")
                return RANK_D->query_respect(ob) + "非我古墓傳人，不知道此話怎講？";
        if (fam["generation"] > 4)
                return RANK_D->query_respect(ob) + "非我神鵰俠侶傳人，還是等以後再説吧。";
        if( query("ygpass", ob) )
                return "我不是已經告訴你玄鐵劍法的運氣之道了麼？";
        if( query("gender", ob) == "男性" )
        {
                command("pat"+query("id", ob));
                command("say 當年我在襄陽城南，得遇神鵰的相助，於獨孤大俠墓前練成玄鐵劍法。");
                set("ygpass", 1, ob);
                return "屏氣具息，凝氣守中，意守丹田，這就是在洪水中運氣的訣竅，你好好去領悟一下吧。";
        }
        if( query("gender", ob) == "女性"){
        if ((int)ob->query_str() < 35)
                return "這位" + RANK_D->query_respect(ob) + "，玄鐵劍法需要極高的膂力，你還是再努力一翻吧。";
        if ((int)ob->query_dex() < 35)
                return "這位" + RANK_D->query_respect(ob) + "，在洪水中練習玄鐵劍法需要極高的身法，你還是再努力一翻吧。";
        if ((int)ob->query_skill("sword", 1) < 200)
                return "這位" + RANK_D->query_respect(ob) + "的基本劍法還需繼續修煉，否則難以抵擋洪水的衝擊。";
        if ((int)ob->query_int() < 35)
                return "這位" + RANK_D->query_respect(ob) + "的悟性還不夠高，難以理解我所要講的口訣。";
                  command("pat"+query("id", ob));
                  command("say 當年我在襄陽城南，得遇神鵰的相助，於獨孤大俠墓前練成玄鐵劍法。");
                  set("ygpass", 1, ob);
                  return "屏氣具息，凝氣守中，意守丹田，這就是在洪水中運氣的訣竅，你好好去領悟一下吧。";
        }
}

int ask_youju()
{
        object ob = this_player();

        if( query("family/family_name", ob) != "古墓派"){
                command("say 這是“美女拳法”最後一招的收式，是我所自創的。");
                return 1;
        }
        if( query("family/master_name", ob) == "李莫愁"){
                command("say 這是“美女拳法”最後一招的收式，是我所自創的。");
                command("say 你是我師伯李莫愁的弟子，我本不該指點於你。");
                command("say 既然一場來到，如果你願意讓我為化去你身上的邪氣，指點你這招“古墓幽居”。你願意(yuanyi)否？");
                set_temp("mark/youju", 1, ob);
                return 1;
                }
        if( query("can_perform/meinv-quan/you", ob)>0){
                command("say 你不是已經學會了嗎？");
                return 1;
        }
        if ((int)ob->query_skill("unarmed", 1) < 120) {
                command("say 要使用這樣的絕招需要高深的拳法，你還是多練習練習“美女拳法”再説吧。");
                return 1;
        }
        command("say 這是“美女拳法”最後一招的收式，是我所自創的。");
        command("say 好，既然一場來到，你我可謂有緣，待我指點你這招“古墓幽居”。");
        message_vision( "$N仔細給$n講解了“古墓幽居”的精要所在。\n",this_object(), ob );
        set("can_perform/meinv-quan/you", 1, ob);
        return 1;
}
int do_yuanyi()
{
        object me = this_player();

        if( !query_temp("mark/youju", me) )
                return 0;

        message_vision("$n伸手在$N身上幾處命門大穴連拍數下。\n", me, this_object() );
        write("你感到頭腦中一陣通泰。\n");
        set("shen", 0, me);
        command("say 好，孺子可教，我就指點你這招“古墓幽居”。");
        message_vision( "$N仔細給$n講解了“古墓幽居”的精要所在。\n",this_object(), me );
        delete_temp("mark/youju", me);
        set("can_perform/meinv-quan/you", 1, me);
        return 1;
}

// 領取怒海狂濤任務
string ask_nuhai()
{
        object me;
        string msg;
        
        
        me = this_player();
        
        if( query("can_perform/surge-force/new", me) )
                return "這怒海狂濤的絕學已經掌握了，還來打攪我幹什麼？";
                
        //如果已經領取任務
        if( query("can_perform/surge-force/quest/step", me) )
                return "如果你能幫我找到龍兒，這怒海狂濤的絕學我便傳你。";
        
        msg = HIC "怒海狂濤是我多年來在與海浪搏擊中領悟而出的驚世絕學，其中融入了多種頂級武學\n"
                  "的精髓。可惜，目前龍兒被金輪法王擄走，下落不明，如果你能協助我找回龍兒，這\n"
                  "套絕學我便傳你。\n" NOR;
        
        tell_object(me, msg);

        set("can_perform/surge-force/quest/step", 1, me);
        me->save();
        
        return "聽説金輪法王最近在絕情谷出沒，你可以上那去看看。\n";    
}
mixed teach_sad()
{
        object ob = this_player();

        if (ob->query_skill("sad-strike", 1) >= 1)
        {
                command("say 你不是已經會了嗎？");
                return 1;
        }

        if( query("gender", ob) != "男性" )
        {
                command("say 我這門武功只適合男性修煉，你還是算了吧！");
                return 1;
        }

        if( query("static/sadly", ob)<3 )
        {
                command("say 你體會不到那種思念妻子的情懷，"
                        "無法領會我的黯然銷魂掌！");
                return 1;
        }

        if( query("character", ob) == "陰險奸詐" || 
            query("character", ob) == "心狠手辣" )
        {
                command("say 你一心想着去害人，無法領悟黯然銷魂的境界！");
                return 1;
        }

        if( query("int", ob)<24 )
        {
                command("say 你先天悟性不足，無法領悟黯然銷魂掌。");
                return 1;
        }

        if( query("str", ob)<28 )
        {
                command("say 你先天臂力不足，無法修煉黯然銷魂掌。");
                return 1;
        }

        if( query("max_neili", ob)<3000 )
        {
                command("say 你的內力修為不足，無法練黯然銷魂掌。");
                return 1;
        }

        if (ob->query_skill("force") < 320)
        {
                command("say 你內功修為不足，無法修煉黯然銷魂掌。");
                return 1;
        }

        if ((int)ob->query_skill("unarmed", 1) < 200)
        {
                command("say 你的基本拳腳不夠嫻熟，無法練黯然銷魂掌。");
                return 1;

        }

        if (ob->query_skill("martial-cognize", 1) < 200)
        {
                command("say 你武學修養不足，無法領悟煉黯然銷魂掌。");

                return 1;
        }

        message_vision(HIW "$n" HIW "看了看$N" HIW "，道：好！你我也算是頗有"
                       "淵源，我就傳你黯然銷魂掌！\n" NOR, ob, this_object());

        ob->set_skill("sad-strike", 10);

        tell_object(ob, HIG "你學會了「黯然銷魂掌」。\n" NOR);

        command("tan");
        command("say 下去練習吧，記得要好好對待你的妻子！");

        return 1;
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

        case "卷字訣" :
       return MASTER_D->teach_pfm(this_player(), this_object(),
                        ([ "perform" : "can_perform/xuantie-jian/juan",
                           "free"    : 1,
                           "name"    : "卷字訣",
                           "sk1"     : "xuantie-jian",
                           "lv1"     : 100,
                           "neili"   : 3000,
                           "force"   : 600,
                        ]));
                break;

        case "迅雷" :
       return MASTER_D->teach_pfm(this_player(), this_object(),
                        ([ "perform" : "can_perform/xuantie-jian/lei",
                           "name"    : "迅雷",
                           "sk1"     : "xuantie-jian",
                           "lv1"     : 200,
                           "sk2"     : "force",
                           "lv2"     : 200,
                           "sk3"     : "surge-force",
                           "lv3"     : 200,
                           "gongxian": 600, ])); 
                break;

        case "大江東去" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xuantie-jian/dong",
                           "free"    : 1,
                           "name"    : "大江東去",
                           "sk1"     : "xuantie-jian",
                           "lv1"     : 200,
                           "neili"   : 5000,
                           "force"   : 600,
                         ]));
                break;

        case "力蕩羣魔" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xuantie-jian/dang",
                           "name"    : "力蕩羣魔",
                           "sk1"     : "xuantie-jian",
                           "lv1"     : 70,
                           "sk2"     : "force",
                           "lv2"     : 90,
                           "gongxian": 600, ]));
                break;

        case "海潮洶湧" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xuantie-jian/hai",
                           "name"    : "海潮洶湧",
                           "sk1"     : "xuantie-jian",
                           "lv1"     : 130,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "sk3"     : "dodge",
                           "lv3"     : 100,
                           "gongxian": 600, ]));

                break;

        case "千均一擊" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xuantie-jian/ji",
                           "name"    : "千均一擊",
                           "sk1"     : "xuantie-jian",
                           "lv1"     : 130,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "sk3"     : "dodge",
                           "lv3"     : 100,
                           "gongxian": 600, ]));

                break;

        case "黯然銷魂" :
                return MASTER_D->teach_pfm(me, this_object(),
                          ([ "perform" : "can_perform/sad-strike/xiao",
                           "free"    : 1,
                           "name"    : "黯然銷魂",
                           "sk1"     : "sad-strike",
                           "lv1"     : 150,
                           "neili"   : 3200,
                           "force"   : 320,
                         ]));
                break;

        case "拖泥帶水" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/sad-strike/tuo",
                           "free"    : 1,
                           "name"    : "拖泥帶水",
                           "sk1"     : "sad-strike",
                           "lv1"     : 180,
                           "neili"   : 6000,
                           "force"   : 360,
                         ]));
                break;

            case "怒海驚濤" :
                  return MASTER_D->teach_pfm(me, this_object(),
                          ([ "perform" : "can_perform/sad-strike/tao",
                             "free"    : 1,
                               "name"    : "怒海驚濤",
                             "sk1"     : "sad-strike",
                             "lv1"     : 280,
                             "neili"   : 6000,
                             "force"   : 560,
                           ]));
                  break;

        default:
                return 0;
        }
}

int not_to_learn_ss(object ob)
{
        if( query("gender", ob) == "女性" )
        {
                command("say 我這門武功不適合女孩子學習，還是算了吧！");
                return 1;
        }

        if( query_temp("can_learn/yang/sad-strike", ob) )
                return 0;

        if( query("family/family_name", ob) != query("family/family_name") )
        {
                command("say " + RANK_D->query_respect(ob) + "你不是我的親傳弟子，找我何干？");
                return 1;
        }

        if( query("static/sadly", ob)<3 )
        {
                command("say 你體會不到那種思念妻子的情懷，"
                        "無法領會我的黯然銷魂掌！");
                return 1;
        }

        message_vision("$n看了看$N，道：好！你我也算是頗有"
                       "淵源，我就傳你黯然銷魂掌！\n",
                       ob, this_object());
        set_temp("can_learn/yang/sad-strike", 1, ob);
        return 0;
}

/*
mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/sad-strike/wannian", me) )
                return "自己好好多練習吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "你不是我的親傳弟子，何出此言？";

        if( query("shen", me)<200000 )
                return "你行俠仗義的事情做的還很不夠，我不能傳你這一招！";

        if (me->query_skill("sad-strike", 1) < 180)
                return "你的黯然銷魂掌還不夠熟練，我還不能教你這一招！";

        message_vision(HIM "$n" HIM "慢慢運起內功，然後以疾風般的速度向$N"HIM"揮出一掌！\n"
                       HIM "$n" HIM "這一掌雖然奇快無比，但是$N"HIM"確把一招的來勢看得很透澈，然後輕而易舉的避開了！\n"
                       "正當$N" HIM "奇怪為什麼這一招這麼差的時候，$n"HIM"的掌勢突然向旁邊一轉，正好打在了$N"HIM"的胸口上！！！\n"
                       "$N"HIM"大吃一驚，躲避已經不行，連忙動起內功硬生生的受了這一招，但是......\n" NOR,
                       me, this_object());
        command("sigh");
        command("say 你就先躺一下吧。");
        tell_object(me, HIG "你學會了萬念俱灰。\n" NOR);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 160000);
        set("can_perform/sad-strike/wannian", 1, me);
        me->unconcious();
        return 1;
}
*/
// 接受絕情丹
int accept_object(object me, object ob)
{
        int r;
        
        if (r = ::accept_object(me, ob)) 
                return r;
                
        if (! objectp(me) || ! objectp(ob))return 0;
        
        if( query("id", ob) != "jueqing dan" )
        {
                return 0;
        }

        if( query("can_perform/surge-force/new", me) )
        {
                tell_object(me, HIG "楊過告訴你：多謝閣下上次仗義相助，這東西還是你自己留着吧。\n" NOR);
                return 0;
        }
        
        if( query("can_perform/surge-force/quest/step", me)<3 )
                return 0;
        
        if( query("reborn/times", me) < 3 )
        {               
                tell_object(me, HIG "楊過告訴你：你還未經歷輪迴轉世的磨練，恐怕難以學成怒海狂濤。這丹我要不得。\n" NOR);
                return 0;
        }
                
        if( query("int", me)<40 || query("con", me)<40 )
        {               
                tell_object(me, HIG "楊過告訴你：你先天屬性不足，難以學成怒海狂濤。這丹我要不得。\n" NOR);
                return 0;
        }
                
        if (me->query_skill("force", 1) < 1000)
        {
                tell_object(me, HIG "楊過告訴你：你基本內功修為不足，無法修煉怒海狂濤。這丹我要不得。\n" NOR);
                return 0;
        }               
        if( query("max_neili", me)<35000 )
        {
                tell_object(me, HIG "楊過告訴你：你內力修為不足，無法修煉怒海狂濤。這丹我要不得。\n" NOR);
                return 0;
        }       
        if (me->query_skill("taoism", 1) < 1)
        {
                tell_object(me, HIG "楊過告訴你：你道學心法修為不足，無法修煉怒海狂濤。這丹我要不得。\n" NOR);  
                return 0;
        }               
        if (me->query_skill("xuantie-jian", 1) < 1)
        {
                tell_object(me, HIG "楊過告訴你：你玄鐵劍法修為不足，無法修煉怒海狂濤。這丹我要不得。\n" NOR);  
                return 0;                               
        }               
        if (me->query_skill("martial-cognize", 1) < 1200)
        {
                tell_object(me, HIG "楊過告訴你：你武學修養不足，無法修煉怒海狂濤。這丹我要不得。\n" NOR);              
                return 0;
        }               
        if (me->query_skill("jiuyin-shengong", 1) < 1 && 
            me->query_skill("jiuyin-hamagong", 1))
        {
                tell_object(me, HIG "楊過告訴你：你未曾練成過九陰真經，無法修煉怒海狂濤。這丹我要不得。\n" NOR);
                return 0;       
        }               

        command("thank "+query("id", me));
        
        message_sort(HIM "\n$N" HIM "對$n説道：多虧了閣下仗義相助，龍兒這下有救了，楊某無以為謝，便"
                     "將這怒海狂濤絕學傳授於你，你可聽好了 ...\n\n" NOR, this_object(), me);

                                
        tell_object(me, HIG "楊過將怒海狂濤絕學修煉要決一一傳授於你...\n" NOR);

        tell_object(me, HIC "\n恭喜你！領悟了怒海狂濤（新）。\n");

        CHANNEL_D->do_channel(this_object(), "rumor", "\n聽説楊過將怒海狂濤絕學傳授給了" HIY + me->name() + HIM "。" NOR);

        me->set_skill("surge-force", 200);
        set("can_perform/surge-force/new", 1, me);
        
        destruct(ob);
        
        me->save();     

        return 1;
}
/*
void unconcious()
{
        die();
}
*/
