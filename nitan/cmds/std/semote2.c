// semote.c

#include <ansi.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

int filter_emote(string emote, int d);
int sort_emote(string e1, string e2);

int main(object me, string arg)
{
        string *e;
        string str;
        int i;
        int d;

        d = 0;
        e = EMOTE_D->query_all_emote();
        if (arg == "-r" || arg && sscanf(arg, "-r %d", d))
        {
                str = HIM "按照時間順序顯示" + LOCAL_MUD_NAME();
                if (d)
                {
                        str += "最近" + chinese_number(d) + "天增加的表情動詞";
                        d *= 86400;
                        e = filter_array(e, (: filter_emote :), d);
                } else
                {
                        str += "所有的表情動詞";
                        e = sort_array(e, (: sort_emote :));
                }
                str += "\n" NOR;
        } else
        {
                str = HIW + LOCAL_MUD_NAME() + "表情動作總匯\n" NOR;
                e = sort_array(EMOTE_D->query_all_emote(), 1);
        }
        str += "─────────────────────────────────────\n";
        for(i=0; i<sizeof(e); i++)
                str += sprintf("%-15s%s", e[i], (i%5==4)?"\n": "");
        me->start_more(str);
        write("\n");
        return 1;
}

int filter_emote(string emote, int d)
{
        int t;

        t = (int)(EMOTE_D->query_emote(emote)["time"]);
        return (time() - t > d) ? 0 : 1;
}

int sort_emote(string e1, string e2)
{
        int t1, t2;

        t1 = (int)(EMOTE_D->query_emote(e1)["time"]);
        t2 = (int)(EMOTE_D->query_emote(e2)["time"]);
        if (t1 == t2)
        {
                if (e1 > e2) return 1;
                return -1;
        }
        return t2 - t1;
}

int help(object me)
{
  write(@HELP
指令格式 : semote [-r [n]]

這個指令可以列出目前所能使用的emote。如果玩家使用了
選項 -r 則可以按照時間順序顯示所有的emote，如果選項
後面添加了參數，則將只顯示最近幾天編寫的emote。

比如semote -r 1將顯示最近一天新編寫或修改的emote。
HELP
    );
    return 1;
}