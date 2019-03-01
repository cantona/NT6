// /d/quanzhen/puguangsi.c
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "普光寺");
        set("long", @LONG
這是一個位於終南山下的小寺廟，廟門橫額寫着 "普光寺" 三個
大字。由於此廟是上終南山的必經之路，大多數的遊客都會在此落腳
休息，也因此此處香火也頗為鼎盛。廟前的幾株松樹下，立着一塊石
碑(shibei)，幾乎快被周圍的長草給遮掩了。往西走是一條小路.
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "west" : __DIR__"shanlu4",
        ]));

        set("coor/x", -3120);
        set("coor/y", 0);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}