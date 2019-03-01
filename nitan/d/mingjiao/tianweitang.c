//tianweitang.c
inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "天微堂");
        set("long", @LONG
這裡就是明教的天微堂，堂主就是威名遠波的殷野王。他是白眉
鷹王的獨子和教主張無忌的舅舅。堂內陳設鮮麗奢華，顯然甚是興旺，
往來教眾進進出出，看他們各執兵刃，似乎是守總舵的衛士。
LONG );
        set("exits", ([
                "east"      : __DIR__"tianshitang",
                "west"      : __DIR__"ziweitang",
                "southdown" : __DIR__"zhandao2",
                "north"     : __DIR__"square",
        ]));
        set("objects",([
             __DIR__"npc/yinyewang":1,
             __DIR__"npc/yinwufu":1,
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        me = this_player();
        if( (query("family/family_name", me) != "明教") && 
            (dir=="north") &&
            (objectp(present("yin yewang", environment(me)))))
        return notify_fail("殷野王攔住你說：此處乃明教重地，請止步。\n");
        return ::valid_leave(me, dir);
}