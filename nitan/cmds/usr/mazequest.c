// quest.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        mapping to_kill, to_find;
        mapping killed, finded;
        array tk, tf;
        string msg;
        int i, n;

        ob = FUBEN_D->query_maze_mainobj(me);

        if (! ob) return notify_fail("你當前地點沒有可以顯示的副本任務。\n");

        if( !query("quest/quest_name", ob) )
                return notify_fail("你目前還沒有領取任何副本任務。\n");

        to_kill=query("quest/to_kill", ob);
        killed=query("quest/killed", ob);
        to_find=query("quest/to_find", ob);
        finded=query("quest/finded", ob);

        write("任務名稱: "+query("quest/quest_name", ob)+"\n");
        write("任務描述: "+query("quest/quest_desc", ob)+"\n");
        if (mapp(to_kill) && sizeof(to_kill))
        {
                write("殺敵任務進程: \n");
                msg = "";
                tk = keys(to_kill);
                for (i=0;i<sizeof(tk);i++)
                {
                        if (sizeof(killed) && !undefinedp(killed[tk[i]]))
                                n = killed[tk[i]];
                        else n = 0;
                        msg += tk[i] + ": " + n + "/" + to_kill[tk[i]] + "\n";
                }
                write(msg);
        }
        if (mapp(to_find) && sizeof(to_find))
        {
                write("尋物任務進程: \n");
                msg = "";
                tf = keys(to_find);
                for (i=0;i<sizeof(tf);i++)
                {
                        if (sizeof(finded) && !undefinedp(finded[tf[i]]))
                                n = finded[tf[i]];
                        else n = 0;
                        msg += tf[i] + ": " + n + "/" + to_find[tf[i]] + "\n";
                }
                write(msg);
        }
        if (n = ob->query_remove_time()-time())
                 write("副本將在"+CHINESE_D->chinese_period(n)+"後消失。\n");

        return 1;
}
