// houtang3.c 後堂三進
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "後堂三進");
        set("long", @LONG
這裡是全真教弟子演練武功的地方。全真教弟子眾多，所以每逢
每月的十五這天，就召集所有弟子來這裡切磋武功，一方面檢驗弟子
們的武功長進，另一方面選拔人才擔任教中的重要職務。現在還不到
演武的日子，堂中空無一人。
LONG
        );
//        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"jingxiushi",
                "west" : __DIR__"houtang2",
                "northeast" : __DIR__"xiaohuayuan1",
        ]));
        set("objects", ([
                CLASS_D("quanzhen")+"/wangzhitan" : 1,
        ]));

        set("coor/x", -2740);
        set("coor/y", 110);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}