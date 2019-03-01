// ding.c 丁春秋

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

#include "xingxiu.h"
#include <ansi.h>

int ask_ding();
int ask_book();
int ask_poison();
int ask_staff();
int ask_job();
string ask_me();
string ask_du1();
string ask_du2();
string ask_xiangliao();
int do_answer(string arg);
void no_answer(object user);

#define ANTI_ROBOT "/kungfu/class/xingxiu/robot"
#define SUO "/clone/lonely/rousisuo"
#define YINLINFEN "/clone/medicine/poison/yinlinfen"
#define HONGLINFEN "/clone/medicine/poison/honglinfen"
#define DUCHONGFEN "/clone/medicine/poison/duchongfen"
#define BINGPOFEN "/clone/medicine/poison/bingpofen"

string ask_huoyan();
string ask_yinlinfen();
string ask_bingpofen();
string ask_duchongfen();
string ask_honglinfen();

void create()
{
        set_name("丁春秋", ({ "ding chunqiu", "ding" }));
        set("nickname", HIG "星宿老怪" NOR);
        set("long", @LONG
他就是星宿派開山祖師、令正派人士深惡痛絕的星宿老怪丁春秋。
可是他看起來形貌清奇，仙風道骨。
LONG );
        set("gender", "男性");
        set("age", 60);
        set("attitude", "friendly");
        set("class", "scholar");
        set("shen_type", -1);
        set("str", 25);
        set("int", 30);
        set("con", 38);
        set("dex", 38);

        set("max_qi", 6400);
        set("max_jing", 2900);
        set("neili", 7300);
        set("max_neili", 7300);
        set("jiali", 120);
        set("level", 30);
        set("combat_exp", 3850000);

        set_skill("force", 600);
        set_skill("huagong-dafa", 600);
        set_skill("guixi-gong", 600);
        set_skill("throwing", 600);
        set_skill("feixing-shu", 600);
        set_skill("dodge", 600);
        set_skill("zhaixing-gong", 600);
        set_skill("strike", 600);
        set_skill("chousui-zhang", 600);
        set_skill("claw", 600);
        set_skill("sanyin-zhua", 600);
        set_skill("whip", 600);
        set_skill("chanhun-suo", 600);
        set_skill("parry", 600);
        set_skill("staff", 600);
        set_skill("poison", 600);
        set_skill("tianshan-zhang", 600);
        set_skill("literate", 600);
        set_skill("medical", 600);
        set_skill("xingxiu-qishu", 600);
        set_skill("martial-cognize", 600);

        map_skill("force", "huagong-dafa");
        map_skill("dodge", "zhaixing-gong");
        map_skill("strike", "chousui-zhang");
        map_skill("claw", "sanyin-zhua");
        map_skill("whip", "chanhun-suo");
        map_skill("parry", "tianshan-zhang");
        map_skill("staff", "tianshan-zhang");
        map_skill("poison", "xingxiu-qishu");
        map_skill("throwing", "feixing-shu");

        prepare_skill("strike", "chousui-zhang");
        prepare_skill("claw", "sanyin-zhua");

        set("book_count", 1);
        set("zhen_count", 1);
        set("san_count", 1);
        set("xiangliao_count", random(10) + 10);

        set("inquiry", ([
                "工作" : (: ask_job :),
                "job" : (: ask_job :),
                "披風杖" : (: ask_staff :),
                "毒經"       : (: ask_me :),
                "星宿毒經"   : (: ask_me :),
                "碧磷針"     : (: ask_du1 :),
                "香料"       : (: ask_xiangliao :),
                "逍遙三笑散" : (: ask_du2 :),
                "神木王鼎" : (: ask_ding : ),
                "冰蠶劇毒" : (: ask_poison :),
                "解毒" : (: ask_poison :),
                "book" : (: ask_book :),
                "易筋經殘篇" : (: ask_book :),
//                "火燄" : (: ask_huoyan :),
                "銀磷粉"        : (:ask_yinlinfen:),
                "yinlin fen" : (:ask_yinlinfen:),
                "紅磷粉" : (:ask_honglinfen:),
                "honglin fen" : (:ask_honglinfen:),
                "冰魄粉" : (:ask_bingpofen:),
                "bingpo fen" : (:ask_bingpofen:),
                "毒蟲粉": (:ask_duchongfen:),
                "duchong fen": (:ask_duchongfen:),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                //(: perform_action, "staff.fugu" :),
                //(: perform_action, "staff.xue" :),
                //(: perform_action, "strike.tao" :),
                (: perform_action, "strike.dan" :),
                (: perform_action, "strike.tao" :),
                (: perform_action, "strike.shi" :),
                (: perform_action, "claw.zhua" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        create_family("星宿派", 1, "開山祖師");
        set("class", "taoist");

        set_temp("apply/damage", 180);
        set_temp("apply/armor", 400);
        set_temp("apply/attack", 250);
        set_temp("apply/dodge", 250);
        set_temp("apply/parry", 250);

        set("master_ob", 5);
        setup();
        //carry_object("/clone/weapon/gangzhang")->wield();
        carry_object("/clone/cloth/cloth")->wear();
        //set_temp("handing", carry_object("/clone/misc/duwan"));

}

void init()
{
        object me;
        object ob,ob1;
        string poison;

        ::init();

        me = this_player();

        if (! interactive(me))
                return;

        add_action("do_answer", "answer", 1);

        if( interactive(ob=this_player()) && ob->query_condition("bingcan_posion") )
        {
                   command("? "+query("id", ob));
                   command("say "+query("name", ob)+"好徒兒,你似乎中了冰蠶劇毒。\n");
        }

        if( interactive(ob=this_player()) && query("family/master_id", ob) == "ding chunqiu"
        && (!present("yu di", this_player()))){
                ob1=new("/d/xingxiu/obj/yudi");
                ob1->move(this_player());
                command("say 這只玉笛是咱們星宿弟子的護身符，你好好拿著，不可弄丟。");
                write("丁春秋給你一只玉笛。\n");
        }

        /*
        if (living(this_object()) && present("shenmuwang ding", me))
        {
                command("say 好家伙，原來你偷了我的神木王鼎！受死吧！");
                kill_ob(me);
                return;
        }
        */

        add_action("do_flatter", "flatter");
}

int ask_book()
{
        object ob;
       object me=this_player();

       if( query("canbook", me) == 1 && (!present("yijinjing",me))){
                tell_object(me,"丁春秋說道：“好徒兒，還沒參透這本易筋經的奧秘麼？\n");
                tell_object(me,"那好吧。這本副本給你，拿回去好好參悟吧！\n");
                tell_object(me,"徒兒你一定要記住，千萬配合神木王鼎一起修煉，要不然很容易走火入魔。”\n");
                ob=new("/clone/book/yjj_book2.c");

                ob->move(me);
                write("丁春秋給你一本易筋經。\n");
                return 1;
        }
        else
                return 0;
}

int ask_ding()
{
        object ob;
        object me=this_player();
        if( query("ask/ding", me) == 1 && (!present("shenmuwang ding",me)) && query("family/master_id", me) == "ding chunqiu" )
        {
                tell_object(me,"幸虧你把阿紫捉回來，神木王鼎才得以失而復返，你既然需要就拿去吧。\n");
                ob=new("/clone/misc/swmuding");
                ob->move(me);
                delete("ask/ding", me);
                return 1;
        }
        else return 0;

}

int ask_poison()
{
        object ob=this_player();
        if( query("family/master_id", ob) == "ding chunqiu" && ob->query_condition("bingcan_poison") )
        {
        tell_object(ob,HIY "要解冰蠶劇毒有兩種辦法，如果有易筋經殘篇，
        然後配合神木王鼎修煉化功大法，這點毒算得了什麼！
        可惜啊，那本殘篇至盡仍然下落不明，如果你能找到那
        本書的話，我看了以後必然能彌補化功大法的缺憾。除
        此之外，只能靠藥物逃過此劫了！\n" NOR);
        return 1; }
        else
        return 0;
}

int do_answer(string arg)
{
        int result;
        object me = this_object(), user = this_player();
        result = ANTI_ROBOT->do_answer(arg, user, me);

        if (result == 2) {
                command("whisper "+query("id", user)+"好！好！好！老仙現在放心了。");
                command("say " + user->name(1) + "，你有什麼問題只管問我吧！");
                set("passed_ding", 1, user);
                return 1;
        }

        if (result == -1) {
                command("hammer "+query("id", user));
                command("say " + user->name(1) + "你這個畜生！居然敢欺騙老仙，給我滾一邊去。");
                addn("ding_robot", 1, user);
                set("robot_ding",query("mud_age",  user)+query("ding_robot", user)*600, user);
                return 1;
        }

        return result;
}

void no_answer(object user)
{
        if( objectp(present(query("id", user),environment()))){
        command("beep "+query("id", user));
        command("heihei "+query("id", user));
        command("say " + user->name(1) + "，你以為你裝馬虎我就治不了你了嗎！");
        command("say 給我滾一邊去吧！");
        }
else {
        command("tell"+query("id", user)+""+user->name(1)+"，你以為你裝馬虎我就治不了你了嗎！");
        command("tell"+query("id", user)+"你暫時用不著給老仙做事了！");
}
        addn("ding_robot", 1, user);
        set("robot_ding",query("mud_age",  user)+query("ding_robot", user)*600, user);
}

void attempt_apprentice(object me)
{

        if( query("shen", me)>-12000 )
        {
                command("say 老仙我越看你越象白道派來臥底的。");
                return;
        }

        if( query("combat_exp", me)<300000 )
        {
                command("say 你這點微末道行如何能學到老仙的神妙功夫。");
                return;
        }

        if (me->query_skill("chousui-zhang", 1) < 120)
        {
                command("say 你抽髓掌都沒熟練，居然還有臉來見我？");
                return;
        }

        if ((int)me->query_skill("poison", 1) < 120)
        {
                command("say 你毒技都沒學明白，還有臉來見我？");
                return;
        }

        if( query_temp("pending/flatter", me) )
        {
                command("say 你如此不把老仙放在眼裡，老仙怎會收你？");
                return;
        } else
        {
                command("say 我星宿老仙比起古往今來的聖人怎麼樣啊？");
                message_vision("星宿老怪微閉雙眼，手捻長須，一副等人拍馬(flatter)的樣子。\n",
                this_player());
                set_temp("pending/flatter", 1, me);
        }
}

int do_flatter(string arg)
{
        if( !query_temp("pending/flatter", this_player()) )
                return 0;

        if (! arg) return notify_fail("你說老仙什麼？\n");
        set_temp("pending/flatter", 0, this_player());
        message_vision("$N大聲說道：" + arg + "\n", this_player());
        if( strsrch(arg, "星宿老仙") >=0 && (strsrch(arg, "德配天地") >=0
         || strsrch(arg, "威震寰宇") >=0 || strsrch(arg, "古今無比") >=0 )) {
                command("smile");
                command("say 這還差不多。\n");
                welcome(this_player());
                command("recruit "+query("id", this_player()));
        } else
        {
                command("say 你如此不把我放在眼裡，我怎能收你？");
        }
        return 1;
}

// 星宿老仙，德配天地，威震寰宇，古今無比
string ask_me()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "星宿派" )
                return RANK_D->query_respect(this_player()) + "與本派素無來往，不知此話從何談起？\n";

        if (query("book_count") < 1)
                return "你來晚了，本派的內功心法不在此處。\n";

        addn("book_count", -1);
        ob = new("/clone/book/dujing_2");
        ob->move(this_player());
        return "好吧，這本「星宿毒經」你拿回去好好鑽研。\n";
}

string ask_du1()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "星宿派" )
                return RANK_D->query_respect(this_player()) + "與本派素無來往，不知此話從何談起？\n";

        if (this_player()->query_skill("poison", 1) < 50)
                return "你的毒技火候未到，用不了這種東西。\n";

        if (query("zhen_count") < 1)
                return "你來晚了，碧磷針都發完了。\n";

        addn("zhen_count", -1);
        ob = new("/d/xingxiu/obj/bilinzhen");
        ob->move(this_player());
        return "好吧，那你就先用這些針吧。\n";
}

string ask_du2()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "星宿派" )
                return RANK_D->query_respect(this_player()) + "與本派素無來往，不知此話從何談起？\n";

        if (this_player()->query_skill("poison", 1)<100)
                return "你的毒技火候未到，用不了這種東西。\n";

        if (query("san_count") < 1)
                return "你來晚了，現在沒什麼剩的了。\n";

        addn("san_count", -1);
        ob = new("/d/xingxiu/obj/sanxiaosan");
        ob->move(this_player());
        return "好吧，這包毒藥你拿回去善加利用吧。\n";
}

