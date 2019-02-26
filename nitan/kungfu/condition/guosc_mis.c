// guosc_mis.c
// 郭靖守城任務

#include <ansi.h>
#include <login.h>

int update_condition(object me, int duration)
{
        object room;
        object* ob_list;
        int i,stat;
                
        room = environment(me);

        me->apply_condition("guosc_mis", duration - 1 );
        if( query_temp("guosc_mis_flag", me) )
        {
                if( query_temp("guosc_mis_where", me) != query("short", environment(me)) )
                {
                        message_vision( HIY"一個宋兵跑過來對$N説道：叫你守城，你卻到處閒逛，我去報告郭大俠！\n"NOR,me);
                }
                else set_temp("guosc_mis_flag", 2, me);
                if( query_temp("guosc_mis_flag", me) == 2 && query_temp("guosc_mis_where", me) == query("short", environment(me)) )
                {
                        switch( random(8) )
                        {
                                case 0:
                                        message_vision( HIY"$N正站在城牆上密切注視着城下"HIR"蒙古兵"HIY"的一舉一動。\n"NOR,me);
                                        break;
                                case 1:
                                        message_vision(HIY"$N指揮一隊宋兵吆喝着將無數巨石從城牆上推下來，城下的"HIR"蒙古兵"HIY"一時不備，死傷不少。\n"NOR,me);
                                        break;
                                case 2:
                                        message_vision(HIC"但聽一聲梆子響，從箭垛後面鑽出無數士兵，箭如飛蝗，城外的"HIR"蒙古兵"HIC"紛紛中箭倒下。\n"NOR,me);
                                        break;
                                case 3:
                                        message_vision(HIR"$N大叫：放火、放火。城上扔下無數燃着的火把，慘叫聲中，蒙古的士兵死傷甚眾。\n"NOR,me);
                                        break;
                                case 4:
                                        message_vision(HIC"城外一聲號角傳來，蒙古靼子發動了新一輪的攻勢，城中箭如雨下，守城的宋兵死傷不少。\n"NOR,me);
                                        me->receive_wound("jing", 50+random(50));
                                        me->receive_damage("qi", 300+random(100));
                                        break;
                                case 5:
                                        message_vision(HIR"$N大叫一聲：大家小心。城外蒙古兵的投石車飛來無數巨石，慘叫聲中，城中的守兵死傷甚眾。\n"NOR,me);
                                        me->receive_wound("jing", 50+random(50));
                                        me->receive_damage("qi", 300+random(100));
                                        break;
                                case 6:
                                        message_vision(HIR"城中宋兵大叫：着火啦、着火啦。城中的蒙古奸細趁守軍不備四處放火，一片救火聲中，城中的軍備損失慘重！\n"NOR,me);
                                        me->receive_wound("jing", 50+random(50));
                                        me->receive_damage("qi", 300+random(100));
                                        break;
                                case 7:
                                        message_vision(HIR"$N大叫：小心暗器！蒙古奸細趁守軍不備射出不少暗器，城中的軍士一時大意，不少人中了偷襲！\n"NOR,me);
                                        me->apply_condition("anqi_poison", 3+random(3));
                                        break;
                                case 8:
                                        message_vision(HIY"城外蒙古兵發動一輪急攻，但守城的宋兵在$N的帶領下卻早有防備，沒有受到損失。\n"NOR, me);
                                        break;
                        }
                }
        }
        if(duration <1)
        {
                message_vision( CYN"\n一個守城宋兵跑過來説道：蒙古靼子暫時被擊退了，$N可以回去覆命了！\n"NOR,me);
                if( query_temp("guosc_mis_flag", me) )
                {
                        set_temp("guosc_mis_flag", 3, me);
                }
                ob_list = children("/d/xiangyang/task/robber1");
                for(i=0; i<sizeof(ob_list); i++) 
                if(environment(ob_list[i]))
                {
                        message_vision("$N歎道：襄陽守軍竟有高人協助，撤呼！\n",ob_list[i]);        
                        destruct(ob_list[i]);
                }
                ob_list = children("/d/xiangyang/task/robber2");
                for(i=0; i<sizeof(ob_list); i++) 
                if(environment(ob_list[i]))
                {
                        message_vision("$N歎道：襄陽守軍竟有高人協助，撤呼！\n",ob_list[i]);    
                        destruct(ob_list[i]);
                }
                ob_list = children("/d/xiangyang/task/robber3");
                for(i=0; i<sizeof(ob_list); i++)
                if(environment(ob_list[i]))
                {
                        message_vision("$N歎道：襄陽守軍竟有高人協助，撤呼！\n",ob_list[i]);
                        destruct(ob_list[i]);
                }

                return 0;
        }
        return 1;
}

string query_type(object me)
{
        return "job";
}
