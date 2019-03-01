// This program is a part of NT MudLIB

#include <ansi.h>
#include "quanzhen.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

string ask_me();
string ask_miji();
mixed ask_skill1();
mixed ask_skill2();
string ask_array();
string ask_shu();
void create()
{
        set_name("馬鈺", ({"ma yu", "ma"}));
        set("gender", "男性");
        set("age", 42);
        set("class", "taoist");
        set("nickname",MAG"丹陽子"NOR);
        set("long",
                "他就是王重陽的大弟子，全真七子之首，丹陽子馬鈺馬真人。\n"
                "他慈眉善目，和藹可親，正笑著看著你。\n");
        set("attitude", "peaceful");
        set("shen_type",1);
        set("str", 28);
        set("int", 32);
        set("con", 31);
        set("dex", 30);

        set("title","全真七子之首");

        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "sword.ding" :),
                (: perform_action, "sword.ding" :),
                (: perform_action, "sword.ding" :),
        }));

        set("qi", 4500);
        set("max_qi", 4500);
        set("jing", 2200);
        set("max_jing", 2200);
        set("neili", 4700);
        set("max_neili", 4700);
        set("jiali", 100);
        set("level", 18);
        set("combat_exp", 1400000);

        set_skill("force", 180);
        set_skill("quanzhen-xinfa", 180);
        set_skill("sword", 170);
        set_skill("quanzhen-jian",170);
        set_skill("dodge", 180);
        set_skill("jinyan-gong", 180);
        set_skill("parry", 180);
        set_skill("literate",100);
        set_skill("strike", 180);
        set_skill("chongyang-shenzhang", 180);
        set_skill("haotian-zhang", 180);
        set_skill("finger",180);
        set_skill("zhongnan-zhi", 180);
        set_skill("taoism",150);
        set_skill("medical", 210);
        set_skill("liandan-shu", 210);
        set_skill("cuff",200);
        set_skill("whip",200);
        set_skill("chunyang-quan",200);
        set_skill("duanyun-bian",200);
        set_skill("array",150);
        set_skill("beidou-zhenfa", 150);

        map_skill("force", "quanzhen-xinfa");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jian");
        map_skill("finger", "zhongnan-zhi");
        map_skill("strike", "haotian-zhang");
        prepare_skill("finger", "zhongnan-zhi");
        prepare_skill("strike","haotian-zhang");

        create_family("全真教", 2, "弟子");

        set("book_count",1);
        set("miji_count",1);
        set("inquiry", ([
                "全真教" :  "我全真教是天下道家玄門正宗。\n",
                "秘籍" : (: ask_miji :),
                "金雁功" : (: ask_me :),
                "金雁圖譜" : (: ask_me :),
                "鷹飛雁舞" : (: ask_skill1 :),
                "天罡北鬥陣" : (: ask_array :),
                "北鬥七星陣" : (: ask_array :),
                "秘籍"      : (: ask_shu :),
                "鞭法總訣"   : (: ask_shu :),
                "shu" : (: ask_shu :),
                "玄門金鎖" : (: ask_skill2 :),
        ]) );

        set("master_ob",3);
        setup();

        carry_object("/clone/weapon/changbian")->wield();
        carry_object("/clone/weapon/changjian");
        carry_object(__DIR__"obj/greenrobe")->wear();

}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if ((int)ob->query_skill("quanzhen-xinfa",1) < 100 )
        {
                command("say 你的本門內功心法火候不足,難以領略更高深的武功。");
                return;
        }
        if( query("shen", ob)<10000 )
        {
                command("say 行俠仗義我輩學武人需銘記在心，這點你做的可不夠啊！\n");
                return;
        }
        command("pat"+query("id", ob));
        command("say 好吧，我就收下你這個徒弟了。");
        command("recruit "+query("id", ob));
}