string ask_xiangliao()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "星宿派" )
                return RANK_D->query_respect(this_player()) + "與本派素無來往，不知此話從何談起？\n";

        if (is_busy() || is_fighting())
                return "等會兒，沒看我這正忙著呢麼？\n";

        if( query_temp("get_xiangliao", this_player()) )
                return "剛才不是給了你嗎？不會這麼快就用完了吧？\n";

        if (this_player()->query_skill("poison", 1) < 40)
                return "你的毒技火候太差，還是練練再說吧！\n";

        if (query("xiangliao_count") < 1)
                return "你來晚了，現在沒什麼剩下的香料了，你還是去倉庫找找看吧！\n";

        addn("xiangliao_count", -1);
        ob = new("/clone/misc/xiangliao");
        ob->set_amount(random(50) + 100);
        ob->move(this_player());
        start_busy(2);
        set_temp("get_xiangliao", 1, this_player());
        call_out("clear_xiangliao_flag", 180);
        return "好吧，這些香料你拿去慢慢用吧。\n";
}

void reset()
{
        set("book_count", 1);
        set("zhen_count", 1);
        set("san_count", 3);
        set("zhen_count", 7);
        set("wxs_count",3);
        set("xiangliao_count", random(10) + 10);
}

/*
void unconcious()
{
        die();
}
*/

