// makelove.c
// updated by Lonely

#include <ansi.h>
#include <command.h>

void do_makelove(object me, object target);
string *loving_msg = ({ 
        HIR "$N輕柔的吻者$n的脣，手掌開始不安分的撫摸$n光滑如緞子般的肌膚，$n嬌喘吁吁，雙手主動的抱住$N...\n" NOR,
        WHT "$N也越來越興奮，終於和$n結為一體，只聽$n如蚊子般的“恩。。”了一聲，似是痛苦，似是舒服...\n" NOR,
        HIW "$N的動作越來越快，越來越猛，$n則配合着$N的節奏釋放出對$N的愛，陣陣呻吟,春光熠熠，春潮綿綿...\n" NOR,
        HIM "洶湧澎湃的高潮過後，$n温順的躺在$N的懷裏，聽着$N的心跳聲，$N輕輕的撫弄着$n光滑的皮膚，無限温柔...\n" NOR,
});

void do_loving(object me, object target, int n);        
void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string no_tell, can_tell;
        object target, *ob;
        object where = environment(me);
        int i;

        seteuid(getuid());

        if( !(query("sleep_room", where) )
              || (query("no_sleep_room", where)) )
                return notify_fail("這裏做愛可不太好，找個安全點的地方吧！\n");

        if (! arg || ! objectp(target = present(arg, where)))
                return notify_fail("你想和誰做愛？\n");

        if( !target->is_character() || query("not_living", target) )
                return notify_fail("看清楚了，那不是活人！\n");

        if( !query("can_speak", target) )
                return notify_fail("你瘋了？想和" + target->name() + "性交？\n");

        if (me == target)
                return notify_fail("你自己要和自己...你還是快回家自己研究吧。\n");

        if (me->is_busy())
                return notify_fail("你現在正忙着呢！\n");

        if (me->is_fighting())
                return notify_fail("邊動手邊做愛？你果然很有創意！\n");

        if (! userp(target))
                return notify_fail(target->name() + "一嚇，怒視着你。(還是別惹人家了)\n");

        if( query("gender", me) == "無性" )
                return notify_fail("你這人都這模樣了還有興致？真是少見。\n");

        if( query("gender", me) == query("gender", target) )
                return notify_fail("同性戀麼...還是自己好好研究怎麼弄吧，這條指令不太合適。\n");

        if( query("age", me)<16 )
                return notify_fail("你還沒有發育完全，就想這事？\n");

        if (me->query_condition("huaiyun") > 0 ||
            target->query_condition("huaiyun") > 0)
                return notify_fail("搞笑啊？孕婦要注意寶寶安全，怎麼能這樣？忍一忍拉！\n");
                
        if( query_temp("pending/makelove", me) == target )
                return notify_fail("你已經向別人提出要求了，可是人家還沒有答應你。\n");

        if( query("jing", me)*100/query("max_jing", me)<80 )
                return notify_fail("你的精神不濟，現在沒有力氣和人家做愛。\n");

        if( query("qi", me)*100/query("max_qi", me)<60 )
                return notify_fail("你的體力不支，現在沒有力氣和人家做愛。\n");

        if( query("gender", me) == "男性" && 
            time()-query_temp("last_makelove", me)<120 )
                return notify_fail("你現在是有心無力，沒法再來一次。\n");

        no_tell=query("env/no_tell", target);
        if (no_tell == "all" || no_tell == "ALL" ||
            is_sub(query("id", me),no_tell) )
        {
                can_tell=query("env/can_tell", target);
                if( !is_sub(query("id", me),can_tell) )
                        return notify_fail("這個人不想聽你羅嗦啦。\n");
        }

        ob = all_inventory(where);
        for (i = 0; i < sizeof(ob); i++)
                if (ob[i]->is_character() && ob[i] != me &&
                    ob[i] != target && ! wizardp(ob[i]))
                        return notify_fail("這兒還有別人呢，多不好意思呀！\n");
                        
        if( query_temp("pending/makelove", target) == me )
        {
                delete_temp("pending/makelove", target);
                if( query("gender", me) == "男性" )
                        message_sort(YEL "$N過了好半響，實在受不了$n的挑逗突然一把將$n緊緊抱住壓在牀上....\n" NOR,
                                     me, target);

                else
                        message_sort(YEL "$N極力的忍受着$n火熱的挑逗，心頭小鹿撞擊不停，終於癱軟在$n的懷裏，"
                                     "被$n一把橫抱了起來，輕柔的放在牀上....\n" NOR, me, target);
                            
                do_makelove(me, target);
                return 1;
        }

        set_temp("pending/makelove", target, me);

        message("vision", me->name() + "悄悄的和" + target->name() + "説了幾句話。\n",
                environment(me), ({ me, target }));
                
        if( query("gender", me) == "男性" )
        {
                message_sort(YEL "$N輕輕的注視着$n，雙手摟在$n的小蠻腰，輕柔的吻着$n的小耳垂....\n" NOR, 
                             me, target);
                me->force_me("tell"+query("id", target)+
                             " 好寶貝，今天就和我歡樂一次吧。");
        } else
        {
                message_sort(YEL "$N的小臉兒紅撲撲的，纏上來勾住$n的脖子，胸前緊緊的貼着$n的胸膛，"
                             "小嘴嘟嘟的湊上來輕輕的吻着$n的嘴脣....\n" NOR, me, target);                
                me->force_me("tell"+query("id", target)+
                            " 你現在想要我麼？");
        }

        return 1;
}

