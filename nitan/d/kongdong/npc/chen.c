inherit NPC;


void create()
{
    set_name("陳漢京", ({ "chen hanjing","chen","jing" }) );
    set("title","崆峒派大師兄");
    set("gender", "男性" );
    set("class","taoist");
    set("positive_score",8000);
    set("age",25);
	set_hp("sen", 600 );
	set_hp("kee", 600 );
	create_family("崆峒派", 2, "弟子");
    set_wugong("jiben-qinggong",100,100);
    set_wugong("nieyun-bufa",60,65,1);
    set_wugong("luofeng",50,50,1);
	set_xiuwei_by_type("dodge",500);
    set_wugong("unarmed",100,100);
    set_wugong("dahong-quan",100,100);
    set_wugong("shizi-zhan",90,86,1);
    set_wugong("wulong-quan",60,60,1);
	set_xiuwei("unarmed",800);
    set("social_exp",2000);
    set("combat_exp",10000);
    set("force",200);
    set("max_force",200);
    set("force_factor",10);
    setup();
    carry_object(__DIR__"obj/cloth2")->wear();
}

void init()
{
        object ob;
        ob = this_player();
       ::init();
        if(interactive(ob=this_player()) && !is_fighting()){
            remove_call_out("say_hi");
            call_out("say_hi",1,ob);
            }
}

void say_hi(object ob)
{
        if(!ob||!present(ob,environment(this_object())))return;
        if(ob->query("family/family_name")!="崆峒派")
        {
                message_vision("陳漢京向$N一拱手：這位"+RANK_D->query_respect(ob)+"，"
                "家師就在裡面，快請進吧。\n",ob);
			return;
        }
        message_vision("陳漢京笑著拍拍$N的肩膀：怎麼樣，功夫有長進嗎？好好練吧。\n",ob);
		return;
}

                
int accept_object( object ppl, object obj )
{
    object gold;

    if ( obj->query( "id" ) != "teng xia" ) 
        return 0;
    if ( query( "box" ) )               
    {
        message_vision( "陳漢京沖著$N大喝道：“周老太爺怎麼會讓你送兩個禮盒？！"
            + RANK_D->query_rude( ppl ) + "竟敢欺騙老夫！”\n", ppl );
        kill_ob( ppl );
        ppl->fight_ob( this_object() );
        remove_call_out( "Dest" );
        call_out( "Dest", 1, obj );
        return 1;
    }

    if ( ppl->query( "mud_age" ) < 3600 * 24 * 2        //如果玩家年齡在十六以下
        && ppl->query( "combat_exp" ) < 50000           //或經驗不足一萬，
        && ppl->query( "max_force" ) < 1000 )            //或內力不足三百，則否認
    {
        message_vision ( "陳漢京上下打量了$N許久，突然嘿嘿冷笑道：“哼！就憑你\n"
            + "這麼點道行，也能走鏢？你是怎麼來的，還不老實交代！！”\n",
            ppl );
        kill_ob( ppl );
        ppl->fight_ob( this_object() );
        remove_call_out( "Dest" );
        call_out( "Dest", 1, obj );
        return 1;
    }
        
    message_vision( "陳漢京拍拍$N肩頭，笑了笑道：“很好，不愧是周老太爺的鏢師。\n"
        + "這些是你走鏢的報酬，拿好哦。”\n", ppl );
    call_out( "Dest", 1, obj );
    set( "box", 1 );                    
    gold = new( MONEY_DIR + "gold" );       
    gold->set_amount( 10 );
    gold->move( ppl );
    command("chat 恭喜，"+ppl->query("name")+"("+ppl->query("id")+")"+"走鏢成功，獲得十兩金子的報酬。");
    return 1;
}

void Dest( object obj )
{
       destruct( obj );
}

