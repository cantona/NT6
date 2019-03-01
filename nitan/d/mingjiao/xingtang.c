// Room: /d/mingjiao/xingtang.c

#include <ansi.h>
#include <login.h>

inherit ROOM;

void create()
{
        set("short", "刑堂");
        set("long", @LONG
整個刑堂門戶緊閉，密不透風。即便是在白晝，也猶如黑夜一般，
每隔幾步的牆上，點燃著幾枝牛油巨燭。中間是一個大火盆，烈燄騰
騰。下方擺著一排排烙鐵、水牛皮鞭、穿孔竹板及狼牙棒等刑具。四
周站滿了手持兵刃的執法教眾。他們正用冷酷的眼神打量著你，令你
不禁渾身哆嗦起來。    冷謙執掌明教刑堂。
LONG );
        set("no_fight", 0);
        set("exits", ([
                "west" : __DIR__"square",
        ]));
        set("objects",([
                __DIR__"npc/lengqian" : 1
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
