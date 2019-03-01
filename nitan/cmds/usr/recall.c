// recall.c
// created by lonely@nitan2

#include <ansi.h>
inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
        string file;
        string str;
        object ob;
 
        if (! environment(me)) 
                return 0; 

        if (! arg || (arg != "back" && 
            arg != "home" && sscanf(arg, "%s %s", arg, str) != 2))
                return help(me);
                               
        if (me->is_busy())
                return notify_fail("你正忙著呢。\n");

        if (me->is_fighting())
                return notify_fail("你現在正在戰鬥！\n"); 

        if (me->is_ghost()) 
                return notify_fail("等你還了陽再說吧。\n"); 
                
        if (me->is_in_prison())   
                return notify_fail("你正在做牢呢。\n");

        if( query("doing", me) )
                return notify_fail("你還想幹什麼？！\n");
                
        if( query("no_magic", environment(me)) )
                return notify_fail("你發現這裡有點古怪！\n");                
        
        if (arg == "back")
        {
                if( query_temp("warquest/party", me) )
                        return notify_fail("你還想在戰爭中使用？！\n");

                if (present("biao huo", me))
                        return notify_fail("你身上帶著鏢銀，不能施展！\n");

                if( sscanf(base_name(environment(me)), "/d/register/%*s") )
                        return notify_fail("你還沒有出生呢，不能施展！\n");

                if( sscanf(base_name(environment(me)), "/d/newbie/%*s") )
                        return notify_fail("你在古村中，不能施展！\n");
                
                file = "/d/city/kedian";
                
                if (base_name(environment(me)) == file)
                        return notify_fail("你已經在揚州客店了。\n");
                        
                if (! get_object(file))
                        return notify_fail("你感覺到似乎有什麼不對勁！\n");

                message("vision", me->name() + "舉起右手在面前極速畫了一個圓，竟劃破了面前的"
                        "空間，\n只見圓內的空間真空將" + me->name() + "給吸了進去。\n",
                        environment(me), ({me}));
                
                tell_object(me, "你從客店的某個角落空間裂縫中鑽出。\n");

                me->move(file);
                message("vision", me->name() + "從客店的某個角落空間裂縫中鑽出。\n",
                        environment(me), ({me}));

                MYGIFT_D->check_mygift(me, "newbie_mygift/recall");
                return 1;
        }
 
        if (arg == "back" || arg == "home")
        {
                if( query_temp("warquest/party", me) )
                        return notify_fail("你還想在戰爭中使用？！\n");

                if (present("biao huo", me))
                        return notify_fail("你身上帶著鏢銀，不能施展！\n");

                if( sscanf(base_name(environment(me)), "/d/newbie/%*s") )
                        return notify_fail("你在古村中，不能施展！\n");
                
                if( arg == "back" )
                        file = "/d/city/kedian";
                else
                        file = query("private_room/position", me);
                
                if( !file ) return notify_fail("你還沒有住房呢！\n");
                
                if (base_name(environment(me)) == file)
                        return notify_fail("你已經在這裡了。\n");
                        
                if (! get_object(file))
                        return notify_fail("你感覺到似乎有什麼不對勁！\n");

                message("vision", me->name() + "舉起右手在面前極速畫了一個圓，竟劃破了面前的"
                        "空間，\n只見圓內的空間真空將" + me->name() + "給吸了進去。\n",
                        environment(me), ({me}));
                
                tell_object(me, "你從某個角落空間裂縫中鑽出。\n");

                me->move(file);
                message("vision", me->name() + "從某個角落空間裂縫中鑽出。\n",
                        environment(me), ({me}));

                MYGIFT_D->check_mygift(me, "newbie_mygift/recall");
                return 1;
        }
                                       
        if( !stringp(file=query("can_whistle/"+str, me)) )
                return notify_fail("你並沒有這個魔幻獸。\n");

        if (file_size(file + ".c") < 0)
                return notify_fail("你並沒有這個魔幻獸。\n");
                                
        if( arg == "reborn" && query("warcraft/status", me) == "died" )
        {
                if (me->query_skill("huisheng-jue", 1) < 100)
                        return notify_fail("你的回生決功力不夠，無法讓魔幻獸重生。\n"); 

                if( query("neili", me)<query("max_neili", me)*9/10 )
                        return notify_fail("你現在內力並不充沛，怎敢貿然運用？\n");

                if( query("jingli", me)<query("max_jingli", me)*9/10 )
                        return notify_fail("你現在精力不濟，怎敢貿然運用？\n");

                if (me->query_skill("force") < 200)
                        return notify_fail("你的內功根基不夠紮實，不能貿然運用。\n");

                if( query("max_neili", me)<3000 )
                        return notify_fail("你嘗試運了一下內力，無法順"
                                   "利運足一個周天，難以施展你的能力。\n");

                if( query("max_jingli", me)<1000 )
                        return notify_fail("你試圖凝神運用精力，但是感覺尚有欠缺。\n");                                
                
                if( query("experience", me)<query("learned_experience", me)+1000 )
                        return notify_fail("你現在積累的實戰體會還太少，無法貿然運用。\n");

                message_sort(HIR "$N集中精神，手指大地，同時運轉丹田內力，經"
                        "由奇經八脈源源由體內流出，注入大地。\n" NOR, me); 

                me->start_busy(1);
        
                addn("max_neili", -500, me);
                set("neili",query("max_neili",  me), me);
                addn("max_jingli", -300, me);
                set("jingli",query("max_jingli",  me), me);
                addn("learned_experience", 1000, me);
                set("warcraft/status", "living", me);
                tell_object(me, HIW "你凝神片刻，覺得魔幻獸"
                        HIW "似乎復活過來，就在不遠處，不禁微微一笑。\n" NOR);                                                                             
                
        } 
        else return help(me);
        return 1;
}

int help(object me)
{
 write(@HELP
指令格式 : recall back | home
回到揚州客店的指令為 < recall back >。
回到住房的指令為 < recall home >。
HELP
    );
    return 1;
}

