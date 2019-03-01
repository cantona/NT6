// ouyangfeng.c

#include <ansi.h>
#include "ouyang.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

//#define ZHANG "/d/baituo/obj/lingshezhang"
#define ZHANG "/clone/lonely/lingshe"

string ask_shenshe(string name);
mixed ask_me();
mixed ask_music_book();
mixed ask_skill1();
mixed ask_skill2();
string ask_lingshe();
mixed ask_shegu();

void create()
{
        set_name("歐陽鋒", ({ "ouyang feng", "ouyang", "feng" }));
        set("long", "他就是白駝山莊主，號稱“西毒”的歐陽鋒。臉型瘦削，\n"
                    "身形剽悍，雖然受到郭靖欺騙誤學習了「九陰真經」而走\n"
                    "火入魔，一度變得精神錯亂，但是現在已然恢復，功力猶\n"
                    "勝往昔。\n");
        set("title", "西域白駝山莊主");
        set("gender", "男性");
        set("age", 53);
        set("nickname", HIR "西毒" NOR);
        set("shen_type", -1);
        set("attitude", "peaceful");

        set("str", 32);
        set("int", 34);
        set("con", 34);
        set("dex", 32);

        set("qi", 6000);
        set("max_qi", 6000);
        set("jing", 5000);
        set("max_jing", 5000);
        set("neili", 8000);
        set("max_neili", 8000);
        set("jiali", 200);

        set("combat_exp", 4000000);

        set_skill("force", 640);
        set_skill("strike", 640);
        set_skill("dodge", 640);
        set_skill("parry", 640);
        set_skill("cuff", 640);
        set_skill("finger", 640);
        set_skill("staff", 640);
        set_skill("training", 640);
        set_skill("poison", 640);
        set_skill("shedu-qiqiao", 640);
        set_skill("hamagong", 640);
        set_skill("chanchu-bufa", 640);
        set_skill("lingshe-quan", 640);
        set_skill("lingshe-zhangfa", 640);
        set_skill("shentuo-zhang", 640);
        set_skill("baibian-daxue", 640);
        set_skill("guzheng-jifa", 620);
        set_skill("xiyu-tiezheng", 620);
        set_skill("wushe-qu", 620);
        set_skill("literate", 680);
        set_skill("medical", 660);
        set_skill("baituo-michuan", 660);
        set_skill("jinchan-tunyue", 660);
        set_skill("martial-cognize", 620);
        set_skill("shexing-diaoshou", 660);

        map_skill("force", "hamagong");
        map_skill("dodge", "chanchu-bufa");
        map_skill("cuff", "lingshe-quan");
        map_skill("parry", "lingshe-zhangfa");
        map_skill("strike","hamagong");
        map_skill("staff", "lingshe-zhangfa");
        map_skill("finger", "shedu-qiqiao");
        map_skill("poison", "shedu-qiqiao");
        map_skill("medical", "baituo-michuan");
        map_skill("guzheng-jifa", "xiyu-tiezheng");

        prepare_skill("finger", "shedu-qiqiao");
        prepare_skill("cuff", "lingshe-quan");

        create_family("歐陽世家", 5, "掌門");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "staff.chan" :),
                (: perform_action, "staff.qianshe" :),
                (: perform_action, "staff.wuji" :),
                (: perform_action, "cuff.rou" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));

        set("inquiry", ([
                "絕招"     : (: ask_me :),
                "絕技"     : (: ask_me :),
                "千蛇出洞" : (: ask_me :),
                "引路神蛇" : (: ask_shenshe, "shenshe":),
                "靈蛇"     : (: ask_lingshe :),
                "蛇谷"     : (: ask_shegu :),
                "箏譜"     : (: ask_music_book :),
                "古箏技法" : (: ask_music_book :),
                "靈蛇纏身" : (: ask_skill1 :),
                "橫行無忌" : (: ask_skill2 :),
        ]));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("music_book", 1);

        set("master_ob",5);
        setup();
        carry_object(__DIR__"obj/baipao")->wear();
        carry_object("/d/baituo/obj/shezhang")->wield();
        carry_object("d/baituo/obj/tiezheng");
        add_money("silver", 50);
}

