// Room: /d/huashan/xiaowu.c

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "林間小屋");
        set("long", @LONG
這裏就是華山劍宗的的根本之地。二十五年來，劍宗弟子卧薪嘗
膽，只是為了奪回華山門派掌門，為此，付出了極大犧牲。    屋裏
陳設極為簡陋，只是西面開了一個小門，上面掛着一道竹簾。
LONG );
        set("exits", ([ /* sizeof() == 4 */
             "west": __DIR__"pingdi",
             "east": __DIR__"neishi",
        ]));
        set("objects", ([
             CLASS_D("huashan") + "/feng-buping": 1,
        ]));
        set("valid_startroom", 1);

        setup();
        "/clone/board/jianzong_b"->foo();
}

/*
int valid_leave(object me, string dir)
{
        object guarder;

        if (! objectp(guarder = present("feng buping", this_object())))
                return 1;

        if (dir == "east")
                return guarder->permit_pass(me, dir);

        return 1;
}
*/