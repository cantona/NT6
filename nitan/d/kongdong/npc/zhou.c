// zhou.c

inherit NPC;
#include <ansi.h>
string *pashan_msg = ({
        HIR"周真人深深吸了幾口氣，沿着顫顫悠悠的棧道走了過去......\n"NOR,
        HIR"只見周真人慢慢地一步一步地往前挪......\n"NOR,
        HIR"只見周真人慢慢地一步一步地往前挪......\n"NOR,
        HIR"只見周真人慢慢地一步一步地往前挪......\n"NOR,
        HIR"只見周真人慢慢地一步一步地往前挪......\n"NOR,        
        HIG"眼看周真人已經到了棧道中央了......\n"NOR,
        HIR"只見周真人慢慢地一步一步地往前挪......\n"NOR,
        HIR"只見周真人慢慢地一步一步地往前挪......\n"NOR,
        HIR"只見周真人慢慢地一步一步地往前挪......\n"NOR,
        HIR"只見周真人慢慢地一步一步地往前挪......\n"NOR,         
        });



void create()
{
        set_name("周真人", ({ "zhou zhenren","zhou","zhenren" }) );
        set("title","苦修者");
        set("gender", "男性" );
        set("age",40);
        set("social_exp",2000);
        set("combat_exp",10000000);
        set_force(3000,3000,300);
        set("attitude", "friendly");
	set_wugong("qishang-quan",150,150,1);
	set_wugong("luofeng",30,30,1);
	set_xiuwei("dodge",3300);
	set_xiuwei("unarmed",5300);
        setup();
        carry_object(__DIR__"obj/cloth2")->wear();
}

void init()
{
    object ppl;

    ::init();
    if ( userp( ppl = this_player() ) 
        && can_act()
        &&!this_object()->query_temp("have") ) 
    {
        remove_call_out( "Greeting" );
        call_out( "Greeting", 5, ppl );
       	this_object()->set_temp("have",1);
    }
    if(environment(this_object())->query("short")==WHT"玄鶴洞"NOR)
        remove_call_out( "say" );
        call_out( "say", 5, ppl );    
}

void Greeting( object ppl )
{
    command("nod "+ppl->query("id"));
    command( "climb 棧道" );     
}

void say(object ppl)
{
	
	}
/*
int refuse_killing(object me)
{
        command("nokill "+me->query("id"));
        me->unconcious();
    return 1;
}
*/