int accept_ask(object me, string topic)
{
        switch(topic)
        {
             case "歷練" :
             case "歷煉" :
             case "鍛煉" :
                 return QUEST_D->accept_ask(this_object(), me, topic);

             case "奪魂勢":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/chanhun-suo/duo",
                                 "name"     :  "奪魂勢",
                                 "sk1"      :  "chanhun-suo",
                                 "lv1"      :  100,
                                 "sk2"      :  "force",
                                 "lv2"      :  130,
                                 "shen"     :  -10000,
                                 "family/gongji" :  80,
                                 "force"    :  80 ]));
                  break;

             case "煉心彈":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/chousui-zhang/dan",
                                 "name"     :  "煉心彈",
                                 "sk1"      :  "chousui-zhang",
                                 "lv1"      :  140,
                                 "sk2"      :  "force",
                                 "lv2"      :  140,
                                 "sk3"      :  "poison",
                                 "lv3"      :  140,
                                 "sk4"      :  "throwing",
                                 "lv4"      :  140,
                                 "shen"     :  -22000,
                                 "neili"    :  1800,
                                 "family/gongji" :  950 ]));
                  break;

             case "滿天花雨":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/feixing-shu/hua",
                                 "name"     :  "滿天花雨",
                                 "sk1"      :  "feixing-shu",
                                 "lv1"      :  100,
                                 "sk2"      :  "force",
                                 "lv2"      :  120,
                                 "neili"    :  500,
                                 "family/gongji" :  300 ]));
                  break;

             case "碧燄滔天":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/chousui-zhang/tao",
                                 "name"     :  "碧燄滔天",
                                 "sk1"      :  "chousui-zhang",
                                 "lv1"      :  220,
                                 "sk2"      :  "poison",
                                 "lv2"      :  250,
                                 "sk3"      :  "huagong-dafa",
                                 "lv3"      :  220,
                                 "shen"     :  -38000,
                                 "neili"    :  3000,
                                 "family/gongji" :  1200 ]));
                  break;

             case "彈射火燄":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/chousui-zhang/huoyan",
                                 "name"     :  "彈射火燄",
                                 "sk1"      :  "chousui-zhang",
                                 "lv1"      :  140,
                                 "sk2"      :  "force",
                                 "lv2"      :  140,
                                 "sk3"      :  "poison",
                                 "lv3"      :  140,
                                 "sk4"      :  "throwing",
                                 "lv4"      :  140,
                                 "shen"     :  -22000,
                                 "neili"    :  1800,
                                 "family/gongji" :  950 ]));
                  break;

             case "彈射火球":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/chousui-zhang/huoqiu",
                                 "name"     :  "彈射火球",
                                 "sk1"      :  "chousui-zhang",
                                 "lv1"      :  140,
                                 "sk2"      :  "force",
                                 "lv2"      :  140,
                                 "sk3"      :  "poison",
                                 "lv3"      :  140,
                                 "sk4"      :  "throwing",
                                 "lv4"      :  140,
                                 "shen"     :  -22000,
                                 "neili"    :  1800,
                                 "family/gongji" :  950 ]));
                  break;

             case "彈射碧燄":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/chousui-zhang/biyan",
                                 "name"     :  "彈射碧燄",
                                 "sk1"      :  "chousui-zhang",
                                 "lv1"      :  140,
                                 "sk2"      :  "force",
                                 "lv2"      :  140,
                                 "sk3"      :  "poison",
                                 "lv3"      :  140,
                                 "sk4"      :  "throwing",
                                 "lv4"      :  140,
                                 "shen"     :  -22000,
                                 "neili"    :  1800,
                                 "family/gongji" :  1000 ]));
                  break;

             case "彈射火浪":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/chousui-zhang/huolang",
                                 "name"     :  "彈射火浪",
                                 "sk1"      :  "chousui-zhang",
                                 "lv1"      :  200,
                                 "sk2"      :  "force",
                                 "lv2"      :  200,
                                 "sk3"      :  "poison",
                                 "lv3"      :  200,
                                 "sk4"      :  "throwing",
                                 "lv4"      :  200,
                                 "shen"     :  -50000,
                                 "neili"    :  1800,
                                 "family/gongji" :  2000 ]));
                  break;

             case "柔絲索" :
                return MASTER_D->give_item(me, this_object(),
                               (["item"     :  SUO,
                                 "master"   :  1,
                                 "sk1"      :  "chanhun-suo",
                                 "lv1"      :  140,
                                 "shen"     :  -30000 ]));
                  break;

             default :
                  return 0;

        }
}

