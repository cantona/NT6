// caotangsi.c
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "草堂寺");
        set("long", @LONG
這是一座位於終南山北麓的小寺。寺院中的一口古井，名為煙霧
井。因為每天清晨都會有一股巨大的煙霧，自井裏裊裊升起，不少遊
客來此，就是為了一觀此奇景。往南上是一條崎嶇的山道。往北是一
條陰森森的小徑。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "southup"     : __DIR__"shanlu13",
//              "north"       : __DIR__"",
        ]));
        set("no_clean_up", 0);

        set("coor/x", -3180);
        set("coor/y", 120);
        set("coor/z", 120);
        setup();
        replace_program(ROOM);
}