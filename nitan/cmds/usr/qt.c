// quest.c

#include <ansi.h>
 
int main(object me, string arg)
{
        int status=query("to_pvp/status", me);
        string str,master=query("family/master_name", me);

        if( !query("to_pvp", me) )
                return 0;

        if( !status )
        {
                if( query("to_pvp/time", me)<time() )
                {
                        delete("to_pvp", me);
                        return notify_fail(master+"長嘆道：“難道本派中就沒有人能殺此賊？悲呼！！！”");
                }
                if( arg == "cancel" )
                {
                        delete("to_pvp", me);
                        return notify_fail(master+"怒道：“哼，象你如此膽小之人，怎能成大器！！！”\n");
                }
                if( arg == "ok" )
                {
                        set("to_pvp/status", 1, me);
                        set("to_pvp/time", time()+600, me);
                        return notify_fail("你怒道：“豈有此理，如此惡賊，我豈能容他在此世上，待我去殺了此賊，替本派除害”。\n");
                }
                str =  sprintf("你將要被派去殺的本門仇敵%s(%s)。\n", 
                        query("to_pvp/name", me),query("to_pvp/id", me));
                str += sprintf("你還有%s秒來接受這個任務。\n",
                        CHINESE_D->chinese_number(query("to_pvp/time", me)-time()));
                str += "如果你要接受任務請輸入“qt ok”\n";
                write(str);
                return 1;
        }
        else
        {
                if( query("to_pvp/time", me)<time() )
                {
                        delete("to_pvp", me);
                        return notify_fail(master+"：“殺此小賊，居然用了這麼久的時間還沒殺死，我看也不再找你了，你給我好好的學藝吧，我另外找人，哼！！！”");
                }
                str =  sprintf("你要殺的本門仇敵是%s(%s)。\n", 
                        query("to_pvp/name", me),query("to_pvp/id", me));
                str += sprintf("你需要在%s前來完成這個任務。\n",
                        CHINESE_D->chinese_date(query("to_pvp/time", me)));
                write(str);
                return 1;
        }
        return 0;
}