void clear_xiangliao_flag()
{
        if( query_temp("get_xiangliao", this_player()) )
               delete_temp("get_xiangliao", this_player());

        return;
}

int ask_staff()
{
        object me=this_player();
        object waguan;
        mapping fam;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "星宿派"){
                command("?");
                return 1;
        }

        if( query("tianshan", me) == 1){
                command("say 不要開這種無聊的玩笑。");
                return 1;
        }

        if (me->query_skill("pixie-jian",1)>=10){
                command("hmm");
                command("say 你陰陽失調，不宜修煉此功。");
                return 1;
        }

        if (me->query_skill("staff", 1) < 200){
                command("say 你基本杖法的修為不夠。");
        }

        if (me->query_str() < 50) {
                command("say 你的體能太低了，好好鍛煉鍛煉在來問我吧。");
                return 1;
        }

        if (me->query_con() < 50) {
                command("say 你的內功修為太低了，好好鍛煉鍛煉在來問我吧。");
                return 1;
        }

        if (me->query_int() < 35) {
                command("sneer");
                command("say 我派武學講究領悟，你悟性太差，回去好好讀一下書吧。");
                return 1;
        }


                message_vision(HIG"$N微微一笑，將$n拉到一旁，慢慢地解釋天山披風杖這一招。\n", this_object(), this_player());
                message_vision(HIG"$n在$N的講解下，對天山杖法又有了一層新的理解。", this_object(), this_player());
                set("tianshan", 1, me);
                tell_object(this_object(),HIC"你的天山杖法進步了！");
                me->add_skill("tianshan-zhang", 10);
                return 1;


        return 1;
}