string ask_me()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "全真教" )
                return RANK_D->query_respect(this_player()) +
                "與本教毫無瓜葛，我教的武功典籍可不能交給你。";
        if (query("book_count") < 1)
                return "你來晚了，金雁圖譜已經被人取走了。";
        addn("book_count", -1);
        ob = new("/clone/book/jinyantu");
        ob->move(this_player());
        return "好吧，這本「金雁圖譜」你拿回去好好研讀。";

}
string ask_shu()
{
        object ob;

        if( query("family/master_id", this_player()) != "mayu" )
                return RANK_D->query_respect(this_player()) +
                "非我弟子，不知此話從何談起？";
        if (query("shu_count") < 1)
                return "你來晚了，本派的秘籍不在此處。";
        addn("shu_count", -1);
        ob = new("/clone/book/whip");
        ob->move(this_player());
        command("rumor"+query("name", this_player())+"拿到鞭法總訣啦。\n");
        return "好吧，這本「鞭法總訣」你拿回去好好鑽研。";
}
string ask_miji()
{
        mapping fam;
        object ob, *obs,ob2 ;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "全真教" )
                return RANK_D->query_respect(this_player()) +
                "與本派素無來往，不知此話從何談起？";

        if (query("miji_count") < 1)
                return "你來晚了，本派的鞭法秘籍不在此處。";

        obs = filter_array(children("/d/quanzhen/obj/whip_book"), (: clonep :));
                  if (sizeof(obs) > 5)
                return "你來晚了，本派的鞭法秘籍不在此處。";

        ob=new("/d/quanzhen/obj/whip_book");
        ob->move(this_player());
        addn("miji_count", -1);
        // command ("rumor "+this_player()->query("name")+"弄到了一冊丹陽鞭法譜。");
        return "好吧，這本「丹陽鞭法譜」你拿回去好好鑽研。";
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/jinyan-gong/yanwu", me) )
                return "這招我不是已經教會你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與貧道素不相識，不知此話從何說起？";

        if (me->query_skill("jinyan-gong", 1) < 1)
                return "你連金雁功都沒學，何談絕招可言？";

        if( query("family/gongji", me)<50 )
                return "你在我全真教內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)<3000 )
                return "你的俠義正事還做得不夠，這招我暫時還不能傳你。";

        if (me->query_skill("jinyan-gong", 1) < 60)
                return "你的金雁功不夠嫻熟，練高點再來吧。";

        if (me->query_skill("force") < 80)
                return "你的內功修為不夠，修煉高後再來找我吧。";

        message_sort(HIY "\n$n" HIY "對$N" HIY "點了點頭，當下更不答"
                     "話，但見身影時如鷹擊長空、時如群雁飛舞，令人眼"
                     "花撩亂，煞是好看。\n\n" NOR, me,
                     this_object());

        command("nod");
        command("say 這招很簡單，稍加練習便成。");
        tell_object(me, HIC "你學會了「鷹飛雁舞」。\n" NOR);
        if (me->can_improve_skill("dodge"))
                me->improve_skill("dodge", 1500000);
        if (me->can_improve_skill("jinyan-gong"))
                me->improve_skill("jinyan-gong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/jinyan-gong/yanwu", 1, me);
        addn("family/gongji", -50, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/jinguan-yusuo/suo", me) )
                return "這招我不是已經教會你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與貧道素不相識，不知此話從何說起？";

        if (me->query_skill("jinguan-yusuo", 1) < 1)
                return "你連金關玉鎖都沒學，何談絕招可言？";

        if( query("family/gongji", me)<400 )
                return "你在我全真教內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)<50000 )
                return "你的俠義正事還做得不夠，這招我暫時還不能傳你。";

        if (me->query_skill("jinguan-yusuo", 1) < 150)
                return "你的金關玉鎖不夠嫻熟，練高點再來吧。";

        if (me->query_skill("force") < 200)
                return "你的內功修為不夠，修煉高後再來找我吧。";

        message_sort(HIY "\n$n" HIY "點了點頭，說道：“我給你演示一遍，可"
                     "看仔細了。”只聽$n" HIY "話音剛落，頓時起身而立，雙"
                     "手驀的回圈，暗含天罡北鬥星位，朝$N" HIY "攻去。霎時"
                     "$N" HIY "只覺招數一緊，接著雙臂癱軟，全身力道竟似被"
                     "$n" HIY "鎖住一般。\n\n" NOR, me, this_object()); 

        command("nod");
        command("say 這招看似簡單，實卻艱奧無比，你自行體會吧。");
        command("say 日後行走江湖，切記得饒人處且饒人，莫要積仇過深。");
        tell_object(me, HIC "你學會了「玄門金鎖」。\n" NOR);
        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 1500000);
        if (me->can_improve_skill("jinguan-yusuo"))
                me->improve_skill("jinguan-yusuo", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/jinguan-yusuo/suo", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}
string ask_array()
{
        object room, qizi, obj, ob = this_player(), me = this_object();
        mapping ob_fam, skl;
        string *skillname;
        int i;

        ob_fam=query("family", ob);
        skl = ob->query_skills();

        if (sizeof(skl) <= 1)
                return RANK_D->query_respect(ob) +
                "功力不夠，不夠資格闖天罡北鬥陣。";
        if( query("score", ob)<20000 )
                return RANK_D->query_respect(ob) +
                "閱歷不足，不夠資格闖天罡北鬥陣。";

        skillname  = keys(skl);
        for(i=0; i<sizeof(skl); i++) {
                if ((skl[skillname[i]] < 80) || (sizeof(skl) == 0))
                return RANK_D->query_respect(ob) +
                "功力不夠，不夠資格闖天罡北鬥陣。";
        }
        if( query("qixing", ob) )
                return RANK_D->query_respect(ob) +
                "已然闖過天罡北鬥陣，可不要拿老道開這等玩笑。";
/*
        if ( ob_fam["family_name"] != "全真教" || ob_fam["generation"] != 3)
                return RANK_D->query_respect(ob) + "，你沒資格闖天罡北鬥陣。";
*/
        if( query("assigned_qixing", me) )
                return RANK_D->query_respect(ob) + "，今日有人挑戰天罡北鬥陣，你過一段時間再來吧。";

        set("assigned_qixing",query("id",  ob), me);
        command("smile");
        say("\n馬鈺道長說道：好吧，我去召集眾師弟。稍候在大校場上等你。\n");
        message_vision("\n馬鈺道長往南離開。\n\n", ob);

/* 譚處端 */
        if(!( room = find_object("/d/quanzhen/rongwutang")) )
                room = load_object("/d/quanzhen/rongwutang");
                  me->move(room);
        if( !objectp(obj = present("tan chuduan", room) ))
        {
                me->move("/d/quanzhen/shiweishi");
                message_vision("\n馬鈺道長走了過來。\n\n", ob);
                return "真是對不起，全真七子有人不在，無法布天罡北鬥陣。\n";
        }
        message("vision","\n馬鈺道長走了過來，跟譚處端說了幾句。\n", room, obj);
        obj->move("/d/quanzhen/daxiaochang");
        message("vision", "譚處端點了點頭，快步跟了出去。\n", room, obj);

/* 劉處玄 */
        if(!( room = find_object("/d/quanzhen/jingxiushi")) )
                room = load_object("/d/quanzhen/jingxiushi");
                  me->move(room);
        if( !objectp(obj = present("liu chuxuan", room) ))
        {
                me->move("/d/quanzhen/shiweishi");
                message_vision("\n馬鈺道長走了過來。\n\n", ob);
                return "真是對不起，全真七子有人不在，無法布天罡北鬥陣。\n";
        }
        message("vision","\n馬鈺道長走了過來，跟劉處玄說了幾句。\n", room, obj);
        obj->move("/d/quanzhen/daxiaochang");
        message("vision", "劉處玄點了點頭，快步跟了出去。\n", room, obj);

/* 丘處機 */
        if(!( room = find_object("/d/quanzhen/laojundian")) )
                room = load_object("/d/quanzhen/laojundian");
                  me->move(room);
        if( !objectp(obj = present("qiu chuji", room) ))
        {
                me->move("/d/quanzhen/shiweishi");
                message_vision("\n馬鈺道長走了過來。\n\n", ob);
                return "真是對不起，全真七子有人不在，無法布天罡北鬥陣。\n";
        }
        message("vision","\n馬鈺道長走了過來，跟丘處機說了幾句。\n", room, obj);
        obj->move("/d/quanzhen/daxiaochang");
        message("vision", "丘處機點了點頭，快步跟了出去。\n", room, obj);

/* 王處一 */
        if(!( room = find_object("/d/quanzhen/wanwutang")) )
                room = load_object("/d/quanzhen/wanwutang");
                  me->move(room);
        if( !objectp(obj = present("wang chuyi", room) ))
        {
                me->move("/d/quanzhen/shiweishi");
                message_vision("\n馬鈺道長走了過來。\n\n", ob);
                return "真是對不起，全真七子有人不在，無法布天罡北鬥陣。\n";
        }
        message("vision","\n馬鈺道長走了過來，跟王處一說了幾句。\n", room, obj);
        obj->move("/d/quanzhen/daxiaochang");
        message("vision", "王處一點了點頭，快步跟了出去。\n", room, obj);

/* 郝大通 */
        if(!( room = find_object("/d/quanzhen/guangning")) )
                room = load_object("/d/quanzhen/guangning");
                  me->move(room);
        if( !objectp(obj = present("hao datong", room) ))
        {
                me->move("/d/quanzhen/shiweishi");
                message_vision("\n馬鈺道長走了過來。\n\n", ob);
                return "真是對不起，全真七子有人不在，無法布天罡北鬥陣。\n";
        }
        message("vision","\n馬鈺道長走了過來，跟郝大通說了幾句。\n", room, obj);
        obj->move("/d/quanzhen/daxiaochang");
        message("vision", "郝大通點了點頭，快步跟了出去。\n", room, obj);

/* 孫不二 */
        if(!( room = find_object("/d/quanzhen/qingjing")) )
                room = load_object("/d/quanzhen/qingjing");
                  me->move(room);
        if( !objectp(obj = present("sun buer", room) ))
        {
                me->move("/d/quanzhen/shiweishi");
                message_vision("\n馬鈺道長走了過來。\n\n", ob);
                return "真是對不起，全真七子有人不在，無法布天罡北鬥陣。\n";
        }
        message("vision","\n馬鈺道長走了過來，跟孫不二說了幾句。\n", room, obj);
        obj->move("/d/quanzhen/daxiaochang");
        message("vision", "孫不二點了點頭，快步跟了出去。\n", room, obj);
        set_temp("pre_qixing", 1, ob);

        me->move("/d/quanzhen/daxiaochang");
        call_out("waiting", 1, me,1);
        return "好！大家都出來了。\n";
}

int waiting(object me,int wait_time)
{
        object ob;

        if( wait_time == 300 )
        {
                say( "馬鈺說道：看來他不會來了，我們回去罷！\n\n");
                call_out("do_back", 0, me);
                addn("score", -5000, ob);
        }
        else if( !objectp(ob=present(query("assigned_qixing", me),environment(me))) )
        {
                wait_time++;
                call_out("waiting", 1, me,wait_time);
        }
        else call_out("preparing", 0, me, ob);

        return 1;
}

int preparing(object me, object ob)
{
        object *obs, room, obj1, obj2, obj3, obj4, obj5, obj6;
        string myname=query("name", me);
        int i;

        if(!( room = find_object("/d/quanzhen/daxiaochang")) )
        room = load_object("/d/quanzhen/daxiaochang");
        if(!objectp( obj1 = present("tan chuduan", environment(me))))
                return notify_fail("二師弟怎麼不在？\n");
        if(!objectp( obj2 = present("liu chuxuan", environment(me))))
                return notify_fail("三師弟怎麼不在？\n");
        if(!objectp( obj3 = present("qiu chuji", environment(me))))
                return notify_fail("四師弟怎麼不在？\n");
        if(!objectp( obj4 = present("wang chuyi", environment(me))))
                return notify_fail("五師弟怎麼不在？\n");
        if(!objectp( obj5 = present("hao datong", environment(me))))
                return notify_fail("六師弟怎麼不在？\n");
        if(!objectp( obj6 = present("sun buer", environment(me))))
                return notify_fail("小師妹怎麼不在？\n");

        me->dismiss_team();
        me->set_leader();
        me->add_team_member(obj1);
        me->add_team_member(obj2);
        me->add_team_member(obj3);
        me->add_team_member(obj4);
        me->add_team_member(obj5);
        me->add_team_member(obj6);

        say( "馬鈺說道：不相幹的人，如不欲觀摩天罡北鬥陣，請即刻離開。\n");


  obs=me->query_team();
        for(i=0;i<sizeof(obs);i++)
        {
                ob->fight_ob(obs[i]);
                obs[i]->fight_ob(ob);
                if(obs[i] != me)
                        message_vision(myname+"道："+query("name", obs[i])+"請做好準備！\n",me);
        }
//        command("say chat " + ob->query("title") + ob->query("name") +
//                "于今日" + NATURE_D->game_time() + "挑戰全真天罡北鬥陣！\n");
        message("channel:snow",HIC"【闖陣】馬鈺[Mayu]："+query("title", ob)+query("name", ob)+
                HIC+"于今日" + NATURE_D->game_time() + "挑戰全真天罡北鬥陣！\n"NOR,users());
        say(HIC"馬鈺吟道：“一住行窩幾十年。”\n");
        say("譚處端吟道：“蓬頭長日走如顛。”\n");
        say("劉處玄吟道：“海棠亭下重陽子。”\n");
        say("丘處機接口道：“蓮葉舟中太乙仙。”\n");
        say("王處一吟道：“無物可離虛殼外。”\n");
        say("郝大通吟道：“有人能悟未生前。”\n");
        say("孫不二吟道：“出門一笑無拘礙。”\n");
        say("馬鈺收句道：“雲在西湖月在天！”\n\n\n"NOR);

        message_vision(myname+ "清了清喉嚨，大聲說道：好，時辰已到，現在開始啟動「天罡北鬥陣」！\n",me);
        message_vision(myname+ "突然身形移動，發動眾全真弟子搶佔位置，左邊四人，右邊三人，正是擺的「天罡北鬥陣」陣法。\n",me);
        say("馬鈺位當天樞，譚處端位當天璇，劉處玄位當天璣，丘處機位當天權，四人組成鬥魁；\n");
        say("王處一位當玉衡，郝大通位當開陽，孫不二位當搖光，三人組成鬥柄。\n");
        remove_call_out("do_qixing");
        call_out("do_qixing", 2, me, ob);
        return 1;
}


int do_qixing(object me, object en)
{
        object *obs, weapon, enweapon;
        int i, j, power;
        string err;
        string *where = ({
                "天樞",
                "天璇",
                "天璣",
                "天權",
                "玉衡",
                "開陽",
                "搖光"
        });

        if(pointerp(obs=me->query_team()) )
        switch (random (4))
        {
                case 0:
message_vision("天罡北鬥陣氣勢宏大，前攻後擊，連環相接，讓人眼花撩亂，方寸頓失。\n",me);
                        break;
                case 1:
message_vision("天罡北鬥陣法滾滾推動，攻勢連綿不絕，瞬間將敵人圍在垓心。\n",me);
                        break;
                case 2:
message_vision("天罡北鬥陣越縮越小，無形劍氣象浪潮一般逼向中央，令人有窒息之感。\n",me);
                        break;
                case 3:
message_vision("只見天罡北鬥陣暗合五行八卦之理，陣中人步法精妙，攻守配合得天衣無縫，威力之大，讓人嘆為觀止。\n",me);
                        break;
        }
        for(i=0;i<sizeof(obs);i++)
        {
                weapon=query_temp("weapon", obs[i]);
                power = obs[i]->query_skill("force",1)/10;
          addn_temp("apply/attack", power, obs[i]);
          addn_temp("apply/damage", power, obs[i]);
                switch (random(2))
                {
                        case 0:
message_vision("\n"+where[i]+"位上的"+query("name", obs[i])+"氣沉丹田，暗運神功，猛然吐氣開聲，身形往前一縱,但見",me);
                                break;
                        case 1:
message_vision("\n"+where[i]+"位上的"+query("name", obs[i])+"挺身而出，步法精妙，長袖飄飄，攻勢如虹。只見",me);
                                break;
//                       default:
                }
          err=catch(COMBAT_D->do_attack(obs[i],en,weapon,0));
          if (err)
          {
                  message("channel:debug","天罡北鬥陣攻擊出錯 err="+err,users());
                  return 1;
          }
                addn_temp("apply/attack", -power, obs[i]);
                addn_temp("apply/damage", -power, obs[i]);
                if( query("qi", en)*2 <= query("max_qi", en) )
                {
                        en->remove_all_enemy();
                        remove_call_out("do_end");
                        call_out("do_end", 1, me, en, 0);
                        return 1;
                }
        }
        j = random(sizeof(me->query_team()));
        enweapon=query_temp("weapon", en);
        if (enweapon)
          COMBAT_D->do_attack(en,obs[j], enweapon);
        else
          COMBAT_D->do_attack(en,obs[j], enweapon);
        if( query("qi", obs[j])*2 <= query("max_qi", obs[j]) )
        {
                message_vision(HIR+query("name", obs[j])+"一跤趴在地上，摔出北鬥陣。\n"NOR,me);
                en->remove_all_enemy();
                remove_call_out("do_end");
                call_out("do_end", 1, me, en, 1);
                return 1;
        }
        else if( query("qi", obs[j])*3 <= query("max_qi", obs[j])*2 )
        {
                message_vision(query("name", obs[j])+"踉蹌了一步，差點摔出北鬥陣。\n",me);
        }
        else if( query("qi", obs[j])*5 <= query("max_qi", obs[j])*4 )
                message_vision(query("name", obs[j])+"被打得晃了幾晃，不過又站穩了步子。\n",me);

        remove_call_out("do_qixing");
        call_out("do_qixing", 1, me, en);
        return 1;
}
int do_end(object me, object en, int result)
{
        if( result == 1)
        {
                if( query_temp("pre_qixing", en) )
                {
                        set("qixing", 1, en);
                }
                delete_temp("pre_qixing", en);
                addn("combat_exp", 50000, en);
                addn("score", 30000, en);
                addn("potential", 10000, en);
                message_vision(HIR"\n天罡北鬥陣被"+query("name", en)+"打破了。\n\n"NOR,me);
                message("channel:snow",HIR"【通告】"HIY+query("name", en)+"打破天罡北鬥陣了！\n"NOR,users());
        }
        else
        {
                delete_temp("pre_qixing", en);
                message("channel:snow",HIR"【通告】"HIY+query("name", en)+"沒能闖出天罡北鬥陣！\n"NOR,users());
    message_vision(HIR"\n$N笑了笑：天罡北鬥陣不愧為全真鎮教之寶。\n"NOR,me);
                addn("score", -3000, en);
        }
        remove_call_out("do_back");
        call_out("do_back", 1, me);
        return 1;
}
int do_back(object me)
{
        object *obs, weapon;
        int i;

        if(pointerp(obs=me->query_team()) )
        {
                for(i=0;i<sizeof(obs);i++)
                {
                        if( objectp(weapon=query_temp("weapon", obs[i]) )
                                 && query("skill_type", weapon) == "sword" )
message_vision("$N身子向後一縱，使一招『收劍式』，將劍挽了一個劍花，往懷中一抱，退出「天罡北鬥陣」。\n", obs[i]);
                        else
message_vision("$N身子向後一縱，使一招『收山式』，右拳劃了一圈，左掌往懷中一抱，退出「天罡北鬥陣」。\n", obs[i]);

message_vision("$N作了個楫道：貧道先告退了！說完就快步離開了。\n", obs[i]);
                        if( query("name", obs[i]) == "馬鈺" )
                                obs[i]->move("/d/quanzhen/shiweishi");
                        if( query("name", obs[i]) == "譚處端" )
                                obs[i]->move("/d/quanzhen/rongwutang");
                        if( query("name", obs[i]) == "劉處玄" )
                                obs[i]->move("/d/quanzhen/jingxiushi");
                        if( query("name", obs[i]) == "丘處機" )
                                obs[i]->move("/d/quanzhen/laojundian");
                        if( query("name", obs[i]) == "王處一" )
                                obs[i]->move("/d/quanzhen/wanwutang");
                        if( query("name", obs[i]) == "郝大通" )
                                obs[i]->move("/d/quanzhen/guangning");
                        if( query("name", obs[i]) == "孫不二" )
                                obs[i]->move("/d/quanzhen/qingjing");
                }
        }///d/quanzhen/shiweishi
        me->dismiss_team();
}
