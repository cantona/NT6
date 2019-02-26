// Room: /heizhao/shanlu10.c
// Date: Dec. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "山間平地");
        set("long", @LONG
這裏有個極大的噴泉，高達二丈有餘，奔雪濺玉，一條巨大的
水柱從石孔中直噴上來，飛入半空，這噴泉是下面溪水與瀑布的源
頭。側面山壁陡立，山上林蔭如蓋，似有一樵夫伐木其間。山邊一
條手臂粗細的長藤(teng)，沿峯而上。仰頭上望，見山峯的上半截
隱入雲霧之中，不知峯頂究有多高。
LONG );
        set("outdoors", "taoyuan");
        set("no_clean_up", 0);
        set("resource/water", 1);
        set("objects", ([
                CLASS_D("dali")+"/yideng/qiao" : 1,
        ]));
        set("exits", ([
                "down"   : __DIR__"pububian",
        ]));
        set("coor/x", -5020);
        set("coor/y", -1260);
        set("coor/z", 30);
        setup();
}

int valid_leave (object who, string dir)
{
        if(dir == "down")
        {
                message_vision(HIY"$N順水流衝舟而下。\n"NOR, who);
        }
        return ::valid_leave(who, dir);
}

void init()
{
        add_action("do_climb","climb");
}

int do_climb(string arg)
{
        object me = this_player();
        int n;
        n = me->query_str();
        if ( !arg || arg != "teng")
        {
                write("你要爬什麼呀? \n");
                return 1;
        }
        message_vision("$N深吸了一口氣，慢慢沿着長藤的向上爬。\n", me);
        if(n > 35)
        {
                message_vision("$N爬了半天，終於爬了上來，$N真是高興。\n", me);
                this_player()->move(__DIR__"shanding");
        }
        else
        {
                message_vision("$N爬了一會，太累了，不小心滑了下來。\n", me);
                me->receive_damage("qi",15);
                me->receive_wound("qi",10);
        }
        return 1;
}