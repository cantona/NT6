// lilishi.c 李力世

#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;
inherit F_MASTER;
int ask_weiwang();
int ask_zhu();
int ask_me();

mixed names = ({
({ "史青山", "林震南", "宋青書", "採花賊","獨腳大盜","史鬆", }),
({ "獅吼子","飛天子","黯然子","溫南揚","侯通海","沙通天", }),
({ "溫方悟","溫方施","史叔剛","武修文","錢青健","溫方達","溫方義","溫方山","齊雲敖","天狼子","包不同","風波惡","鄧百川", }),
({ "殷天正","韋一笑","楊逍","范遙","慕容復","黛綺絲","瀟湘子","李莫愁", }),
({ "張昭重","成昆","丁春秋","歸辛樹","歸二娘","胡逸之","西華子", }),
});

void create()
{
        set_name("李力世", ({ "li lishi", "li" }));
        set("gender", "男性");
        set("age", 45);
        set("str", 25);
        set("dex", 20);
        set("long", "這是一個高高瘦瘦的老者，滿臉凄苦的神色，頷下一\n"
                "把稀稀拉拉的胡子，飽經滄桑的樣子。身上的\n"
                "衣服又臟又破，臉上滿是皺紋，看上去飽經風霜。\n");
        set("combat_exp", 35000);
        set("score", 5000);
        set("shen_type", 1);
        set("attitude", "peaceful");

        set_skill("force", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);
        set_skill("claw", 50);
        set_skill("hand", 50);
        set_skill("blade", 50);
        set_skill("literate", 50);
        set_skill("wuhu-duanmendao", 50);
        set_skill("yunlong-shengong", 60);
        set_skill("yunlong-shenfa", 60);
        set_skill("yunlong-shou", 50);
        set_skill("yunlong-zhua", 50);
        map_skill("hand", "yunlong-shou");
        map_skill("claw", "yunlong-zhua");
        map_skill("blade", "wuhu-duanmendao");
        map_skill("force", "yunlong-shengong");
        map_skill("dodge", "yunlong-shenfa");
        map_skill("parry", "wuhu-duanmendao");
        prepare_skill("hand","yunlong-shou");
        prepare_skill("claw","yunlong-zhua");

        set("qi", 800);
        set("max_qi", 800);
        set("jing", 1000);
        set("max_jing", 1000);
        set("neili", 800); 
        set("max_neili", 800);
        set("jiali", 10);
        set("chat_chance", 2);
        set("chat_msg", ({
                "李力世說：呆會兒我還得把豬送到宮裡去。\n",
                "李力世突然吆喝道: 花雕芙苓豬啊，只賣黃金一兩，誰買誰買啊？\n",
                "李力世突然吆喝道: 燕窩人參豬啊，只賣黃金一兩，誰買誰買啊？\n",
                "李力世搔了搔頭，說道：這麼好的豬肉怎麼沒人要啊。\n",
                "李力世突然說：初進洪門結義兄，對天明誓表真心。\n",
        }));
        set("inquiry", ([
                "陳近南" : "想見總舵主可不容易啊。\n",
                "天地會" : "只要是英雄好漢，都可以入我天地會(join tiandihui)。\n",
                "入會" : "只要入了我天地會，可以向會中各位好手學武藝。\n",
                "反清復明" : "去棺材店和回春堂仔細瞧瞧吧！\n",
                "暗號" : "敲三下！\n",
                "切口" : "敲三下！\n",
//                "反清復明" : (: ask_me :),
                "進宮" : (: ask_zhu :),
                "花雕芙苓豬" : (: ask_zhu :),
                "燕窩人參豬" : (: ask_zhu :),
                "威望" : (: ask_weiwang :),
                "江湖威望" : (: ask_weiwang :),
        ]) );
        set("party/party_name", "天地會");
        set("party/rank", HIG"青木堂"NOR"會眾");
        create_family("雲龍門", 2, "弟子");
        setup();
        carry_object(CLOTH_DIR"male-cloth")->wear();
        carry_object(CLOTH_DIR"male-shoe")->wear();
        carry_object(__DIR__"obj/tudao")->wield();
        add_money("silver", 20);
}

int ask_weiwang()
{
        command("tell"+query("id", this_player())+"你現在的江湖威望是"+(query("weiwang", this_player())));
        say( "\n李力世說道：如果你威望值很高，有些人見了你不但不會殺你，還會教你武功，送你寶貝。\n而且你還可以加入幫會，率領會眾去攻打目標，就連去錢莊取錢也會有利息 。。。。。\n");
        say("李力世說：殺某些壞人或救某些好人可以提高江湖威望。\n");
        return 1;
}

int ask_zhu()
{
        if( query_temp("money_paid", this_player()) )
        {
                delete_temp("money_paid", this_player());
                set("huanggong\\canenter", 1, this_player());
                say("李力世說：您老現在可以走啦！\n");
                return 1;
        }
        say("李力世說：幹什麼也得先交錢啊。\n");
        return 1;
} 

