inherit ROOM;

void create()
{
        set("short", "小土屋");
        set("long", @LONG
這是一間小土屋，看樣子是一户農家的房子。屋裏簡單地擺着些
傢俱，牆角里堆着些農具。炕上坐着一個老婆婆和一個小孩，見有人
衝進來，都神色緊張地望着你。
LONG );
        set("exits", ([
                "north" : __DIR__"wdroad6",
        ]));
        set("objects", ([
                "/d/village/npc/oldwoman" : 1,
                "/d/village/npc/kid" : 1,
        ]));
        set("coor/x", -300);
        set("coor/y", -160);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}

