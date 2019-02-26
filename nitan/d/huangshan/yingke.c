// Room: /d/huangshan/yingke.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "迎客鬆");
        set("long", @LONG
從半山寺過來，一過蓬萊三島，遠遠便可以看見一株古鬆伸出“雙
臂”，宛若主迎遠客。鬆高十餘米，樹冠茂密，過了迎客鬆，標誌着人
們已經踏入“萬山拜其下，孤雲卧此中”的文殊院了。
LONG
        );
        set("exits", ([ 
                "southdown" : __DIR__"guanyin",
                "northwest" : __DIR__"yuping",
                "northeast" : __DIR__"wenzhu",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huangshan");
        set("coor/x", -585);
        set("coor/y", -1060);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}