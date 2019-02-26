// shibi.c writen by cry 10.1.98

#include <ansi.h>
private int gain_points( object me );
private int gain_xiuwei( object me );
inherit ITEM;
int look_item(string arg);


void create()
{
	set_name(HIC"石壁"NOR, ({ "shibi" }) );
        set_weight(200000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "這是一塊石壁，表面光亮如鏡，刻着寫揮舞着刀法的小人. \n");
		set("unit", "塊");
		set("no_get",1);
		set("value",1000);
		set("material", "stone");
	}
	setup();
}

void init()
{
    add_action("can_xiu", "canxiu");
}

int can_xiu( string arg )
{
    object me;
    me = this_player();
    if ( me->query("marks/kongdong/dao")!=2)
      return notify_fail(HIB"你是怎麼進來的？去死吧！呵呵，嚇唬你的！下次按照規矩進來！\n"NOR);
    if( !me->can_act() || me->is_fighting() )
        return notify_fail(HIB"你現在哪兒有心思去研究這快石壁上的東西。\n"NOR); 
    tell_object( me, WHT"你對着石壁，潛心的研究起來。\n"NOR);
    me->disable_command("verb", HIB"一心豈能二用！? ！\n"NOR);
    call_out("start_canxiu", 10, me );
    return 1;
}

void start_canxiu( object me )
{
    int time;
    if( !me ) return;
    if( me->query_xiuwei_by_type("blade") < 5300 )
    {
        me->enable_path();
        me->receive_damage("gin", 50 );
        tell_object( me, YEL"你莫名其妙看着石壁上那些招式，只覺心裏空蕩蕩的。\n"NOR);
        return;
    }
    if (!me->query_jibie("huoyan-dao"))
    {           me->enable_path();      
        me->improve_jibie("huoyan-dao", 1);
            tell_object( me, WHT"你居然領悟出一套以掌御刀的奇妙刀法。\n"NOR
                             HIM"你的『火焰刀』進步了！\n" NOR);
             return;
        }
    tell_object( me, WHT"你慢慢的比劃着那牆上的小人兒圖形，心中突然靈光一閃\n"
                    WHT"你沉思其中，久久不醒......\n"NOR);
    me->set_temp("block_msg/all", 1);
    time = 30 ;
    call_out("get_gain", time, me );
}

void get_gain( object me )
{
    string msg;
    int point;

    if( !me ) return;

    me->delete_temp("block_msg/all");

    msg = CYN"不知道過了許久，你才從沉思中醒來，發現這門功夫很是奇妙。\n"NOR;
    if ( me->query_lingwu_ratio( "huoyan-dao" )<90)
    {       point=0;
            msg += WHT"只感到石壁上的圖案真是是玄妙萬分。\n" NOR;
     }
    else if ( me->query_jibie( "huoyan-dao" )>149)
    {       point=0;
            msg += WHT"只覺得石壁上的一招儀式都已經了熟於心了。\n" NOR;
     }     
    else {
    point = me->query_xiuwei("blade")/1500;
    msg += HIM"只覺石壁上這套以掌御刀的功夫招式奇妙，威力一定也非同小可。\n" NOR; 
        if( !me->query_jibie("huoyan-dao") )
            msg += HIM"你終於學會了絕世的的刀法。\n"NOR;
     
        msg += HIG "你的『火焰刀』進步了！\n" NOR;
        me->improve_jibie("huoyan-dao", 1);
        me->improve_xiuwei("blade",  point); 
        msg += HIW"你的〖 刀 術 〗的修為有所提高。"NOR;
        me->improve_xiuwei("zonggang", random(point) );        
        msg += HIW"在〖 武 學 〗上的造詣也更深了。\n"NOR;
    }
    
    tell_object( me, msg );
    me->receive_damage("gin", 100);
    me->enable_path();
}