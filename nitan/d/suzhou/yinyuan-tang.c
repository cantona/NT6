// Room: /d/suzhou/yinyuan-tang.c    拜堂之處
// by llm 99/06

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "姻緣堂");
        set("long", @LONG
你簡直走進了一片紅色的世界，高低左右地垂着各式各樣的紅綢
綾緞彩紙貼花，細細看去，每一處竟都繡扎着鴛鴦鳳凰，透出一股股
濃郁的喜慶氣氛，當中一塊橫匾：          千裏姻緣一線牽
LONG );
        set("exits", ([
                "west" : "/d/suzhou/hongniang-zhuang",
        ]) );
        set("objects", ([
        ]) );
        set("no_fight",1);
        set("no_steal",1);
        set("no_beg",1);
        set("no_sleep_room",1);

        set("coor/x", 240);
        set("coor/y", -200);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
