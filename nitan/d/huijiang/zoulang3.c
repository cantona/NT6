// Room: /d/huijiang/zoulang.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long",@LONG
你走在一條長長的走廊上，兩旁池塘裏的殘荷上停了幾隻呱呱亂叫
的青蛙，陣陣輕風吹來，令人慾醉。北邊是個大廚房，一陣陣的飯菜香
味飄了滿走廊。
LONG );
        set("outdoors", "huijiang");        
        set("exits", ([
                "east"     : __DIR__"wuchang",
                "north"    : __DIR__"chufang",
                "south"    : __DIR__"qiufang",
                "westdown" : __DIR__"zoulang1",
        ]));
        set("objects", ([
                CLASS_D("honghua") + "/first" : 1,
        ]));
        set("coor/x", -50050);
        set("coor/y", 9140);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
