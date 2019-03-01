// ride.c

#include <ansi.h>

inherit F_CLEAN_UP;

int do_ride(object me, object ob);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object obj, env;
        object horse, person;
        string who, s1, s2;
        int i, level, rec_n, max_rec;
        mapping self_flag;
        string *ps;

        if( !arg ) return notify_fail("你要騎什麼東西？\n");
        
        env = environment(me);
        // 邀請人上坐騎
        sscanf(arg, "%s %s", s1, s2);
        if( s1 == "up" ) // s1 == arg;
        {
                if( !MEMBER_D->is_valid_member(query("id", me)) )
                        return notify_fail("對不起，只有會員才能邀請別人上坐騎。\n");

                if( sscanf(arg, "up %s", who) == 1 )
                {
                        if( !objectp(horse=query_temp("is_riding", me)) )
                                return notify_fail("你連坐騎都沒有，怎麼要求別人上坐騎？\n");

                        if( !objectp(person = present(who, env)) )
                                return notify_fail("這裡沒有這個人！\n");

                        if( query_temp("is_riding", person) )
                                return notify_fail("別人已經有坐騎了。\n");

                        if( objectp(query_temp("is_rided_follow", horse)) )
                                return notify_fail("你的坐騎上已經有人了。\n");

                        message_vision(HIW "$N勒坐騎于前，對$n說道：請上坐騎一敘！\n" NOR, me, person);
                        set_temp("ride_up",query("id", me), person);
                        tell_object(person, HIG + me->name() + "邀請你上坐騎，如果同意請輸入 ride ok 。\n" NOR);                  
                        return 1;
                }

                return notify_fail("你要邀請誰上坐騎？\n");
        }

        // 同意邀請上坐騎
        if( arg == "ok" )
        {
                if( !stringp(who=query_temp("ride_up", me)) )
                        return notify_fail("沒有人邀請你上坐騎。\n");

                if( query_temp("is_riding_follow", me) )
                        return notify_fail("你還是先下坐騎（ride down）再說吧。\n");
        
                person = find_player(who);
        
                if( !objectp(person) ) return notify_fail("這裡沒有這個人。\n");

                if( environment(me) != environment(person) )
                        return notify_fail("這裡沒有這個人。\n");
                
                if( !objectp(horse=query_temp("is_riding", person)) )
                        return notify_fail(person->name() + "似乎沒有坐騎吧！\n");

                if( query_temp("is_rided_follow", horse) )
                        return notify_fail(person->name() + "的" + horse->name() + NOR "已經有人在乘坐了。\n");

                delete_temp("ride_up", me);
                MAP_D->me_ride(me, horse);
                
                return 1;
                
        }
        
        // follower 強行下坐騎
        if( arg == "down" )
        {
                if( objectp(horse=query_temp("is_riding_follow", me)) )
                {
                        delete_temp("is_riding_follow", me);
                        delete_temp("is_rided_follow", horse);
                
                        message_vision("$N一翻身， 從" + horse->name() + NOR "跳了下來。\n" NOR, me);

                        return 1;
                }
                
                return notify_fail("OK.\n");            
        }

        if (arg == "kick")
        {
                if( objectp(horse=query_temp("is_riding", me)) )
                {                       
                        if( objectp(person=query_temp("is_rided_follow", horse)) )
                                delete_temp("is_riding_follow", person);

                        delete_temp("is_rided_follow", horse);

                        message_vision("$N強行要求所有人下坐騎。\n", me);

                        return 1;               
                }

                return notify_fail("你並沒有騎坐騎。\n"); 
        }
        
        if( arg == "?" )
        {
                self_flag = query("horse/flags", me);
                if( mapp(self_flag) && sizeof(self_flag) )
                {
                        ps = keys(self_flag);
                        for (i = 0; i < sizeof(ps); i ++)
                                write(sprintf(HIG "%-20s%-20s\n" NOR, ps[i], get_object(self_flag[ps[i]])->short()));
                } else
                        write("你目前沒有記錄地點。\n");

                return 1;
        }

        if( sscanf(arg, "rec %s", who) == 1 )
        {
                env = environment(me);

                // 判斷記錄是否已經超過限制
                if( !MEMBER_D->is_valid_member(query("id", me))) max_rec = 0;
                else
                {
                        level = MEMBER_D->db_query_member(me, "vip");
                        switch( level )
                        {
                                case 3:
                                        max_rec = 4;
                                        break;
                                case 2:
                                        max_rec = 3;
                                        break;
                                case 1:
                                        max_rec = 2;
                                        break;
                                default:
                                        max_rec = 1;
                                        break;                          
                        }
                }

                rec_n=sizeof(query("horse/flags", me));
                max_rec+=query("horse/stone", me);

                if( rec_n >= max_rec )
                {
                        write(HIR "你的記錄已達到 " + sprintf("%d", rec_n) + " 條，已滿！\n" NOR);
                        write(HIR "你可以嘗試使用以獻□錁徑來增加你的記錄數：\n\n" NOR);

                        write(HIC "普通玩家：         Max = 0 條\n" NOR);
                        write(HIM "普通會員：         Max = 1 條\n" NOR);
                        write(WHT "白銀會員：         Max = 2 條\n" NOR);
                        write(HIY "黃金會員：         Max = 3 條\n" NOR);
                        write(HIW "白金會員：         Max = 4 條\n" NOR);
                        write(HIG "冊 坐騎 石：         每個冊坐騎石增加 1 條 Max\n" NOR);
                        
                        return 1;
                }
 
                if( !objectp(horse=query_temp("is_riding", me)) )
                        return notify_fail("你還是先找匹坐騎再說吧？\n"); 

                if( stringp(MAP_D->get_trans_path(who)) )
                        return notify_fail("對不起，編號 " + who + " 已經存在，請另取一個編號。\n");

                if( stringp(query("horse/flags/"+who, me)) )
                        return notify_fail("對不起，編號 " + who + " 已經存在，請另取一個編號。\n");

                // 如果房間沒有出口不能記錄
                if( !sizeof(query("exits", env)) )
                        return notify_fail("此地點不能記錄。\n");

                // no_magic 不能記錄
                if( query("no_magic", env) || query("maze", env) )
                        return notify_fail("此地點不能記錄。\n");

                if( clonep(env) || !env->is_room() )
                        return notify_fail("此地點不能記錄。\n");

                if( domain_file(base_name(environment(me))) == "city2" )
                        return notify_fail("此地點不能記錄。\n");

                if( sscanf(base_name(environment(me)), "/data/%*s" ) )
                        return notify_fail("此地點不能記錄。\n");

                //if( !query("outdoors", env) )
                //        return notify_fail("此地點不能記錄。\n");
                        
                set("horse/flags/"+who, base_name(env), me);
                me->save();
                write(HIG "記錄成功！\n" NOR);

                return 1;

        } 

        if( sscanf(arg, "unrec %s", who) == 1 )
        {
                if( !objectp(horse=query_temp("is_riding", me)) )
                        return notify_fail("你還是先找匹坐騎再說吧？\n"); 

                if( !stringp(query("horse/flags/"+who, me)) )
                        return notify_fail("對不起，編號 " + who + " 不存在，請使用 rideto 查看。\n");

                delete("horse/flags/"+who, me);
                me->save();

                write(HIG "刪除記錄成功。\n" NOR);

                return 1;
                
        }
        
        if( query_temp("is_riding", me) )
                return notify_fail("你已經有座騎了！\n");

        if( query_temp("is_riding_follow", me) )
                return notify_fail("你先下馬（ride down）再說吧！\n");

        if( me->is_busy() )
                return notify_fail("你上一個動作還沒有完成！\n");

        if( me->is_fighting() )
                return notify_fail("你還在戰鬥中！沒空騎上去。\n");

        // Check if a container is specified.

        if (! objectp(obj = present(arg, environment(me))))
                return notify_fail("你沒有這樣東西可騎。\n");

        if( !query("ridable", obj) )
                return notify_fail("這個東西你也要騎？當心你的屁股！\n");

        if( query("owner", obj) && query("owner", obj) != query("id", me) )
                return notify_fail("它已經有主人了，你無法駕馭它！\n");

        return do_ride(me, obj);
        write("騎上去了。\n");
}

