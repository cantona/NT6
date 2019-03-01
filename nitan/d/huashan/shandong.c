// shandong.c

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "山洞");
        set("long", @LONG
這裡是一個不大的山洞，奔騰的瀑布成了它的門簾，陽光輕易就
可以的透過水簾射進來，因此這裡白天並不陰暗。
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "out"  : __DIR__"shanhongpb",
                // "enter": __DIR__"s",
        ]));

        setup();
        (CLASS_D("ultra") + "/dugu")->come_here();
}

string long()
{
        object ob;
        string msg;

        msg = query("long");
        if (! objectp(ob = present("dugu qiubai", this_object())))
                return sort_string(msg, 64, 4);

        if (! ob->is_fighting())
                msg += "只見一人坐在地上，手中抱著一柄竹劍，翻了復"
                       "去的看，也不知道在研究什麼。\n";
        else
                msg += "只見一人正在與" +
                       (ob->is_fighting(this_player()) ? "你" : "人") +
                       "激戰，竹劍施展開來竟然有諾大的威力，真是匪夷所思。\n";

        return sort_string(msg, 64, 4);
}

int valid_leave(object me, string dir)
{

        if (dir == "enter")
        {
                write(HIG "\n你進入山洞，只覺四周漆黑一片，你一直不停地往前走… \n" NOR);
                write(HIG "不久，穿過了山洞，只見前方卻是懸崖峭壁。\n\n");
        }
        
        return 1;
}