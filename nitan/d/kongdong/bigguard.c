//  秦天彪：龍門鏢局總鏢頭  /d/city/lanzhou/npc/bigguard.c
//  等級：
//  【丙等】大門派的二級師傅、中等門派的一級師傅，江湖上知名的豪客
//  ★★★★☆
//  〖一級〗四級修為（１５０１－１９００）五級武功（  ８０－１２０）
//          經驗（  １００萬－  ２００萬）聲望（  １００００－  ２００００）
//          內力（  ２２００－  ３０００）體能、生命（  ７５０－    ９５０）
//  By Lin
//  Changed Lala, 1998-03-25

#include <ansi.h>
string ask_skills();
inherit NPC;
int CanTeach();



void create()
{
    set_name( "秦天彪", 
        ({ "qin tianbiao", "qin", "qintianbiao", "tianbiao", "master" }) );
    set( "title", HIW"龍門鏢局總鏢頭"NOR );
    set( "nickname", CYN"關西第一刀"NOR );
    set( "gender", "男性" );                //性別：男
    set( "age", 72 );                       //年齡：52
    set( "str", 30 );                       //臂力：30
    set( "cor", 30 );                       //膽識：30
    set( "dex", 30 );                       //身法：30
    set( "per", 22 );                       //容貌：22
    set( "int", 35 );
    set( "rank_info/respect", "老英雄" );   //敬稱：老英雄
    set( "positive_score", 18000 );         //正聲望：18000
    set( "negative_score",  2000 );         //負聲望：2000
    set( "long", @LONG
    秦天彪少年時就生得異常魁梧，早年曾在少林寺當了很多年的俗家弟子，後
來又得高人相授，刀法和鐵砂掌功夫都是相當了得。現在是龍門鏢局的大當家。
LONG
    );

    set_wugong( "blade",        120,    120,    0 );    //橫刀六式：    一級
    set_wugong( "ditang-dao",   120,    120,    0 );    //地趟刀：      二級
    set_wugong( "wuhu-dao",     100,    100,    0 );    //五虎斷門刀：  三級
    set_wugong( "kuaidao",      105,    105,    1 );    //快刀十三式：  四級
    set_wugong( "fenglei-dao",  150,    150,    0 );    //風雷刀：      五級

    set_wugong( "unarmed",      120,    120,    0 );    //基本拳法：    一級
    set_wugong( "luohan-quan",  100,    100,    0 );    //羅漢拳：      一級
    set_wugong( "taizu-quan",   120,    120,    0 );    //太祖長拳：    二級
    set_wugong( "weituo-zhang",  80,     80,    0 );    //韋陀掌：      二級
    set_wugong( "tiesha-zhang", 150,    150,    1 );    //鐵砂掌：      三級

    set_wugong( "qinggong",     120,    120,    0 );    //基本輕功：    一級
    set_wugong( "feiyan-zoubi", 120,    120,    0 );    //飛檐走壁之術：二級
    set_wugong( "feiyan-gong",  100,    100,    1 );    //飛燕功：      三級      
    set_wugong( "caiyun-gong",   90,     90,    1 );    //彩雲功：      四級
    set_wugong( "xueying-jian", 100,    100,    1 );

    set_wugong( "banruo-xinfa",120,    120,    1 );    //少林心法

    set_xiuwei_by_type( "blade",    3000 ); //刀法修為：    五級
    set_xiuwei_by_type( "unarmed",  1800 ); //拳腳修為：    三級
    set_xiuwei_by_type( "dodge",    1800 ); //輕功修為：    三級
    set_xiuwei_by_type( "zonggang",  1000 ); //總綱修為：    一級

    set( "max_force",   2700 );             //內力：    2700
    set( "force",       2700 );
    set( "force_factor", 135 );             //加力：    135 (5%)

    set_hp( "kee",      875 );              //生命、體能：  875
    set_hp( "sen",      875 );

    set( "combat_exp",  1000000 );          //戰鬥經驗：100萬
    set( "social_exp",   170000 );          //江湖閲歷：17萬
    set( "talk_msg", ({
        "“這位英雄來我鏢局有何貴幹？”",
    }) );
    set("inquiry",([
        "武功"   :    (: ask_skills :),
        "skills" :    (: ask_skills :),
    ]) );
    setup();

    carry_object( CLOTH_DIR + "cloth5" )->wear();       //紫綢長衫
    add_money( "silver", 5 );               //有銀子五兩
       
}

void init()
{
    object ppl;

    ::init();

    if ( !userp( ppl = this_player() ) 
        || !can_act() ) 
        return;

    remove_call_out( "Greeting" );
    call_out( "Greeting", 1, ppl );
}

void Greeting( object ppl )
{       
     
    if( !ppl 
        || environment( ppl ) != environment() ) 
        return;
    if( ppl->query_temp( "marks_lin/kill_wang" ) )       //如果此人殺過王太醫
    {
        message_vision( "秦天彪向$N憤怒地説道：“想不到有人竟敢欺負到我的頭上"
            "？！”\n", ppl );
        message_vision( "秦天彪對$N大喝道：“今天為王老丈報仇！”\n", ppl );
        kill_ob( ppl );
        ppl->fight_ob( this_object() );
        return;
     }
    command( "say “這位英雄來我鏢局有何貴幹？”" );
    command( "look "+ ppl->query( "id" ) );
}

int refuse_killing( object ppl )            //被殺時的反應
{
    object npc = this_object();

    if( !living( npc ) 
        || query_temp( "weapon" ) )
        return 0;
    message_vision( "$N看了$n一眼，冷笑道：“居然有你這麼不知天高地厚的狂妄之"
        "徒，哼哼，待老夫今天好好收拾你！！\n", npc, ppl );
    new( BLADE_DIR "blade2" )->move( npc ); //拿一把單刀
    command( "wield blade" );               
    command( "enable fenglei-dao" );         //使用風雷刀
    command( "disable kuaidao" );            //不使用快刀
    return 0;
}

int killed_enemy( object ppl )              //殺死敵人的反應
{
    if ( ppl->query( "marks_lin/kill_wang" ) )//玩家刪除殺死王太醫的記錄
        ppl->delete( "marks_lin/kill_wang" );
    ppl->delete_temp( "marks_lin/" );
    return 1;
}

int valid_teach( object ppl, string skill )
{
	command( "say “以後要多替為師押鏢，閒着多練練般若心法。”" );
    if ( ppl->query( "marks/lin/蘭州祕密B/送官" )!=1)      //如果沒有學功夫的標記
    {
        command( "say “武林中人，要多為朝廷辦事？”" );
        return 0;
    }

    if ( !query_jibie( skill ) )
        return 0;

    if ( skill == "blade"              //高級的武功不給學
        || skill == "unarmed" 
        || skill == "qinggong" )
    {
        command( "say “這些功夫嘛，太基本了，沒工夫教你啊！”" );
        return 0;
    }
    
    return 1; 
}

int zhongcheng( object ppl, string skill )  //不檢查忠誠度
{
    return 1;
}

string ask_skills()
{ 
    command( "sigh" );
   return "為師離開少林後，跟過很多名師，象地趟刀法、快刀十三式、\n
           五虎斷門刀、風雷刀以及彩雲功等都曾學過。\n
           可惜象相思刀法、胡家刀法、殺人刀法都不曾學會。";
   
}