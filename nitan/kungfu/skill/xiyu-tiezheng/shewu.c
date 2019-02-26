// shewu.c 蛇舞
#include <ansi.h>
#include <skill.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me)
{
    int skill,n;
    object ob,snake;
    me=this_player();
    skill = me->query_skill("xiyu-tiezheng",1);

    if( query("neili", me)<500 )
        return notify_fail("你的內力不夠充沛,無法彈出「蛇舞」。\n");
    
    if( query("jingli", me)<50 )
        return notify_fail("你的精力不夠,無法專心彈琴。\n");

    if (me->query_skill("guzheng-jifa",1)<100)
        return notify_fail("你的古箏技法不夠。\n");
    
    if (skill < 100)
        return notify_fail("你的家傳箏曲不夠嫻熟。\n");

    if( !objectp(ob=query_temp("handing", me)) || !ob->valid_as_zheng() )
        return notify_fail("你不拿出箏來，怎麼彈奏？\n"); 

//    if(!environment(me)->query("can_perform_shewu"))  
//        return notify_fail("在這裏彈奏似乎不太適合吧。\n"); 

    if( query("sleep_room", environment(me)) )
        return notify_fail("在這裏彈奏似乎不太適合吧。\n");  

    if( query("no_fight", environment(me)) )
        return notify_fail("在這裏彈奏似乎不太適合吧。\n");  

    if(me->is_busy())
        return notify_fail("你現在正忙着呢！\n");


    message_vision(HIB"$N盤膝而坐，雙手拂琴，時而快疾，時而緩慢，可似乎並未彈出聲音。\n"NOR,me); 
    
    if(skill >= 100 && skill <= 150)  n =10; 
    else if(skill > 150 && skill <= 200) n = 8;
    else if(skill > 200 && skill <= 250) n = 6;
    else if(skill > 250 && skill <= 300) n = 4;
    else if(skill > 300) n = 2;  
//    if (random(n) <10 && random(n) >1 )
    if (random(n) <=2 )
    {
        switch(random(4))
        {
            case 0:
            message_vision("突然，$N感覺身邊黑影閃動，只見一條毒蛇正吐着信子，昂首隨着$N雙手的節奏舞動。\n",me); 
            snake=new("/clone/beast/dushe");
            snake->move(environment(me));
            break;
        
            case 1:
            message_vision("突然，$N感覺身邊黑影閃動，只見一條金環蛇正吐着信子，昂首隨着$N雙手的節奏舞動。\n",me);
            snake=new("/clone/beast/jinshe");
            snake->move(environment(me));
            break;
        
            case 2:
            message_vision("突然，$N感覺身邊黑影閃動，只見一條五步蛇正吐着信子，昂首隨着$N雙手的節奏舞動。\n",me);
            snake=new("/clone/beast/wubushe");        
            snake->move(environment(me));
            break;
        
            case 3:
            message_vision("突然，$N感覺身邊黑影閃動，只見一條竹葉青蛇正吐着信子，昂首隨着$N雙手的節奏舞動。\n",me);
            snake=new("/clone/beast/qingshe");        
            snake->move(environment(me));
            break;
        }
        addn("neili", -100, me);
        addn("jingli", -200, me);
        me->start_busy(5);
    }
    else
    {
        message_vision(GRN"$N心緒紛雜，彈了一會便感血氣翻湧，收功站了起來。\n"NOR,me);
        addn("neili", -100, me);
        addn("jingli", -50, me);
        me->start_busy(3);
    }
    return 1;    
}