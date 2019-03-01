inherit ROOM;

void create()
{
        set("short", "上山小路");
        set("long", @LONG
這是一條上山的小路，腳下是青石砌成的台階，濕漉漉的長滿了
青苔，四周全是茂密的竹林。前面似乎就快到小山頂上了。
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "southup" : __DIR__"caoping",
                "northdown" : __DIR__"shanlu2",
        ]));
        set("objects", ([
                __DIR__"npc/qiaofu": 2,
        ]));

        setup();
        replace_program(ROOM);
}