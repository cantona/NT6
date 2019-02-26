// huaiyun.c
// updated by linux
// updated by Lonely

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int birth1(object me);
int birth2(object me);
int birth3(object me);

int update_condition(object me, int duration)
{
        if (duration < 1) return 0; 

        if (duration == 1200)
        {
                tell_object(me, HIY "你覺得周圍的人好像都在偷偷看你，心裏好不自在！\n" NOR);
                message("vision", me->name() + HIY "羞澀的低着頭，擺弄着自己的衣角。\n" NOR,
                        environment(me), me);
        } else 
        if (duration == 800)
        {
                tell_object(me, HIY "你覺得周圍的人都好奇怪，對你指指點點，真是討厭！\n" NOR);
                message("vision", me->name() + HIY "瞪着你，好像你欠了她什麼似的……\n" NOR,
                        environment(me), me);
        } else 
        if (duration == 400)
        {
                tell_object(me, HIY "你覺得周圍的人都在笑嘻嘻的看着你，可能他們已經看出來了你……。\n" NOR);
                message("vision", me->name() + HIY "用一種異常慈祥的目光，反覆打量着自己的肚子。\n" NOR,
                        environment(me), me);
        } else 
        if (duration == 200)
        {
                tell_object(me, HIY "你覺得周圍的人與世界都是那麼的美好，心情無比的舒暢！\n" NOR);
                message("vision", me->name() + HIY "一身充滿了安詳的氣息，那積聚着母愛的目光不時掃視着周圍！\n" NOR,
                        environment(me), me);
        } else 
        if (duration == 20 || duration == 10)
        {
                tell_object(me, HIY "你覺得周圍的人都用着極其關切的目光注視着你，難道是……快了？\n" NOR);
                message("vision", me->name() + HIY "已經行動十分的遲緩了，不時的停下來喘氣。\n" NOR,
                        environment(me), me);
        } else 
        if (duration == 1)
        {
                tell_object(me, HIY "周圍的人都驚訝的合不上了嘴巴，一定是見到了什麼奇怪事情！\n"
                                "看來你是馬上就要生了，請趕緊和孩子的父親去揚州藥鋪的二樓產房，否則會有生命危險的！\n" NOR);
                message("vision", me->name() + HIY "捂着大大的肚子，蹲在了地上，臉上一副極其痛苦的神情！\n" NOR,
                        environment(me), me);
                remove_call_out("birth1");
                call_out("birth1", 100, me);
        }
        me->apply_condition("huaiyun", duration - 1);
        return 1;
}

int birth1(object me)
{
        object target;        
        
        if( (query("age", me))<18 )
        {
                message_vision(HIY "\n$N似乎覺得腹中一陣巨痛，大叫一聲，由於$N年齡太小，不適合生育，\n所以$N的孩子流產了，好可憐啊！\n" NOR, me);
                set("qi", 1, me);
                set("jing", 1, me);
                set("neili",query("neili",  me)/2, me);
                set("long",query("longbak",  me), me);
                delete("longbak", me);
                me->unconcious();
                return 1;
        } 
        
        if (base_name(environment(me)) != "/d/city/chanfang")
        {
                message_vision(HIY "\n$N似乎覺得腹中一陣巨痛，大叫一聲，由於這裏的環境實在是太惡劣了，\n所以$N的孩子流產了，好可憐啊！\n" NOR, me);
                set("qi", 1, me);
                set("jing", 1, me);
                set("neili",query("neili",  me)/2, me);
                set("long",query("longbak",  me), me);
                delete("longbak", me);
                me->unconcious();
                return 1;
        }
         
        target=find_player(query("couple/couple_id", me));
        if (! target || environment(target) != environment(me))
        {
                message_vision(HIY "\n$N似乎覺得腹中一陣巨痛，大叫一聲，由於關鍵時刻你的男人沒有守侯在身邊，\n所以$N的孩子流產了，好可憐啊！\n" NOR, me);
                set("qi", 1, me);
                set("jing", 1, me);
                set("neili",query("neili",  me)/2, me);
                set("long",query("longbak",  me), me);
                delete("longbak", me);
                me->unconcious();
                return 1;
        }
        
        if (! me->is_busy())
                me->start_busy(15);
        if (! target->id_busy())
                target->start_busy(15);
                
        message_vision(HIY "\n$N忽覺腹中一陣顫動，趕緊拉住$n的手，柔聲説道：要生了! \n" NOR, me, target);
        remove_call_out("birth2");
        call_out("birth2", 15, me);
      
        return 1;
}

