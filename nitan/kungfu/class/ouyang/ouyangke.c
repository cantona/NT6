// ouyangke.c

#include <ansi.h>
#include "ouyang.h"

inherit F_MASTER;
inherit NPC;

void greeting(object ob);
int  accept_object(object who, object ob);
void do_back();
string ask_shenshe(string name);
string ask_job();
void reward_dest(object obj,object ob);
void destroy_dest(object obj,object ob);
void destroy_staff(object obj,object ob);
void thank_dest(object obj,object ob);

void create()
{
        seteuid(getuid());
        set_name("歐陽克", ({ "ouyang ke", "ouyang", "ke" }));
        set("long", "他一身飄逸的白色長衫，手搖摺扇，風流儒雅。\n");
        set("title", "歐陽世家少莊主");
        set("nickname", "玉面蛇心");
        set("gender", "男性");
        set("age", 27);
        set("attitude", "friendly");
        set("shen_type", -1);

        set("str", 25);
        set("int", 29);
        set("con", 25);
        set("dex", 26);

        set("qi", 1700);
        set("max_qi", 1700);
        set("jing", 800);
        set("max_jing", 800);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 50);

        set("combat_exp", 300000);

        set_skill("cuff",  130);
        set_skill("dodge", 120);
        set_skill("parry", 140);
        set_skill("force", 130);
        set_skill("staff", 100);
        set_skill("training", 80);
        set_skill("hamagong",130);
        set_skill("chanchu-bufa", 120);
        set_skill("lingshe-quan", 130);
        set_skill("baibian-daxue", 120);
        set_skill("poison", 120);
        set_skill("finger", 100);
        set_skill("shedu-qiqiao", 120);
        set_skill("medical", 150);
        set_skill("baituo-michuan", 150);
        set_skill("literate", 150);
        set_skill("shexing-diaoshou", 150);

        map_skill("force", "hamagong");
        map_skill("dodge", "chanchu-bufa");
        map_skill("cuff",  "lingshe-quan");
        map_skill("parry", "baibian-daxue");
        map_skill("staff", "baibian-daxue");
        map_skill("shedu-qiqiao", "shedu-qiqiao");
        map_skill("finger", "shedu-qiqiao");

        prepare_skill("finger", "shedu-qiqiao");
        prepare_skill("cuff", "lingshe-quan");

        create_family("歐陽世家", 6, "傳人");

        set("inquiry", ([
                "引路神蛇"   : (: ask_shenshe, "shenshe" :),
                "歐陽峯" : "他是我叔父。",
                "化屍粉" : "我只有一份化屍粉，不能給你。不過你要是給我一具屍體，我可以給你做些。",
                "活" : (: ask_job :),
                "job" : (: ask_job :),
        ]));

        set("chat_chance", 2);
        set("chat_msg", ({
                "歐陽克唱道：漂亮姑娘你請留步￣￣讓我多看你一眼￣￣\n",
                "歐陽克色迷迷地看着街邊的小姑娘。\n",
                "歐陽克把紙扇一展，轉過身去，深情地吟道：紅顏知己最難得￣\n",
        }) );

        set("master_ob",3);
        setup();
        carry_object("/d/baituo/obj/baipao")->wear();
        add_money("silver",10);
}