int recognize_apprentice(object me, string skill)
{
        if (skill != "guzheng-jifa")
                return 0;

        if( query_temp("can_learn/ouyang/guzheng-jifa", me) )
                return 1;

        command("say 好吧，你願意學我就傳你一點古箏之道。");
        set_temp("can_learn/ouyang/guzheng-jifa", 1, me);
        return 1;
}

void attempt_apprentice(object ob)
{
        if(! permit_recruit(ob))
                return;

        if( query("combat_exp", ob)<200000 )
        {
                if (random(2))
                        command("smile");
                else
                        command("pat"+query("id", ob));

                command("say 你的經驗還不夠，先和我的侄兒歐陽克學習武功吧。");
                return ;
        }

        command("sigh");
        command("pat"+query("id", ob));
        command("recruit "+query("id", ob));
        command("say 不錯，不錯！我歐陽真是後繼有人。");
        return;
}

mixed ask_skill1()
{
        object me=this_player();

        if( query("can_perform/lingshe-zhangfa/chan", me) )
                return "我不是已經教給你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return ("哪來的野小子敢在這裡撒野！\n");

        if (me->query_skill("lingshe-zhangfa",1 ) < 100)
                return ("你的杖法還不到家，學不了「靈蛇纏身」！\n");

        command("say 好吧，你看好了。");
        tell_object(me, HIR"歐陽峰將「靈蛇纏身」演練了一遍，你心裡默默暗記，心中驚嘆不已。\n"NOR);

        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("lingshe-zhangfa"))
                me->improve_skill("lingshe-zhangfa", 1500000);
        if (me->can_improve_skill("lingshe-zhangfa"))
                me->improve_skill("lingshe-zhangfa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/lingshe-zhangfa/chan", 1, me);
        return 1;
}

mixed ask_skill2()
{
        object me;
        me = this_player();

        if( query("can_perform/lingshe-zhangfa/wuji", me) )
                return "你還不快去練功去？好好把我們歐陽家發揚光大！";

        if( query("family/family_name", me) != query("family/family_name") )
                return ("哪來的野小子敢在這裡撒野！\n");

        if (me->query_skill("lingshe-zhangfa", 1) < 100)
                return ("你的杖法還不到家，學不了「橫行無忌」！\n");

        command("say 好吧，你看好了。");
        tell_object(me, HIR"歐陽峰將「橫行無忌」演練了一遍，你心裡默默暗記，心中驚嘆不已。\n"NOR);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("lingshe-zhangfa"))
                me->improve_skill("lingshe-zhangfa", 1500000);
        if (me->can_improve_skill("lingshe-zhangfa"))
                me->improve_skill("lingshe-zhangfa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/lingshe-zhangfa/wuji", 1, me);
        return 1;
}

mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/lingshe-zhangfa/qian", me) )
                return "你還不快去練功去？好好把我們歐陽家發揚光大！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪兒來的？找死麼？";

        if( query("shen", me)>-40000 )
                return "你這人手段不夠狠毒，我現在還不能傳你絕招！";

        if (me->query_skill("lingshe-zhangfa", 1) < 120)
                return "你先好好把靈蛇杖法練好了再說！";

        message_vision(HIY "$n" HIY "喝道：看仔細了！說把盪"
                       "臂橫掃，伸伸縮縮，當真是變幻無窮！把$N"
                       HIY "的眼睛都看直了。\n" NOR,
                       me, this_object());
        command("heihei");
        command("say 我演示的這麼清楚，你看懂了沒有？");
        tell_object(me, HIG "你學會了千蛇出洞。\n" NOR);

        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("lingshe-zhangfa"))
                me->improve_skill("lingshe-zhangfa", 1500000);
        if (me->can_improve_skill("lingshe-zhangfa"))
                me->improve_skill("lingshe-zhangfa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
           set("can_perform/lingshe-zhangfa/qian", 1, me); 
        return 1;
}