int ask_job(){

        object me=this_player();
        object waguan;
        mapping fam;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "星宿派"){
                command("?");
                return 0;
        }

        if( query("robot_ding", me)>query("mud_age", me)){
                command("say 哼！上次你騙老仙的事，老仙還沒有和你算帳呢！你現在還有臉問這問那！");
                command("say 你先給我回去好好反省自己一下，以後再來！");
                return 1;
        }

        if( query("robot_answer", me))return notify_fail("快給老夫把先前的問題答了！\n");

        if( random(4) == 1 && !query("passed_ding", me)){
                command("say 昨夜老夫受仙人告戒，說你" + me->name(1) + "做事不老實。用寫機器來欺騙老夫");
                command("say 所以老夫現在要問你一問，你聽好了！");
                ANTI_ROBOT->get_question(me, this_object());
                return 1;
        }

        if( query_temp("xx_job", me) == 1){
                command("say 好小子，上一個工作沒有完成就敢來問我工作。");
                return 1;
        }
        command ("say 「老仙我最近練功需要一些毒丹，你到後山拿些來給我吧。」");
        waguan=new("/d/xingxiu/obj/waguan");
        set_temp("xx_job", 1, me);
        if (!present("wa guan", me)) waguan->move(me);
            message_vision("丁春秋順手從身後架子上取出一個小瓦罐扔給你。\n", me);
                command ("say 「快去快回，路上小心。」");
        return 1;

}

