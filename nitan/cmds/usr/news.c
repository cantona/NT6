// news cmds
// by Doing
#include <ansi.h>
 
inherit F_CLEAN_UP;

#ifndef NEWS_D
#define NEWS_D          "/adm/daemons/newsd"
#endif

int main(object me, string arg)
{
        if( !wizardp(me) && time()-query_temp("last_news", me)<3 )
        {
                write("系統氣喘噓地歎道：慢慢來 ....\n");  
                return 1;
        }

        set_temp("last_news", time(), me);

        MYGIFT_D->check_mygift(me, "newbie_mygift/news");   

        if (! arg || arg == "" || arg == "all")
        {
                NEWS_D->show_news(me, (arg != "all") ? 1 : 0);
                write(HIC "閲讀新聞指令格式：" HIY "news " NOR "<" HIY "new" NOR "|" HIY "next" NOR "|" HIY "新聞編號" NOR ">\n"
                      HIC "搜索新聞指令格式：" HIG "news search " NOR "<" HIG "title" NOR "|" HIG "author" NOR "|" HIG "document" NOR "> <" HIM "關鍵字" NOR "|" HIM "關鍵詞" NOR ">\n");
                return 1;
        }

        if (sscanf(arg, "discard %s", arg) || sscanf(arg, "del %s", arg))
        {
                NEWS_D->do_discard(me, arg);
                return 1;
        }

        if (sscanf(arg, "post %s", arg) || sscanf(arg, "add %s", arg))
        {
                NEWS_D->do_post(me, arg);
                return 1;
        }

        if (sscanf(arg, "search %s", arg) || sscanf(arg, "find %s", arg))
        {
                NEWS_D->do_search(me, arg);
                write(HIC "閲讀新聞指令格式：" HIY "news " NOR "<" HIY "new" NOR "|" HIY "next" NOR "|" HIY "新聞編號" NOR ">\n"
                      HIC "搜索新聞指令格式：" HIG "news search " NOR "<" HIG "title" NOR "|" HIG "author" NOR "|" HIG "document" NOR "> <" HIM "關鍵字" NOR "|" HIM "關鍵詞" NOR ">\n");
                return 1;
        }

        NEWS_D->do_read(me, arg);
        write(HIC "閲讀新聞指令格式：" HIY "news " NOR "<" HIY "new" NOR "|" HIY "next" NOR "|" HIY "新聞編號" NOR ">\n"
              HIC "搜索新聞指令格式：" HIG "news search " NOR "<" HIG "title" NOR "|" HIG "author" NOR "|" HIG "document" NOR "> <" HIM "關鍵字" NOR "|" HIM "關鍵詞" NOR ">\n");
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : news [next] | [<新聞編號>] | new | all
           news search <title|author|document> <關鍵字|關鍵詞>

這條指令讓你你可以閲讀遊戲中的新聞。所有的更新和消息都是通過
新聞發佈的。

使用 new 參數可以讓你閲讀還沒有讀過的新聞。
使用 all 參數可以讓你查看系統目前所有的新聞。
使用 search 參數可以讓你查找系統目前符合搜索條件的新聞。
     search <title|author|document> <關鍵字|關鍵詞>
     根據標題、作者、內容搜索包含指定關鍵字或者關鍵詞的新聞。
     比如：news search title 轉世系統 ----將返回所有標題中包
           含“轉世系統”的新聞。


總站的巫師可以通過news post <標題>來發布新聞。news discard來
刪除新聞。
HELP );
    return 1;
}