string ask_shenshe(string name)
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "歐陽世家" )
                return RANK_D->query_respect(this_player()) +
                "，你並不是本山莊的人，此話從何說起？";

        if (  present("shen she", this_player()) )
                return RANK_D->query_respect(this_player()) +
                "你身上不是有神蛇嗎？怎麼又來要？真是貪得無厭！";

        ob = new("/d/baituo/obj/" + name);
        ob->move(this_player());

        message_vision("歐陽鋒給$N一條"+query("name", ob)+"。\n",this_player());
        return "此神蛇乃本山莊特有，切記不可給予他人！";
}

mixed ask_music_book()
{
        object me;
        object ob;

        me = this_player();
        if (query("music_book") < 1)
                return "我的箏譜已經借出去了。\n";

        ob = new("/clone/book/zhengpu");
        ob->move(me, 1);
        message_vision("$n把箏譜給了$N，道：你拿去自己好好琢磨吧。\n",
                       me, this_object());
        set("music_book", 0);
        return 1;
}

mixed ask_shegu()
{
        object me, staff;
        object owner;
        object ob;
int lv,cost;
        me = this_player();

        if( query("family/family_name", me) != "歐陽世家" && query("combat_exp", me)>100000){
                command("sneer"+query("id", me));
                command("say 白駝山蛇谷的秘密，豈能透露給外人知曉？"+RANK_D->query_rude(me)+"，你太多嘴了！");
                kill_ob(me);
                command("performbite"+query("id", me));//hasweapon
                command("performpuji"+query("id", me));//noweapon
                return 1;
        }

        if( query("family/family_name", me) != "歐陽世家"){
                command("sneer"+query("id", me));
                message_vision("$N沒有回答$n。\n", this_object(), me);
                return 1;
        }

   if( query("family/first", me) ) cost = 250; 
             else cost = 500; 
             if( query("family/gongji", me) < cost ) 
                     return "你為我白駝山效力還不夠，等你擁有足夠的師門功績再來兌換靈蛇杖使用時間吧。";
             ob = find_object(ZHANG);
             if (! ob) ob = load_object(ZHANG);
             owner = environment(ob);
             while (owner)
            {
                    if (owner->is_character() || ! environment(owner))
                            break;
                    owner = environment(owner);
            }

            if (owner == me)
                    return "靈蛇杖不是在你的手中麼，怎麼又來找我呢？";

             if (objectp(owner) && owner != this_object())
             {
                     if (! owner->is_character())
                             return "我已經把靈蛇杖已經借出去了。";

                     if( query("family/master_id", owner) == query("id") )
                             return "靈蛇杖現在在"+query("name", owner)+
                                    "手中，你要想用就去找他吧。";
                     else
                             return "靈蛇杖現在落在"+query("name", owner)+
                                    "手中，你去把他找回來吧。";
            }

        if( query("baituo/shegu_permit", me)){
//                command("say 蛇谷中的蛇兒，你可以隨意捕捉。好好修煉毒技，莫要墮了西毒的威名！");
//        staff = new("/d/baituo/obj/lingshezhang");
//        staff->move(me);
             ob->move(this_object());

message_vision("$N點點頭道：蛇谷中的蛇兒，你可以隨意捕捉。好好修煉毒技，莫要墮了西毒的威名！\n", this_object(), me);
            command("give lingshe zhang to "+query("id", me));
addn("family/gongji", -cost, me); 
                ob->start_borrowing();
                return 1;
        }

        lv = (int)me->query_skill("poison", 1);

        if( lv < 80 ) {
                command("say 憑你這點使毒本事，想進蛇谷還早得很。乖乖的在莊裡修煉！");
                return 1;
        }

        if( lv < 100 ) {
                command("pat "+query("id", me));
                command("say 你的毒技是有點火候了，不過想進蛇谷，還得多下點功夫琢磨。");
                return 1;
        }

        command("nod "+query("id", me));
        command("say 你用毒的能耐，似乎是進步多了。好，老夫就許你進蛇谷練練本領。");
        set("baituo/shegu_permit", 1, me);

//        staff = new("/d/baituo/obj/lingshezhang");
//        staff->move(me);
             ob->move(this_object());

//        message_vision("$N將一根"+staff->name()+"交給$n。\n",this_object(), me);
message_vision("$N點點頭道：從今以後，你可以自由進出蛇谷。用心從中鑽研，你的毒技還可以更上層樓！\n", this_object(), me);
            command("give lingshe zhang to "+query("id", me));
//        command("say 從今以後，你可以自由進出蛇谷。用心從中鑽研，你的毒技還可以更上層樓。");

        return 1;
}