int accept_object(object who, object ob){

        object me=this_player();
        mapping fam;
        int pot, exp;
        string msg;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "星宿派"){
                command("?");
                return 0;
        }

        if( query("id", ob) == "du dan"){

              if( query_temp("xx_job", this_player()) != 1 || query("player", ob) != query("id", me)){
                        command("hehe");
                        return 0;
                } else {
                     command("pat "+query("id", this_player()));
                        command("say 好樣的，老仙我越看你越順眼了。\n");
                        // exp triple
                        pot = random(100)+100;
                        exp = 200 + random( 50 );

        if( query("combat_exp", me)>6400000 )
        {
                pot /= 2;
                exp = exp / 2;
        }
                        addn("combat_exp", exp, me);
                        addn("potential", pot, me);
                        if( query("potential", me)>me->query_potential_limit() )
                                set("potential", me->query_potential_limit(), me);
                        msg = sprintf("你抓蟲得到 %d 點經驗和 %d 點潛能。\n", exp, pot);
                        tell_object(me,msg);
                        delete_temp("xx_job", me);
                        delete_temp("found", me);
                        delete_temp("bug_hold", me);
                        delete_temp("bug_out", me);
                        delete("passed_ding", me);
                        call_out("destob",2,ob);
                        return 1;
                }
        }
        if( query("id", ob) == "a zi"){

                        command("say 太好了，終于有把這個孽徒抓回來了！\n");
                        command("say 來人哪！把這個孽徒給我先關到牢房裡面去！\n");
                        tell_object(me,"門外進來兩名星宿弟子把阿紫拖出去了。\n");
                        pot = random(300)+80;
                        exp = 500 + random( 20 );
                        addn("combat_exp", exp, me);
                        addn("potential", pot, me);
                        if( query("potential", me)>me->query_potential_limit() )
                                set("potential", me->query_potential_limit(), me);
                        set("ask/ding", 1, me);
                        destruct(ob);
                        return 1;
        }
        if( query("id", ob) == "noname book" )
        {
        if( !query("my_owner", ob) || query("my_owner", ob) != me )
                return notify_fail("丁春秋怒道：這是你哪裡揀來的破東西，還不扔了！\n");
                // if(me->query("ask/ding")==1)
                if(me)
                {
                        tell_object(me,"這……這是易筋經殘篇！！好
徒兒，咱們星宿一統江湖的日子來了！此書既然由你取得，日後你當然也可
以修習，待為師將其譯出並抄錄副本。咱們師徒共同研究！\n");
                        set("canbook", 1, me);
                        return 1;
                }
                else
                return notify_fail("丁春秋怒道：“我老仙是何等身份？！怎會收你這種垃圾，我不要！”\n");
        }

        if( query("id", ob) == "ling pai"){
                if( query("player", ob) != query("id", me)){
                        command("hehe");
                        return 0;
                } else {
                        command("hehehe");
                        command("say 好樣的，讓這些自稱名門正派的知道老仙的利害。\n");
                        if( query("menpai", ob) == "huashan" || query("menpai", ob) == "quanzhen" )
                                exp = 100 + random( 50 );
                        else if( query("menpai", ob) == "mingjiao"){
                                command("say 嗯。。明教竟然也跟我幹上了。\n");
                                //exp triple
                                exp = 120 + random( 60 );
                        } else        exp = 70+random(30);
        if( query("combat_exp", me)>6400000 )
        {
                exp = exp / 2;
        }
                        addn("combat_exp", exp, me);
                        msg = sprintf("你撿令牌得到 %d 點經驗。\n", exp);
                        tell_object(me,msg);
                        call_out("destob",1,ob);
                        delete("passed_ding", me);
                        return 1;
                }
        }

        return ::accept_object(who, ob);
}