void do_makelove(object me, object target)
{
        mapping armor;
        string msg;
        string msg1, msg2;
        object man, woman;        

        if( query("gender", me) == "男性" )
        {
                man = me;
                woman = target;
        } else
        {
                man = target;
                woman = me;
        }
        
        message_vision(HIB "...屋裏的" + HIR "紅燭" + HIB "被吹滅了...\n" NOR, me, target);
        
        msg = YEL "$N輕輕的摟着$n，雙手從$n的臉頰慢慢的撫摸下去直至胸膛，只見$p"
              "不由的顫動了一下，一時間意亂情迷，雙手緊緊的抱住了$N，把臉深"
              "深的埋在$N的懷中，磨擦着$P的胸口，霎時間滿堂春意，錦繡亦添光"
              "華，兩人漸漸的進入了忘我的狀態。" NOR;
        msg1 = replace_string(msg, "$N", "你");
        msg1 = replace_string(msg1, "$n", woman->name());
        msg1 = replace_string(msg1, "$P", "你");
        msg1 = replace_string(msg1, "$p", "她");

        msg2 = replace_string(msg, "$N", man->name());
        msg2 = replace_string(msg2, "$n", "你");
        msg2 = replace_string(msg2, "$P", "他");
        msg2 = replace_string(msg2, "$p", "你");

        msg = replace_string(msg, "$N", man->name());
        msg = replace_string(msg, "$n", woman->name());
        msg = replace_string(msg, "$P", "他");
        msg = replace_string(msg, "$p", "她");

        msg1 = sort_string(msg1, 60);
        msg2 = sort_string(msg2, 60);
        msg  = sort_string(msg, 60);

        message("vision", msg1, man);
        message("vision", msg2, woman);
        message("vision", msg, environment(man), ({ man, woman }));      
        
        if( armor=query_temp("armor", me) && sizeof(armor) )
                me->force_me("remove all");

        if( armor=query_temp("armor", target) && sizeof(armor) )
                target->force_me("remove all");
                
        message_sort(HIM "$n閉上眼睛靜靜地躺在牀上，感到自己身上的衣服一件一件的被脱掉，突然$n感到$N火燙的身體壓上了自己...\n" NOR, 
                     man, woman);

        remove_call_out("do_loving");
        call_out("do_loving", 1, man, woman, 0); 

}

void do_loving(object me, object target, int n)
{
        remove_call_out("do_loving"); 
        message_sort(loving_msg[n], me ,target); 
        
        if (n == sizeof(loving_msg) - 1) 
        {
                remove_call_out("do_over");
                call_out("do_over", 3, me, target);
                return;
        }
        call_out("do_loving", 3, me, target, n + 1); 
        return;
}

void do_over(object me, object target)
{
        set_temp("last_makelove", time(), me);
        addn("sex/"+target->name(1), 1, me);
        addn("sex/times", 1, me);
        if( query("sex/times", me) == 1 )
                set("sex/first", target->name(1), me);

        set("jing", 20, me);
        set("qi", 50, me);

        set_temp("last_makelove", time(), target);
        addn("sex/"+me->name(1), 1, target);
        addn("sex/times", 1, target);
        if( query("sex/times", target) == 1 )
                set("sex/first", me->name(1), target);

        if( query("id", target) == query("couple/couple_id", me )
         && query("id", me) == query("couple/couple_id", target )
        &&  ! target->query_condition("huaiyun")
         && !query("couple/child_id", me )
         && !query("couple/child_id", target )
        &&  random(100) < 21)
        {
                message("shout",HIR"【家有喜事】："HIM"恭喜"HIY+query("name", me)+"("+query("id", me)+")"
                        HIM"與"HIY+query("name", target)+"("+query("id", target)+")"HIM"做了準父母。\n"NOR,
                        users());
                message_vision(HIY "\n$N突然覺得一陣做嘔，旋即羞紅着臉，咬咬牙想起了那個該死的。\n" NOR, target);
                message_vision(HIM"\n$N懷孕了。趕快通知孩子的爸爸"HIY+query("name", me)+"("+query("id", me)+")"HIM"啊？．．．\n"NOR,target);
                target->apply_condition("huaiyun", 1200);           
                set("longbak",query("long",  target), target);
                set("long", HIY"\n"+query("name", target)+"挺着個大肚子，一看就知道是懷孕了，混身散發出一股慈祥的母愛。\n"NOR, target);
        }
}

int help(object me)
{
        write(@HELP
指令格式 : makelove <id>
 
你可以用這個指令想你喜歡的人提出做愛的要求，當然要在安全的地
方。如果對方對你設置了no_tell 的選項，你就無法提出這個要求。
做愛以後會極大的消耗男方的精和氣。

HELP );
        return 1;
}