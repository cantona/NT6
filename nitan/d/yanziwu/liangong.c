//ROOM: /d/yanziwu/linggong.c

inherit ROOM;

void create()
{
        set("short", "神功台");
        set("long",@LONG
這裏就是慕容家練功之所。四壁開着窗口，窗外是太湖景物風致，
時時隨風帶來陣陣江南水鄉的綠色和芳香。
LONG );
        set("exits", ([
                "west": __DIR__"qingyun",
        ]));
        set("objects", ([
                "/clone/npc/mu-ren": 6,
        ]));
        set("coor/x", 960);
        set("coor/y", -1500);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}