int birth2(object me)
{        
        object target;
         
        target=find_player(query("couple/couple_id", me));
        if (! target || environment(target) != environment(me))
        {
                message_vision(HIY "\n$N似乎覺得腹中一陣巨痛，大叫一聲，由於關鍵時刻你的男人沒有守侯在身邊，\n所以$N的孩子流產了，好可憐啊！\n" NOR, me);
                set("qi", 1, me);
                set("jing", 1, me);
                set("neili",query("neili",  me)/2, me);
                set("long",query("longbak",  me), me);
                delete("longbak", me);
                me->unconcious();
                return 1;
        }  
              
        if (! me->is_busy())
                me->start_busy(15);
        if (! target->id_busy())
                target->start_busy(15);
                        
        message_vision(HIY "\n$N已是大汗淋漓，一直都在呼天搶地，雙手緊緊扣住$n的手不放。\n\n嬰兒已經探出了頭．．．\n" NOR, me, target);
        remove_call_out("birth3");
        call_out("birth3", 15, me);
        return 1;
}

int birth3(object me)
{
        object target;
        object baby;
        
        target=find_player(query("couple/couple_id", me));
        if (! target || environment(target) != environment(me))
        {
                message_vision(HIY "\n$N似乎覺得腹中一陣巨痛，大叫一聲，由於關鍵時刻你的男人沒有守侯在身邊，\n所以$N的孩子流產了，好可憐啊！\n" NOR, me);
                set("qi", 1, me);
                set("jing", 1, me);
                set("neili",query("neili",  me)/2, me);
                set("long",query("longbak",  me), me);
                delete("longbak", me);
                me->unconcious();
                return 1;
        }  
                
        message_vision(HIY "\n「哇」．．．，嬰兒出世了！\n" +
                "\n$N面色蒼白，斜倚在牀頭，看看孩子滿意地露出一絲微笑。\n" NOR, me, target);
        set("long", "\n她看起來已經是一個成熟的少婦了哦。\n"NOR, me);
        delete("longbak", me);

        set("neili", 0, me);
        set("qi", 1, me);
        set("jing", 1, me);
        
        baby = new("/clone/user/baby");
        if (random(2) > 0)
        {
                set("gender", "男性", baby);
                baby->set_name("小"+query("name", target),
                               ({"xiao_"+query("id", target),"baby"}));
                               
                set("long", "這是"+query("name", target)+"和"+query("name", me)+"的孩子。長的好像"+query("name", target)+"啊！\n", baby);
                message("shout",HIR"【家有喜事】"HIM"恭喜"HIR+query("name", me)+"("+query("id", me)+")"
                        HIM"給"HIR+query("name", target)+"("+query("id", target)+")"HIM"添了一個大胖小子。\n"NOR,
                        users());
        } else
        {
                set("gender", "女性", baby);
                baby->set_name("小"+query("name", me),
                               ({"xiao_"+query("id", me),"baby"}));
                               
                set("long", "這是"+query("name", target)+"和"+query("name", me)+"的孩子。長的好像"+query("name", me)+"啊！\n", baby);
                message("shout",HIR"【家有喜事】"HIM"恭喜"HIR+query("name", me)+"("+query("id", me)+")"
                        HIM"給"HIR+query("name", target)+"("+query("id", target)+")"HIM"添了一個千金小寶貝。\n"NOR,
                        users());                
        }
        
        set("per", (query("per", me)+query("per", target))/2, baby);
        set("kar", (query("kar", me)+query("kar", target))/2, baby);
        set("int", (query("int", me)+query("int", target))/2, baby);
        set("str", (query("str", me)+query("str", target))/2, baby);
        set("con", (query("con", me)+query("con", target))/2, baby);
        set("dex", (query("dex", me)+query("dex", target))/2, baby);
        set("parents/father",query("id",  target), baby);
        set("parents/mother",query("id",  me), baby);
        baby->save();
        
        set("couple/child_id",query("id",  baby), me);
        set("couple/child_name",query("name",  baby), me);
        set("couple/child_id",query("id",  baby), target);
        set("couple/child_name",query("name",  baby), target);
        me->save();
        target->save();
        
        if (! baby->move(environment(me)))
                baby->move(environment(environment(me)));
                
        return 1;
}