void destob(object ob){
        destruct(ob);
}

string ask_huoyan()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || 
                fam["family_name"] != "星宿派")
                return RANK_D->query_respect(this_player()) + "與本派素無來往，不知此話從何談起？";
        if (this_player()->query_skill("poison",1)<100)
                return "你的毒技火候未到，用不了這種東西。";
        if (query("huoyan_count") < -100) return "你來晚了，現在沒什麼剩的了。";
        addn("huoyan_count", -1);
        ob = new("/d/xingxiu/npc/obj/huoyan.c");
        ob->move(this_player());
        return "好吧，我就給你堆火燄吧。";
}

string ask_yinlinfen()
{
        mapping fam;
        object ob;
        object owner;
        object temp;
        object me=this_player();
        if( !(fam=query("family", me)) || 
                fam["family_name"] != "星宿派")
                return RANK_D->query_respect(this_player()) + "與本派素無來往，不知此話從何談起？";
        if (me->query_skill("poison",1)<100)
                return "你的毒技火候未到，用不了這種東西。";
        ob=new(YINLINFEN);
        if (temp=ob->violate_unique())
         {
                 destruct(ob);
                 ob=temp;
          owner = environment(ob);
          if (owner == me)
                return query("name",ob)+"不就在你手中嗎？";
          if (objectp(owner) && owner != this_object())
     {
      if (! owner->is_character())
           return "你來晚了，"+query("name", ob)+"現在不在我手中。";
      if( query("family/family_name", owner) == "星宿派" )
           return query("name",ob)+"現在在本派" + query("name",owner) +"手中，你要用就去找他吧。";
      else
           return "我正為此事擔憂呢，"+query("name", ob)+"現在落入了"+query("name", owner)+"之手，你快去把他殺了，把東西取回來！";
     }
  }
        command("nod");
  ob->move(this_object());
  command("give fen to "+query("id", me));
  return "這"+query("name", ob)+"你便拿去，希望你能好好利用。";
}

