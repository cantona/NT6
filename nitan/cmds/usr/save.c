// save.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object link_ob;
        int lasttime;

        seteuid(getuid());

        if( !objectp(link_ob=query_temp("link_ob", me)) )
                return notify_fail("你不是經由正常連線進入，不能儲存。\n");

        lasttime=time()-query("last_save", me);
        if( lasttime >= 0 && lasttime < 30)
                return notify_fail("為了降低系統負載，請不要頻繁儲存進度。\n");

        if( query("valid_startroom", environment(me))){
                set("startroom", base_name(environment(me)), me);
                write("當你下次連線進來時，會從這裏開始。\n");
        }

        if( (int)link_ob->save() && (int)me->save() ) {
                write("檔案儲存完畢。\n");
                set("last_save", time(), me);
                return 1;
        } else {
                write("儲存失敗。\n");
                return 0;
        }
}

int help(object me)
{
        write(@HELP
指令格式：save

把你辛苦奮鬥的結果存起來。
HELP
        );
        return 1;
}