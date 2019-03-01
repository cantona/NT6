// drift_sense.c
#include <ansi.h>
//inherit SSERVER;

int conjure(object me, object target)
{
        object ob;
        int i;

        if ( !query("reborn/times", me) ) return notify_fail("你還沒有掌握奇門遁甲。\n");

        if ( !wizardp(me) && me->query_family() != "桃花島" && member_array("桃花島", query("reborn/fams", me)) == -1 )
                return notify_fail("只有桃花島的玩家才能領悟奇門遁甲。\n");

        if ( me->is_fighting() ) return notify_fail("戰鬥中你沒有時間打洞,呵呵！\n");
          
        if ( !query("outdoors", environment(me)) ) return notify_fail("□！□！□！這裡的地板，似乎好硬喲！\n");

        ob = first_inventory(me);
        while ( ob )
        {
                if (ob->is_character() && !ob->is_corpse() )
                        return notify_fail(ob->name()+"不能和你一起鑽洞！\n");
                ob = next_inventory(ob);
        }
        if ( query("jing", me) < 30 ) return notify_fail("你的精力不夠！\n");
        if ( target ) return notify_fail("奇門遁術只能自己使用！\n");

        if ( virtualp(environment(me)) ) return notify_fail("這裡無法使用神通!\n");
        write("你要鑽到哪一個人身邊？");
        input_to( (: call_other, __FILE__, "select_target", me :));
        return 1;
}

