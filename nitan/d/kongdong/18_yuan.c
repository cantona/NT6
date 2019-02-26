//1997-3-10 by qyz

inherit ROOM;
#include <room.h>

string *things = ({
        CLONE_DIR + "book/quanfa",
        CLONE_DIR + "book/jianshu",
                });



void create()
{
	set("short","十八院");
	set("long",@LONG
這裏環境清幽，四處打掃得乾乾淨淨，是崆峒山弟子以及進香客歇息的地方
，由於近兩年來崆峒山香火不斷，進香的人越來越多，於是準備再建一處廂房供
住宿之用，這裏向西走就是崆峒山的主殿－－“軒轅宮”了。
角落裏是一個櫃子，似乎放了什麼東西。
LONG);
    set("need_clean", "崆峒派");
	set("exits",
	([
             "west" : __DIR__"xuanyuan_gong",
             "up" : __DIR__"baguatai",
          	]));
    set("sleep_room","崆峒派");
	set("objects", ([
		__DIR__"npc/kdizi4" : 1,
		]) );
    if( random(10) > 5 )
        set("search_things", ([
                "櫃子" : things[random(sizeof(things))],
                    ]));

    setup();
    //place_program(ROOM);
}