string ask_lingshe()
{
        mapping fam;
        object obj, me;

        me = this_player();
        if( query("family/master_name", me) != "歐陽鋒"){
                return ("娃娃功力不夠，還是別要為妙！");
        }
        if (query("lingshe_count") < 1) {
                return ("靈蛇馴養不易，現在沒有！");
        }
        message_vision(CYN"$N撮唇作嘯，袖中緩緩遊出一條銀色小蛇，對著$n搖頭擺尾，似在示意問好。\n"NOR,
        this_object(), me);
        obj = new("/d/baituo/npc/lingshe.c");
        obj->move(environment());
        addn("lingshe_count", -1);
                  return ("靈蛇已顯，娃娃不妨試試是否有緣成為它的主人。");
}

void reset()
{
        if (query("lingshe_count") < 3)
                addn("lingshe_count", 1);
        set("music_book", 1);
}

/*
void unconcious()
{
        die();
}
*/

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "歷練" :
        case "歷煉" :
        case "鍛煉" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "蟾震九天" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/hamagong/zhen",
                           "name"    : "蟾震九天",
                           "sk1"     : "hamagong",
                           "lv1"     : 100,
                           "sk2"     : "force",
                           "lv2"     : 140,
                           "neili"   : 2000,
                           "gongxian": 1000,
                           "shen"    : -24000, ]));
                break;

        case "蛤蟆撲擊" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/hamagong/puji",
                           "name"    : "蛤蟆撲擊",
                           "sk1"     : "hamagong",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 600,
                           "neili"   : 1400,
                           "shen"    : -28000, ]));
                break;

        case "推天式" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/hamagong/tui",
                           "name"    : "推天式",
                           "sk1"     : "hamagong",
                           "lv1"     : 60,
                           "force"   : 150,
                           "gongxian": 400,
                           "shen"    : -20000, ]));
                break;

        case "雪鎖千山" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shentuo-zhang/suo",
                           "name"    : "雪鎖千山",
                           "sk1"     : "shentuo-zhang",
                           "lv1"     : 120,
                           "gongxian": 400,
                           "shen"    : -10000, ]));
                break;

        case "柔字訣" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/lingshe-quan/rou",
                           "name"    : "柔字訣",
                           "sk1"     : "lingshe-quan",
                           "lv1"     : 120,
                           "gongxian": 400,
                           "shen"    : -10000, ]));
                break;

        case "點字訣" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/baibian-daxue/dian",
                           "name"    : "點字訣",
                           "sk1"     : "baibian-daxue",
                           "lv1"     : 140,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 600,
                           "shen"    : -10000, ]));
                break;

        case "靈蛇纏身" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/lingshe-zhangfa/chan",
                           "name"    : "靈蛇纏身",
                           "sk1"     : "lingshe-zhangfa",
                           "lv1"     : 140,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 600,
                           "shen"    : -30000, ]));
                break;

        default:
                return 0;
        }
}

int accept_object(object me, object ob)
{
        int r;
        if (r = ::accept_object(me, ob))
                return r;

        if (base_name(ob) != ZHANG)
        {
                command("say 你給我這種東西幹什麼？");
                return 0;
        }

        if( query("family/master_id", me) != query("id") )
                command("say 多謝這位" + RANK_D->query_respect(me) + "將靈蛇杖送回。");
        else
                command("say 很好，很好！");
        destruct(ob);
        return 1;
}