void select_target(object me, string name)
{
        object ob, env;
        mapping exits;
        int i;
        
        if ( !name || name=="" ) 
        {
                write("中止施法。\n");
                return;
        }
        ob = find_player(name);
        if ( !ob || !me->visible(ob) || wizardp(ob) ) ob = find_living(name);
        if ( !ob || !me->visible(ob) || !living(ob) || wizardp(ob) ) 
        {
                write("你無法感受到這個人的精力 ....\n");
                return;
        }
        if ( !objectp(env=environment(ob)) )
        {
                write("你無法感受到這個人的精力 ....\n");
                return;
        }
        if ( random(query("jing",me))<30 )
        {
                write("你無法感覺到對方的存在\n");
                return;
        }
        /*
        if ( query("quest/quest_type",me)=="殺"
                && (string)query("quest/quest",me)==ob->short()
                && query("quest/task_time",me)<time() )
        {
                write("你無法感受到這個人的精力 ....\n");
                return;
        }
        */
        if ( me->is_fighting() ) 
        {
                write("戰鬥中你沒有時間打洞,呵呵！\n");
                return;
        } 

        me->receive_damage("jing", 30);
        if ( query("jingli",ob) > random(query("jingli",me)) 
                || !random(3)
                || time() - query_temp("do_flee",me) < 2 ) 
        {
                message_vision( HIY "$N飛快地在地上扒了個洞，鑽了進去 ....\n" NOR, me);
                write("咚咚幾聲，你挖到幾塊大石頭，哇，沒門！\n");
                message( "vision",HIY+me->name()+"一臉氣急敗壞，灰頭灰臉地從洞裡又鑽了回來。\n" NOR, environment(me),({me}));
                return;
        }
        set_temp("do_flee",time(),me);
        if ( !environment(ob) || query("no_magic",environment(ob)) 
                || query("no_fight", environment(ob)) 
                || random(me->query_skill("qimen-wuxing",1)) < 30 ) 
        {
                write("你手指都磨破了，才挖出個老鼠洞，MY GOD，怎麼鑽呀！\n");
                message( "vision",HIY+me->name()+"使勁把臉往土裡蹭了幾下，真無聊。\n" NOR, environment(me),({me}));
                return;
        }
        exits=query("exits", environment(ob));
        if (!mapp(exits) || !sizeof(exits) )
        {
                write("你挖到一堵石牆，不得不退了回來！\n");
                message( "vision",HIY+me->name()+"一臉氣急敗壞，灰頭灰臉地從洞裡又鑽了回來。\n" NOR, environment(me),({me}));
                return;
        }
        if ( domain_file(base_name(environment(ob)))=="shaolin" 
                || domain_file(base_name(environment(ob)))=="newbie" 
                || domain_file(base_name(environment(ob)))=="mingjiao" 
                || domain_file(base_name(environment(ob)))=="shenlong" 
                || domain_file(base_name(environment(ob)))=="wizard" 
                || domain_file(base_name(environment(ob)))=="death" ){
                write("那裡佛氣好重，非道術所能及！\n");
                message( "vision",HIY+me->name()+"一臉氣急敗壞，灰頭灰臉地從洞裡又鑽了回來。\n" NOR, environment(me),({me}));           
                return;         
        }               

        if ( domain_file(base_name(environment(ob)))=="taohua" || domain_file(base_name(environment(ob)))=="binghuo"){
                write("恭喜你，你挖到了泉水哩！\n");
                message( "vision",HIY+me->name()+"從口了吐出幾口水大叫：好咸呀！\n" NOR, environment(me),({me}));
                return;
        }

        if ( domain_file(base_name(environment(ob)))=="xiakedao" ){
                write("恭喜你，你挖到了茅坑哩！\n");
                message( "vision",HIY+me->name()+"從口了吐出幾口大糞大叫：好臭呀！好臭呀！\n" NOR, environment(me),({me}));
                return;
        }

        if ( domain_file(base_name(environment(ob)))=="gaochang" ) {
                write("那裡太遙遠了。\n");
                message( 
                        "vision",HIY+me->name()+"一臉氣急敗壞，灰頭灰臉地從洞裡又鑽了回來。\n" NOR, environment(me),({me}));
                return;
        }

        if ( sscanf(base_name(environment(ob)), "/data/%*s") ){
                write(HIM "那裡是人家的私宅，想進去偷東西啊?\n" NOR);
                message( "vision",HIY+me->name()+"一臉氣急敗壞，灰頭灰臉地從洞裡又鑽了回來。\n" NOR, environment(me),({me}));
        }

        if ( !environment(ob) || wizardp(ob) ){
                 message_vision( HIY "$N飛快地在地上扒了個洞，鑽了進去 ....\n" NOR, me);
                write("你在地底鑽了半天，發現"+ob->name()+"似乎在天上 ....\n");
                message( "vision",HIY+me->name()+"一臉氣急敗壞，灰頭灰臉地從洞裡又鑽了回來。\n" NOR, environment(me),({me}));
                return;
        }
        
        /*
        if( userp(ob) )
        {
                message_vision( HIY "$N飛快地在地上扒了個洞，鑽了進去 ....\n" NOR, me);
                write("你在地底鑽了半天，發現似乎不著邊際 ....\n");
                message( "vision",HIY+me->name()+"一臉氣急敗壞，灰頭灰臉地從洞裡又鑽了回來。\n" NOR, environment(me),({me}));
                return;
        }
        */
        message_vision( HIY "$N飛快地在地上扒了個洞，鑽了進去 ....\n" NOR, me);
        message( "vision", HIY "\n很快，洞口又封了起來，" + me->name() + "不見了！\n\n" NOR, environment(me), ({ me }) );


        if( file_size(file_name(environment(ob))+".c")<=0 )
        {
                write(HIY"但是，很快地你發現那裡似乎並不存在，于是又灰頭土臉地退了回來。\n"NOR);        
                return;
        } else 
                me->move(environment(ob));
        message( "vision", HIY "\n一個黑影突然從地下冒了出來，噴了你滿臉的灰！\n\n" NOR,
                environment(ob), ({ me }) );
        
        /*
        if( me->query_skill("taoism",1) > me->query_skill("qimen-wuxing", 1) )
                me->improve_skill("qimen-wuxing", random(me->query_skill("taoism")), 0);
        else    
                me->improve_skill("qimen-wuxing", random(me->query_skill("taoism")), 1);
        */
}


