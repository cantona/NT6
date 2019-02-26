//square.c
inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "大院");
        set("long", @LONG
你走進了明教總舵廣場，卻發現這裏人聲鼎沸，五散人羣聚於此，
看來有要事發生了。來往教眾匆匆忙忙。廣場左首是教眾飯堂；右首
就是教眾聞之變色的刑堂。向上走就是光明頂明教總舵了。
LONG );
        set("exits", ([
                "west"    : __DIR__"fangtang",
                "northup" : __DIR__"qiandian",
                "east"    : __DIR__"xingtang",
                "south"   : __DIR__"tianweitang",
        ]));
        set("objects",([
                __DIR__"npc/shuobude":1,
                __DIR__"npc/zhangzhong":1,
                __DIR__"npc/pengyingyu":1,
                __DIR__"npc/zhoudian":1,
                CLASS_D("mingjiao") + "/first" : 1,
        ]));
        set("valid_startroom","1");
        set("outdoors", "mingjiao");
        setup();
        "/clone/board/mingjiao_b"->foo();
}

int valid_leave(object me, string dir)
{
        mapping mypar;
        me = this_player();
        mypar = (mapping)query("family", me);
        if ((!mypar || mypar["family_name"]!="明教") &&
            (dir!="south") &&
            ((objectp(present("peng yinyu", environment(me)))) ||
             (objectp(present("zhang zhong", environment(me)))) ||
             (objectp(present("shuo bude", environment(me)))) ||
             (objectp(present("zhou dian", environment(me))))))
                 return notify_fail("明教五散人攔住你説：此處乃明教"
                                   "重地，請止步。\n");
        return ::valid_leave(me, dir);
}
