// Room: /d/yanping/youlang.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "十裡遊廊");
        set("long", @LONG
十裡遊廊穿行于溪源峽谷中。遊廊風光漪麗，景色秀美。兩岸石壁
對立，怪石嶙峋；峰回路轉，山曲水迂；千屏萬嶂，綿延起伏；樹木森
鬱，古籐纏繞。
LONG );
        set("exits", ([
                "southeast" : __DIR__"beimenling",
                "northwest" : __DIR__"xiagu",
        ]));
        set("outdoors", "yanping");
        set("no_clean_up", 0);
        set("coor/x", 1450);
        set("coor/y", -6150);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}