void init()
{
        object ob;

        ::init();

        if( interactive(ob = this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if (!ob || environment(ob) != environment()) return;

        if (check_family(ob, "歐陽世家"))
        {
                command("nod"+query("id", ob));
                return;
        }

        if( query("gender", ob) == "女性" )
        {
                if( query("per", ob)<22 )
                        return;

                if( query("sex/歐陽克", ob) )
                {
                        command("kiss"+query("id", ob));
                        command("say 怎麼樣，要不要再來幾次啊... 嘻嘻。");
                } else
                switch(random(3))
                {
                case 0: command("rose "+(string)query("id", ob));break;
                case 1: command("kiss "+(string)query("id", ob));break;
                case 2: command("love "+(string)query("id", ob));break;
                }

        }
        else
                say("歐陽克歎了一口氣説：這位"+RANK_D->query_respect(ob)+
                        "，你要是能給我弄一個女人來就好了。\n");
        return;
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        message_vision("$N道：好... 很好！\n", this_object());
        command("recruit "+query("id", ob));
        if( !query("special/shenshe", ob) )
        {
                command("say 你還不會使用引路神蛇吧？我告訴你口訣，你可不要忘記了！");
                command("whisper"+query("id", ob)+"口訣是：@#$%^&*，你"
                        "拿着引路神蛇到了西域沙漠就可以讓神蛇帶你回家了！");
                set("special/shenshe", 1, ob);
        }
}

int accept_fight(object ob)
{
        if( query("gender", ob) == "女性" )
        {
                message_vision("歐陽克擺擺手説道：這位"+RANK_D->query_respect(ob)+
                "，我怎能欺負女孩子呢！\n", ob);
                return 0;
        }

        return ::accept_fight(ob);
}

void do_back()
{
        remove_call_out("do_back");
        if (base_name(environment()) == query("startroom"))
                return;

        if (! living(this_object()) ||
            is_busy() || is_fighting())
        {
                call_out("do_back", 10 + random(10));
                return;
        }

        message_vision("$N輕搖羽扇，飄然而去。\n", this_object());
        move(query("startroom"));
        message_vision("$N輕搖羽扇，施施然的走了過來。\n", this_object());
}

string ask_shenshe(string name)
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "歐陽世家" )
                return RANK_D->query_respect(this_player()) +
                "，你並不是本山莊的人，此話從何説起？";

        if (  present("shen she", this_player()) )
                return RANK_D->query_respect(this_player()) +
                "你身上不是有神蛇嗎？怎麼又來要？真是貪得無厭！";

        ob = new("/d/baituo/obj/" + name);
        ob->move(this_player());

        message_vision("歐陽克給$N一條"+query("name", ob)+"。\n",this_player());
        return "此神蛇乃本山莊特有，切記不可給予他人！";
}

string ask_job()
{
        mapping job_stat;
        object ob2;
        object ob = this_player();
        object me = this_object();
        object guaishe,staff,here=environment(me);
                string dataname;
        int good_skill;

                dataname=query("id", ob);

        job_stat=query_temp("baituo/feeding", ob);

        if( query("family/family_name", ob) != "歐陽世家" )
                return RANK_D->query_rude(ob)+"莫非別有用心！\n";

        if( query_temp(dataname, me)>5 )
                       return "你已經跟我要了五隻蛇了都還沒還給我，我現在不放心給你蛇，你去冷靜一下吧。\n";


        if( ob->is_busy() ){
                command("hmm"+query("id", ob));
                return "你還在忙着幹別的事呢！\n";
        }

        if( job_stat ){
                command("hmm"+query("id", ob));
                return "你還沒幹完活呢!\n";
        }

        if( ob->query_skill("training") < 10 && random(4)!=0 ) {
                return "你的馴獸術太低，隨便拿只蛇練練去吧。\n";
        }

        ob->start_busy(random(4));
        good_skill=to_int(pow(to_float(query("combat_exp", ob)/100),1.0/3))*10*0.7*3/2;

        if( query("combat_exp", ob)>20000 && (ob->query_skill("force")<good_skill) && random(15)>0){
                command("say 你去好好練習一下蛤蟆功吧！");
                return "蛤蟆功是本派的獨門絕技，練成之後一定可以幫本少爺多抓幾個美女來！\n";
                }

        if( query("combat_exp", ob)>5000 && 
        query("max_neili", ob)<ob->query_skill("force")*7 && random(5)>0){
                command("say 你內力不夠，去好好打坐一下吧！");
                return "內力越高，蛤蟆功的威力就越大，嘿黑，和美眉在一起也。。。\n";
                }



        if( query_temp("job_pos", me) == 0){
                if(random(8)==1)
                set_temp("job_pos", 1, me);
                return "現在沒什麼事，你自個兒晃盪去吧。\n";
        }

        addn_temp("job_pos", -1, me);
                addn_temp(dataname, 1, me);

        command("nod");
        command("say好，我這裏有一隻奇毒的怪蛇，"+query("name", ob)+"你拿去好好調養。");
        command("say 這怪蛇吃鳥類、吸人血。越是所謂名門正派的高手的氣血越是滋養怪蛇。");
        command("hehe");
        command("say 它吃飽了以後，就會乖乖的爬進蛇杖裏成為天下最厲害的兵器。");


        guaishe = present("guai she",me );
        if(guaishe)destruct(guaishe);
        guaishe = present("guai she",me );
        if(guaishe)destruct(guaishe);
        ob2 = new("/d/baituo/npc/guaishe");
        ob2->move(me);
        ob2->set_owner(ob);
        set_temp("baituo/feeding", 1, ob);
        addn("bt/job", 1, ob);
        set("bt/time", time(), ob);
        command("giveguaisheto"+query("id", ob));
        guaishe = present("guai she",me );
        if(guaishe)command("drop guai she");

        staff = present("guai shezhang",here);
        if(!staff)staff=present("guai shezhang",ob);
        if(staff)destruct(staff);
        staff = new("/clone/weapon/gshezhan");
        staff->move(me);
        command("giveguaishezhangto"+query("id", ob));
        guaishe = present("guai shezhang",me );
        if(guaishe)command("drop guai shezhang");

        return "千萬別弄丟了！\n";
}