int do_ride(object me, object obj)
{
        object old_env, *guard;

        if( !obj ) return 0;

        if( guard=query_temp("guarded", obj)){
                guard = filter_array(guard, (: objectp($1) && present($1, environment($2)) && living($1) && ($1!=$2) :), me);
                if( sizeof(guard) )
                        return notify_fail( guard[0]->name()
                                + "正守在" + obj->name() + "一旁，防止任何人騎走。\n");
        }

        obj->set_weight(1);
        if( obj->move(me) )
        {
                message_vision( "$N飛身躍上$n，身手很是矯捷。\n", me, obj );
                set_temp("is_rided_by", me, obj);
                set_temp("is_riding", obj, me);
        }
        else
        {
                message_vision( "$N身上帶的東西太重了，無法騎到$n身上去。\n", me, obj );
        }

        return 1;
}

int help(object me)
{
	write(@HELP
指令格式 :

ride <生物名>        騎上代步的已馴養的動物。
ride up <id>         邀請別人上馬（會員指令）。
ride ok              同意別人的邀請。
ride down            從別人的馬上下馬（此指令是專為同乘他人的馬的玩家設置的）。
ride kick            讓馬上的同乘者下馬。            
ride rec <代號>      可以讓你記錄當前地點到rideto列表中去，以後可以直接騎上馬
                     使用 rideto <代號> 到達這個地方。

                     普通玩家：               可記錄 0 條。
                     普通會員：		      可記錄 1 條。
                     白銀會員：		      可記錄 2 條。
                     黃金會員：		      可記錄 3 條。
                     白金會員：		      可記錄 4 條。
                     使用冊馬石一次：	      可增加最大可記錄空間 1 條。

ride unrec <代號>    刪除指令代號的記錄。
                       
HELP
    );
    return 1;
}
