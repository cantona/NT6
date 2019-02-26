//一個可以指導崆峒弟子武功的NPC，可以看作是神仙的化身。
//行蹤無定，而且很少出現。
// Qyz

inherit F_UNIQUE;
inherit NPC;



void create()
{
        set_name("無名老者", ({ "lao zhe","zhe", "old" }) );
        set("title","");
        set("gender", "男性" );
        set("age", 110);
        set("cor", 40);
        set("cps", 40);
        set("per", 40);
        set("int", 40);
        set("chat_chance", 10);
        set("chat_msg", ({
                    (: random_move :)
                    }) );

        set("attitude", "friendly");
        set("can_teach",1); 
        set("max_gin", 1000);
        set("max_kee", 1000);
        set("max_sen", 1000);
        set("eff_gin", 1000);
        set("eff_kee", 1000);
        set("eff_sen", 1000);
        set("gin", 1000);
        set("kee", 1000);
        set("sen", 1000);
        set_wugong("hujia-dao",150,150,1);
        set_xiuwei_by_type("blade",5300);
        set("max_force", 10000);
        set("force", 10000);
        set("force_factor",1000);

        set("long",     "這是一位仙風道骨的老道人，長得慈眉善目，極是可親。\n");
        set("chat_chance_combat", 20);      
        set("chat_msg_combat", ({
        (: SKILL_D("hujia-dao")->perform_action(this_object(), "weizhen-bafang") :),
           }) );  

        set("combat_exp", 99999999);
        set_wugong("kongdong-xinfa",1000,1000,1);

        set("positive_score",10000);
        setup();

        carry_object(__DIR__"obj/cloth1")->wear();
        carry_object(__DIR__"obj/bidao")->wield();
}

int valid_teach( object ppl, string skill )
{
	
   
    if (ppl->query("family/family_name") != "崆峒派")      //如果沒有學功夫的標記
    {
        command( "say “呵呵，好久沒人和老夫説話啦！”" );
        return 0;
    }
   
    if (ppl->query("marks/kongdong/zhou") != 1) 
    {
        command( "say “你見過周真人麼？”" );
        return 0;
    }
    if ( !query_jibie( skill ) )
        return 0;
     
     
    if( ppl->query("class_score/崆峒派") < 500 )
        {
        command( "say “我在崆峒山住幾十年了，怎麼不曾見過你？”" );
        return 0;
           
        }
    if( skill=="kongdong-xinfa")
    return 1;   
    if( skill=="hujia-dao"&&random( (int)ppl->query("kar") ) < 20 &&ppl->query_jibie("hujia-dao")<1) 
     {
        command( "say “你這人看起來心術不正，我不能教你！”" );
        ppl->add("gin",-20);
        return 0;
    }
       if(skill=="hujia-dao"&& ppl->query_xiuwei_by_type("blade")<1500)
     {
        command( "say “可惜你修為不夠，領悟不了我家傳的胡家刀法！”" );
        return 0;
    }  
    command( "say “終於找到一個可以發揚我胡家刀法的後輩了。”" );
    command( "haaa" );
    return 1; 

}


int zhongcheng( object ppl, string skill )  //不檢查忠誠度
{
    return 1;
}