int accept_object(object me, object obj)
{
        object obn;
        int addition;
        object hsf, ob = this_player();

        if( query("id", obj) == "corpse" )
        {
                if( !query("family", me) || query("family/family_name", me) != "歐陽世家"){
                        command("say 你要我給你收屍不成？\n");
                        return 0;
                }
                if( query("family/master_name", me) != "歐陽鋒" && 
                        query("family/master_name", me) != "歐陽克"){
                        command("say 你還?竅攘泛黴Ψ虯傘n");
                        return 0;
                }

                if( query_temp("huashifen", me)){
                         command("say 化屍粉這樣烈性的藥物不要用得過多。\n");
                        return 0;
                 }

                message_vision("$N將" + obj->name() + "放在地上，從懷中掏出一份化屍粉撒在上面。\n",this_object());
                message_vision("片刻之間，" + obj->name() + "化作一灘黃水。黃水乾了後成了一堆發出熒熒的黃光的粉末。\n" ,obj);
                message_vision("$N將其中一份收在懷中，其餘的交給$n。\n",this_object(),me);
                command("say 你可以把化屍粉倒在屍體上，可即刻將其融化掉。");
                command("say 你也可以把它塗在繃帶上給人佯裝裹傷，待毒性深入其傷口，他就死定了。");
                command("hehe ouyang ke");

                hsf = new(DRUG_D("huashi"));
                hsf->set_amount(10);
                hsf->move(me);
                set_temp("huashifen", 1, me);
                return 1;
        }

        command( "say "+obj->name()+"?");

        if( query("id", obj) == "guaishe"){
                call_out("destroy_dest", 1, obj, ob);
                return 1;
        }

        if( query("id", obj) == "guaishezhang"){
                if( query("family/family_name", ob) == "歐陽世家"){
                        if( query("snake", obj)>0 )
                                call_out("reward_dest", 1, obj, ob);
                        else
                                call_out("destroy_staff", 1, obj, ob);
                }
                else {
                        call_out("thank_dest", 1, obj, ob);
                }
                return 1;
        }

        if( !obj->is_character() || query("gender", obj) != "女性" )
        {
                      command("say 我歐陽克不需要這件東西。");
                return 0;
        }

        if( query("born_family", obj) == "歐陽世家" )
        {
                command("kick"+query("id", me));
                command("slap"+query("id", me));
                command("say 我靠：你膽子可真不小，連我的胞妹你也敢欺負？");
                return 1;
        }

        if( query("short", environment(this_object())) == "麗春院" )
        {
                       command("say 我已經有女人了，你改天再送來吧。");
                return 0;
        }

        if( query("age", obj)<18 )
        {
                command("fear");
                command("say 未成年少女我怎敢要！");
                return 0;
        }

        if( query("age", obj)>29 )
        {
                command("say 這種老古董還是留給你自己吧！");
                return 0;
        }

        addition = 0;
        addition+=query("per", ob);
        if (userp(obj))
        {
                command("papapa");
                command("say 靠，你小子怎麼比我還色，這個女的還是你自己留着吧！");
                return 0;
        }

        if( query("sex/歐陽克", obj) >= 3 )
        {
                command("shake");
                command("say 這女人我已經玩膩了，你自個留着吧。");
                return 0;
        }

        if( !query("sex", ob) )
        {
                command("say 哇，這還是個處女，怎麼也得多給"
                        "你點辛苦費！");
                addition += 30;
        }

        obn=new("/clone/money/silver");
        obn->set_amount(20 + addition);
        obn->move(me);

        message_vision("$n把" + obj->name() + "交給了$N。\n",
                       this_object(), me);

        message_vision("$N一把把" + obj->name() + "攬在懷裏，對$n説："
                       "這點銀子是你的辛苦費，咱回頭見。\n説完，就攜着" +
                       obj->name() + "往麗春院奔去...\n",
                       this_object(), me);

        obj->move("/d/city/lichunyuan");
        move("/d/city/lichunyuan");

        message_vision("$N抱着昏迷不醒的$n走了進來。\n", this_object(), obj);

        addn("sex/歐陽克", 1, obj);
        addn("sex/times", 1, obj);
        if( query("sex/times", obj) == 1 )
                set("sex/first", "歐陽克", obj);

        obj->revive();
        tell_object(obj, HIY "你剛剛掙開眼睛，卻發現一個人"
                        "正抱着你，你大叫一聲，幾乎暈了過去。\n\n" NOR);
        command("kiss"+query("id", obj));
        command("say 嘻嘻，你慌什麼麼嘛，可是" + me->name() +
                "把你送過來的啊。");
        /*
        shout(sprintf(HIW "\n%s(%s)大聲喊道：救命啊... 救... 救命...\n\n" NOR,
                      obj->name()+HIW,query("id", obj)));
        */

        if (! userp(obj))
        {
                set("chat_chance", 15, obj);
                obj->set("chat_msg",({
                        obj->name() + "不住的抽泣。\n",
                        obj->name() + "嗚咽道：" + this_object()->name() + "，他... 他... 他這個壞東西。\n",
                        obj->name() + "哭了起來：我不想活了！\n",
                }) );
        }

        remove_call_out("do_back");
        call_out("do_back", 10 + random(10));
        return -1;
}

