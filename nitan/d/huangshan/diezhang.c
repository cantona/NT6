// Room: /d/huangshan/diezhang.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "疊嶂峯");
        set("long", @LONG
山峯實在是多，相傳黃山三千六百峯，從疊嶂峯來看，只怕尤有過
之，僅次一處山峯便難以計算，羣峯疊嶂，都是一根而出，看似羣峯，
也難説清究竟該有多少，過去是極難行走，好在現在以有石階，鐵索，
遊人便可以輕鬆到達後山的鬆谷庵。
LONG
        );
        set("exits", ([ 
                "southeast" : __DIR__"qingliang",
                "north"     : __DIR__"songgu",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huangshan");
        set("coor/x", -605);
        set("coor/y", -980);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}