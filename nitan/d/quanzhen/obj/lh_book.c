// Code of ShenZhou
//lh_book.c
//wsky
#include <ansi.h>
inherit ITEM;

int do_start(object me);


void create()
{
        set_name("黃皮冊子", ({ "ce zi", "book" }));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", YEL"這是一本黃皮冊子，冊子上寫著《三連環》三個篆字，左下角署名寫著全真長春子。\n"NOR);
                set("material", "paper");
                set("no_drop","這樣東西不能離開你。\n");
                set("no_get","這樣東西不能離開你。\n");
                set("no_steal", 1);
                set("no_sell", 1);
                set("value", 300000);
        }
}

void init()
{
        add_action("do_lingwu","lingwu");
  
}
int do_lingwu(string arg)
{
        object me;
        int cost;
        me=this_player();
         if (me->is_busy())
            return notify_fail("你正忙著呢!\n");
        
        if( arg != query("id", this_object()))return notify_fail("你要領悟什麼?\n");
        
        if(me->query_skill("quanzhen-jian", 1) <100)
            return notify_fail("你的全真劍法不夠嫻熟，無法領悟要決中的奧妙。\n");
            
        if(me->query_skill("taoism",1)<100)
                return notify_fail("你的道學修為不夠。\n");
                
        if(me->query_skill("literate",1)<100)
                return notify_fail("你文學水平太差，看不懂此冊。\n");
        
        if( query("player_id", this_object()) != query("id", me) )
        {
                addn("max_neili", -10, me);
                return notify_fail(HIR"你一讀之下只覺渾身燥熱，內力不聚，說不出的難受。\n"NOR);

        }

        if( query("can_perform/quanzhen-jian/lian", me) == 1 )
                    return notify_fail("你已經領悟三連環精要。\n");
        
        if( query("neili", me)<1000 || query("jing", me)<200 )
                return notify_fail("你精神不佳，無法領悟心法中的奧妙。\n");
                
        cost=query("int", me);
        
        if(cost>=30)
                cost=5;
        else
                cost=35-cost;
        
        set_temp("lianhuan_cost", cost, me);
        
        message_vision(YEL"$N從懷中摸出一本小冊子,全神灌注地閱讀著，不時左手輕輕的比劃。\n" NOR, me);
            me->start_busy((: do_start:));
        return 1;

}

int do_start(object me)
{

        if( query_temp("lianhuan_cost", me) <= 0 )
        {
                if( random(query("int", me))>15 || random(me->query_int())>35 )
                {
                        addn("lingwu_lianhuan", 1, me);
                        tell_object(me,HIY"你靜坐良久，似乎對三連環的運用有一絲領悟。\n"NOR);
                        
                        if( query("lingwu_lianhuan", me) >= 20 )
                        {
                                tell_object  (me,HIG"恭喜，你終于領悟出□三連環□秘決的精要。\n"NOR);
                                set("can_perform/quanzhen-jian/lian", 1, me);
                                delete("lingwu_lianhuan", me);
                                
                        }
                        set("neili", 0, me);
                        set("jingli", 0, me);
        
                }
                else
                {
                        
                        tell_object  (me,HIR"你左思右想始終不能領悟，不用得心中大燥。\n"NOR);
                            addn("neili", -query("max_neili", me), me);
                            me->receive_damage("jing",query("max_jing", me));
                            
                            if( query("neili", me)<0 || query("jing", me)<0 )
                                    me->unconcious();
                                   
                }
        
                return 0;
        }
        addn_temp("lianhuan_cost", -1, me);
        
        return 1;
}