void reward_dest(object obj,object ob)
{
        string dataname;

        dataname=query("id", ob);

        command("pat"+query("id", ob));
        command("say"+query("name", ob)+"乾的還不錯，這樣多幹活，將來本少爺一定會賞你的！\n");

        if( query("gender", ob) == "女性" )
                command("kiss1"+query("id", ob));

        if( query_temp("baituo/feeding", ob) )
        {
                delete_temp("baituo/feeding", ob);
                addn_temp("job_pos", 1);
        }
        addn_temp(dataname, -1, this_object());

                if( query_temp(dataname, this_object())<1 )
                {
                        delete_temp(dataname, this_object());
                }

                destruct(obj);
}


void destroy_staff(object obj,object ob)
{
        command( "hmm" );
        command("kick"+query("id", ob));
        command( "say 怎麼就這樣還給我？蛇呢？小心少爺我賞你一蛇杖！" );
        command( "angry" );

        destruct(obj);
}

void destroy_dest(object obj,object ob)
{
        command( "hmm" );
        command("kick"+query("id", ob));
        command( "say 怎麼就這樣還給我？應該餵飽變成蛇杖再交給我。小心少爺我賞你給蛇吃！" );
        command( "angry" );

        if( query_temp("baituo/feeding", ob) )
        {
                delete_temp("baituo/feeding", ob);
                addn_temp("job_pos", 1);
        }
        destruct(obj);
}


void thank_dest(object obj,object ob)
{
        command( "ah");
        command( "jump");
        command( "say 本少爺的蛇杖？多謝啦！\n");
        destruct(obj);
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

        case "打字訣" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shedu-qiqiao/da",
                           "name"    : "打字訣",
                           "sk1"     : "shedu-qiqiao",
                           "lv1"     : 100,
                           "sk2"     : "force",
                           "lv2"     : 100,
                           "neili"   : 2000,
                           "gongxian": 200,
                           "shen"    : -4000, ]));
                break;

        case "煉毒" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shedu-qiqiao/liandu",
                           "name"    : "煉毒",
                           "sk1"     : "shedu-qiqiao",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "neili"   : 2000,
                           "gongxian": 300,
                           "shen"    : -6000, ]));
                break;

        default:
                return 0;
        }
}