void init()
{
        ::init();
        add_action("do_join","join");
}

int recognize_apprentice(object ob)
{
        if( query("weiwang", ob)<50 )
        {
                message_vision("$N搖了搖頭。\n",this_object());
                command("tell"+query("id", ob)+"不是天地會弟子我不教。\n");
                return 0;
        }
        return 1;
}
/*
int do_skills(string arg)
{
        object ob ;
        ob = this_player () ;
        if( !arg || arg!="li" )
                return 0;
        if(wizardp(ob)) return 0;
        if( query("party/party_name", ob) != "天地會" )
        {
                message_vision("$N搖了搖頭。\n",this_object());
                command("tell"+query("id", ob)+"不是天地會弟子不能察看。\n");
                return 1;
        }
        command("tell"+query("id", ob)+"我所有的武功如下：\n"+
"  基本刀法 (blade)                         - 一代宗師  90/    \n"+
"  基本輕功 (dodge)                         - 神乎其技  60/    \n"+
"  基本內功 (force)                         - 神乎其技  60/    \n"+
"  基本招架 (parry)                         - 出類拔萃  50/    \n"+
"  基本拳腳 (unarmed)                       - 出類拔萃  50/    \n"+
"□雲龍身法 (yunlong-shenfa)                - 神乎其技  60/    \n"+ 
"□五虎斷門刀 (wuhu-duanmendao)             - 一代宗師  90/    \n");
        return 1;
}
*/
int ask_me()
{ 
        object ob, me;
        int exp,position;
        string target;
        me = this_player();
        ob = this_object();
        exp=query("combat_exp", me);
        if(me->query_condition("gb_mission") ||
                me->query_condition("guanfu_task") ||
                me->query_condition("xx_task") ||
                me->query_condition("xx_task") ||
                me->query_condition("xx_task2") ||
                me->query_condition("dali_songxin"))
        {
                command("say 你現在和江湖其他幫會糾葛不清，我不能交給你任務。");
                return 1;
        }
        if(me->query_condition("thd_task2") || me->query_condition("thd_task3"))
        {
                command("say 你正在執行天地會青木堂的任務！");
                return 1;
        }
/*if( !query_temp("tdh_li", me) && 
                (me->query_condition("tdh_task_wait")<0))
        {
                command( "say 沒有香主的命令，我不能交給你任務，天地會一向紀律嚴明。");
                return 1;
        }
        if( !query_temp("tdh_li", me) )
        {
                command( "say 沒有香主的命令，我不能交給你任務，天地會一向紀律嚴明。");
                return 1;
        }
*/
         if(exp>=850000) position=5;
        else if(exp>=600000) position=4;
        else if(exp>=300000) position=3;
        else if(exp>=150000) position=2;
        else position=1;
        target = names[position-1][random(sizeof(names[position-1]))];
        set_temp("tdh_target", target, me);
        me->apply_condition("tdh_task1",30); 
        me->clear_condition("tdh_task_wait");
        command( "say "+target+"最近投靠清廷，殺我會中兄弟，你去把此賊的人頭提來，以祭亡靈！");
        if(!present("qingmu ling", me))
        {
                new(__DIR__"qml")->move(me);
                message_vision("李力世把一枚青木令交給了$N。\n", me);
                return 1;
        }
        return 1;
}
int accept_object(object who, object ob,object me)
{
/*
        if( !query("tdh_pass", who))return 0;
        if( query("id", ob) != "head")return 0;
        if( !query_temp("tdh_target", who))return 0;
*/
        if( query("money_id", ob) && ob->value() >= 10000 )
        {
                message_vision("\n李力世對$N一揖作禮，說道：這位客官，要什麼盡管說。\n",this_player());
                set_temp("money_paid", 1, who);
                return 1;
        }
        if( query_temp("tdh_target", who) && 
                (who->query_condition("tdh_task1")<0))
        {
                command("say 你來晚了，已經有人為會中兄弟報仇了。");
                return 0;
        }
        if( query("victim_name", ob) != query_temp("tdh_target", who)+"的首級" )
        {
                command( "say 天地會恩怨分明，怎能亂殺無辜呢？下次你要在違反會規我絕不客氣！");
                return 0;
        }
        if( query("victim_user", ob) )
        {
                command("say " + RANK_D->query_rude(who) + "，敢作弊！");
                return 0;
        }
        if( query("kill_by", ob) != who )
        {
                command( "say 天地會全是頂天立地的豪傑，你怎麼冒領其他人的功勞呢？");
                return 0;
        }
        command("say 你能手刃惡賊，使會中兄弟大仇得報，好樣的！");
        addn("tdh_job", 2, who);
        who->clear_condition("tdh_task1");
        delete_temp("tdh_target", who);
        who->deltet_temp("tdh_li");
        call_out("destroying", 1, ob);
        call_out("ok", 1, who);
        return 1;
} 

void destroying(object obj)
{
        destruct(obj);
        return;
}
#include "tiandihui.h";
