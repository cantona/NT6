// Room: /binghuo/lingshetop.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "山頂");
        set("long", @LONG
這裏是靈蛇島山頂。從這裏俯瞰，碧螺般的靈蛇島鑲嵌在湛藍的
大海中，一派生機勃勃。抬頭遠眺，真所謂煙波浩淼、海天一色了，
讓人心襟大開。靈蛇島所在偏僻，四周也不常有什麼船隻經過，除了
時而飛鳥掠空振翼外，只有不盡的海風呼嘯了。
LONG );
        set("outdoors", "lingshe");
        set("no_clean_up", 0);
        set("exits", ([
                "enter"      : __DIR__"lingsheroom",
                "southdown"  : __DIR__"lingsheroad3",
                "eastdown"   : __DIR__"lingsheroad4",
        ]));
        setup();
        replace_program(ROOM);
}
