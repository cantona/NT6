// whistle.c

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        string file;
        mapping whistle;
        string *ks;
        string msg;
        int i;

        if (! arg)
        {
                whistle=query("can_whistle", me);
                if (! mapp(whistle) || ! sizeof(whistle))
                        return notify_fail("你要召喚什麼？\n");
                ks = keys(whistle);
                msg = "你現在可以召喚的魔幻獸有\n";
                for( i=0; i<sizeof(ks); i++ )
                {
                        if( sscanf(whistle[ks[i]], "/data/beast/%*s") )
                        {
                                delete("can_whistle/" + ks[i], me);
                                continue;
                        }
                        msg += sprintf(HIW "魔幻獸代碼：%-15s    魔幻獸名字：%-20s\n"NOR,ks[i],whistle[ks[i]]->name());
                }
                write(msg);
                return 1;
        }
                        
        if( me->is_busy() || query("doing", me) )
                return notify_fail("你現在正忙呢，等你有空了再說吧。\n");
 
        if (me->is_in_prison())   
                return notify_fail("你正在做牢呢，你想幹什麼？！\n"); 
                               
        if (me->is_ghost())
                return notify_fail("等你還了陽再召喚吧。\n");

        if( !stringp(file=query("can_whistle/"+arg, me)) )
                return notify_fail("你不知道如何召喚這個魔幻獸。\n");

        if (file_size(file + ".c") < 0)
                return notify_fail("你不知道如何召喚這個魔幻獸。\n");
        
        if( query("warcraft/status", me) == "died" )
                return notify_fail("你的魔幻獸已經死亡，請到張天師那裡讓它先復活。\n");

        if( query("no_magic", environment(me)) || query("no_fly", environment(me)) )
                return notify_fail("你發現這裡有點古怪，你的魔幻獸好象不能進來！\n");    
         
        call_other(file, "???");
        ob = find_object(file);

        if (! ob || ! ob->receive_whistle(me))
        {
                message_vision(HIM "$N" HIM "吹了一聲口哨。\n"
                               "然而什麼也沒有發生 :)\n", me);
        }
        
        if (! ob) return 1;
        ob->reset_action();
        ob->set_leader(me);
        
        if (me->is_fighting())                                                                     
                me->start_busy(1 + random(3));

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : whistle <魔幻獸ID>

此指令可讓你把你的魔幻獸呼喚過來，當然你得有一定的精力施展才行。
HELP );
        return 1;
}

