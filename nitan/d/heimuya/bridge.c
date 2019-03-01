//bridge.c

inherit ROOM;

void create()
{
        set("short", "小橋");
        set("long", @LONG
這是一座小竹橋，黑木崖頂上的冰雪融化形成一條清澈的小溪，
從橋下緩緩流過。不時有頑皮的小魚躍出水面，在陽光下劃出一條銀
白色的弧線。
LONG );
        set("outdoors", "baituo");
        set("exits", ([
            "northwest" : "/d/baituo/guangchang",
            "east" : "/d/baituo/xijie",
        ]));
        set("objects",([
                __DIR__"npc/cungu" : 1,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}