string ask_duchongfen()
{
        mapping fam;
        object ob;
        object owner;
        object temp;
        object me=this_player();
        if( !(fam=query("family", me)) || 
                fam["family_name"] != "星宿派")
                return RANK_D->query_respect(this_player()) + "與本派素無來往，不知此話從何談起？";
        if (me->query_skill("poison",1)<100)
                return "你的毒技火候未到，用不了這種東西。";
        ob=new(DUCHONGFEN);
        if (temp=ob->violate_unique())
         {
                 destruct(ob);
                 ob=temp;
          owner = environment(ob);
          if (owner == me)
                ob->query("name",ob)+"不就在你手中嗎？";
          if (objectp(owner) && owner != this_object())
     {
      if (! owner->is_character())
           return "你來晚了，"+query("name", ob)+"現在不在我手中。";
      if( query("family/family_name", owner) == "星宿派" )
           return query("name",ob)+"現在在本派" + query("name",owner) +"手中，你要用就去找他吧。";
      else
           return "我正為此事擔憂呢，"+query("name", ob)+"現在落入了"+query("name", owner)+"之手，你快去把他殺了，把東西取回來！";
     }
  }
        command("nod");
  ob->move(this_object());
   command("give fen to "+query("id", me));
  return "這"+query("name", ob)+"你便拿去，希望你能好好利用。";
}

string ask_honglinfen()
{
        mapping fam;
        object ob;
        object owner;
        object temp;
        object me=this_player();
        if( !(fam=query("family", me)) || 
                fam["family_name"] != "星宿派")
                return RANK_D->query_respect(this_player()) + "與本派素無來往，不知此話從何談起？";
        if (me->query_skill("poison",1)<100)
                return "你的毒技火候未到，用不了這種東西。";
        ob=new(HONGLINFEN);
        if (temp=ob->violate_unique())
         {
                 destruct(ob);
                 ob=temp;
          owner = environment(ob);
          if (owner == me)
                return query("name",ob)+"不就在你手中嗎？";
          if (objectp(owner) && owner != this_object())
     {
      if (! owner->is_character())
           return "你來晚了，"+query("name", ob)+"現在不在我手中。";
      if( query("family/family_name", owner) == "星宿派" )
           return query("name",ob)+"現在在本派" + query("name",owner) +"手中，你要用就去找他吧。";
      else
           return "我正為此事擔憂呢，"+query("name", ob)+"現在落入了"+query("name", owner)+"之手，你快去把他殺了，把東西取回來！";
     }
  }
        command("nod");
  ob->move(this_object());
   command("give fen to "+query("id", me)); 
  return "這"+query("name", ob)+"你便拿去，希望你能好好利用。";
}

string ask_bingpofen()
{
        mapping fam;
        object ob;
        object owner;
        object temp;
        object me=this_player();
        if( !(fam=query("family", me)) || 
                fam["family_name"] != "星宿派")
                return RANK_D->query_respect(this_player()) + "與本派素無來往，不知此話從何談起？";
        if (me->query_skill("poison",1)<100)
                return "你的毒技火候未到，用不了這種東西。";
        ob=new(BINGPOFEN);
        if (temp=ob->violate_unique())
         {
                 destruct(ob);
                 ob=temp;
          owner = environment(ob);
          if (owner == me)
                return query("name",ob)+"不就在你手中嗎？";
          if (objectp(owner) && owner != this_object())
     {
      if (! owner->is_character())
           return "你來晚了，"+query("name", ob)+"現在不在我手中。";
      if( query("family/family_name", owner) == "星宿派" )
           return query("name",ob)+"現在在本派" + query("name",owner) +"手中，你要用就去找他吧。";
      else
           return "我正為此事擔憂呢，"+query("name", ob)+"現在落入了"+query("name", owner)+"之手，你快去把他殺了，把東西取回來！";
     }
  }
        command("nod");
  ob->move(this_object());
   command("give fen to "+query("id", me)); 
  return "這"+query("name", ob)+"你便拿去，希望你能好好利用。";
}
