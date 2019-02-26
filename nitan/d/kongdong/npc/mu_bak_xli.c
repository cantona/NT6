// mu.c

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

string leave_kongdong( object );



void create()
{
        seteuid(getuid());
        set_name("木靈子", ({ "mu lingzi", "mu","lingzi" }) );
        set("class","taoist");
    set("vendetta_mark","kongdong");
        set("gender", "男性" );
        set("age", 50);
        set("str", 30);
        set("cor", 30);
        set("cps", 30);
        set("int", 25);
        set("ker", 24);
        set("kar", 30);
        set("max_force", 1500);
        set("force", 1500);
        set("force_factor", 3);

        set("rank_info/respect", "老神仙");

        set("long",
    "木靈子紅光滿面，一看就是修道有成之人，頗有些仙風道骨之相。\n");

        create_family("崆峒派", 1,"掌門人");
        set("positive_score",10000);
        set("combat_exp", 1000000);
        set("social_exp", 200000);

	set_wugong("kongdong-xinfa",130);
    set_wugong("unarmed",100,100,0);
	set_wugong("shizi-zhan",100);
	set_wugong("dahong-quan",100);
	set_wugong("wulong-quan",100);
    set_wugong("qishang-quan",120,120,1);
	set_xiuwei_by_type("unarmed",2300);
	set_wugong("sword",100);
    set_wugong("fengyun-jian",100);
	set_wugong("kongling-jian",100);
	set_xiuwei_by_type("sword",900);
	set_wugong("jiben-qinggong",100);
	set_wugong("nieyun-bufa", 100,100,1);
	set_wugong("luofeng",100,100,1);
	set_xiuwei("dodge",900);
	
	set( "inquiry",([ /*sizeof() ==1 */
	    "出師" : (: leave_kongdong :),
	]) );

    set("env/attack", 75);
    set("force_factor", 20);

    setup();
    carry_object(__DIR__"obj/cloth1")->wear();
}

void init()
{
	add_action("give_quest", "quest" );
}

void attempt_apprentice(object ob)
{
         //Hydra 19980507 for 出師
        if( ob->query("hydra/出師/崆峒派") )
        {
            message_vision(CYN"$N對$n説道：“你既已離開師門，怎麼又回來"
"了呢？”\n"NOR,this_object(),ob);
            return 0;
        }
        
        if( (int)ob->query("pks") > 10 ) 
        {
                command("hmm");
                command("say 你手上血腥濃重，怎能修身得道？\n");
                return;
        }
        command("en");
        say("木靈子笑道：“這位"+RANK_D->query_respect(ob)+"真是個可造之才呀！\n"
            "將來必能發揚我崆峒派門庭！\n");
        command("recruit "+ob->query("id") );
        ob->delete("master");
        ob->set("class","taoist");
        ob->set_family("title","開山大弟子");
}


//Hydra:add for 出師 19980507
string leave_kongdong( object me )
{
    object this;
    me = this_player();
    this = this_object();

    if( me->query("hydra/出師/崆峒派"))
    {
        return "你不是已經出師了嗎？";
    }
    if( me->query("family/family_name") != "崆峒派" )
    {
        command( "? "+me->query("id") );
        return "你好像不是我崆峒派門人啊？";
    }
    if( me->query_temp("出師比劃"))
    {
        return "我不是讓你先跟我比劃一下嗎？";
    }
    
    if( me->query( "class_score/崆峒派" ) < 1000 )
    {
        message_vision(CYN"$N對$n道：“你在我門下多年，為師門所做"
"未免太少了一些。”\n"NOR,this,me );
        me -> add( "class_score/崆峒派",-10);
        return "你還是先為光大師門多幹點事吧！\n";
    }

    if( me->query_jibie("qishang-quan") > 80 )
    {
        if( me->query("age") < 30 )
        {
            message_vision(CYN"$N對$n説道：“你年紀輕輕就出去，人家會以為我崆峒派"
"無人的。”\n"NOR,this,me);
            me -> add( "class_score/崆峒派",-10);            
            return "過兩年再説吧。\n";
        }
        else
        {
            me->set_temp("出師比劃",1);
            return "你先空手跟為師比劃一下，讓我看看你拳腳功夫如何了。";
        }
    }
    else
    {
        return "以你現在的實力，難於在江湖上獨擋一面，還是跟為師再學學吧！";
    }
    return "";
}        

int accept_fight( object ppl )
{
    object this;
    this = this_object();
    
    if( ppl-> query_temp( "出師比劃" ))
    {
        if(this->is_fighting() )
        {
            return notify_fail( "現在木靈子不能跟你比劃。\n");
        }    
        if(ppl->query_temp("weapon"))
            return notify_fail("木靈子道：“我不是讓你空手跟我比劃嗎？”\n");
        this->set( "eff_kee",this->query("max_kee"));
        this->set( "kee",this->query("max_kee"));
        this->set( "eff_sen",this->query("max_sen"));
        this->set( "sen",this->query("max_sen"));
        this->set( "force",this->query("max_force"));
        this->set( "force_factor",100);
        this->set( "env/attack",90 );
        message_vision(CYN"$N道，“好，進招吧。”\n",this);
        return 1;
     }
     return ::accept_fight( ppl );
}

int lose_bihua( object ppl)
{
    object this;
    this=this_object();
    if( ppl->query_temp("出師比劃"))
    {
        command( "chat* haha" );
        command( "chat 我崆峒終於也出了一個人才。");
        command( "say 真是青出於藍勝於藍啊，你的功夫已經比為師的高了。");
        command( "say 如此，你就另謀高就去吧。");  
        ppl -> delete_temp("出師比劃");    
        ppl -> set("title","普通百姓");
        ppl -> delete("family");
        ppl -> delete("class");
        ppl -> delete("class");
        ppl -> set("hydra/出師/崆峒派",1);
             LOG_D->do_log(ppl,sprintf("你獲得了木靈子的允許，從崆峒出師。\n"));
        log_file("chushi",sprintf("%s(%s)於%s順利從崆峒出師。\n",ppl->query("name"),
            getuid(ppl),ctime(time()) ) );
        message_vision("$N恭恭敬敬地跪了下來，向$n磕了四個響頭。\n",ppl,this);
    }
    return 1;
}
        
int win_bihua( object ppl )
{
    object this;
    this=this_object();
    if( ppl->query_temp("出師比劃"))
    {
        command("pat "+ppl->query("id"));
        command("say 看來為師的功夫還略高你一些，還夠你學一陣的。");
        ppl->delete_temp("出師比劃");
        ppl->add("class_score/崆峒派",-10);
    }
    return 1;
}
            
void heart_beat()
{
    object this,ob;
    string *bihua;
    this = this_object();
    bihua = this->query_bihua();
    
    foreach( string name in bihua )
    {
       if( objectp( ob=find_player(name)) && 
           ob->query_temp("出師比劃") && 
           ob -> query_temp("weapon") )
       {
           ob -> add( "class_score/崆峒派",-100);
           command("heng "+ob->query("id"));
           command("say 我不是讓你空手跟我打的嗎？居然敢欺騙師傅！！");
           command("stop");
        }
    }
    return ::heart_beat();
}
    
                
