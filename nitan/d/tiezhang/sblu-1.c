// Room: /u/zqb/tiezhang/sblu-1.c

inherit ROOM;

void create()
{
        set("short", "石板路");
        set("long", @LONG
你走在一條石板舖成的小路上，兩旁是高大的垂柳，雖在驕陽似火的夏
日，依舊涼爽怡人。因為小指峰風光秀美，遊人較多，因此這裡的路也修砌
的很好。
LONG        );
        set("exits", ([ /* sizeof() == 2 */
  "westup" : __DIR__"pubu",
  "eastdown" : __DIR__"shanlu-5",
]));
        set("no_clean_up", 0);
        set("outdoors", "tiezhang");

        setup();
        replace_program(ROOM);
}