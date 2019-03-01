// laojundian.c 老君殿
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "老君殿");
        set("long", @LONG
這裡是供奉太上老君的大殿。殿的正中塑著老君的塑像，老君騎
在青牛上，正臨雲而去。兩旁塑著兩個童子，都栩栩如生。殿中的地
都是以青磚一塊塊的舖成，打掃得一塵不染。
LONG
        );
        set("exits", ([
                "east" : __DIR__"houtang1",
                "south" : __DIR__"tongtiandian",
                "north" : __DIR__"yuanshidian",
                "west" : __DIR__"datang3",
        ]));
        set("objects", ([
                CLASS_D("quanzhen")+"/qiu" : 1,
        ]));
        set("coor/x", -2770);
        set("coor/y", 110);
        set("coor/z", 170);
        setup();
}

int valid_leave(object me, string dir)
{
        mapping fam;

        if (dir == "east" )
        {
                if( !(fam=query("family", me)) || fam["family_name"] != "全真教"){
                        if(present("qiu chuji", environment(me)) && living(present("qiu chuji", environment(me))))
                        {
                                return notify_fail(
"丘處機喝道：後面是本教重地，這位" + RANK_D->query_respect(me) + "請止步。\n");
                        }
                        else
                                return ::valid_leave(me, dir);
                }
                else
                        return ::valid_leave(me, dir);
        }
        else
                return ::valid_leave(me, dir);

}