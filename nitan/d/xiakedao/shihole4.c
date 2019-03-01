// /d/xiakedao/shihole4.c 俠客島 石洞4

inherit ROOM;

int do_learn(string arg);
void create()
{
        set("short", "石洞");
        set("long", @LONG
此洞氣氛卻又大不相同，卻似來到火焰山一般。只見一色紅布帷
幔，八支粗大的紅燭分列四角。一旁站立的是虯髯大漢，各佩彎刀，
刀柄上紅櫻低垂。正中大字是雄健的魏碑體：「烈焰豪情」。
LONG );
        set("exits", ([
                "out"   : __DIR__"shihole3",
                "enter" : __DIR__"shihole5",
                "north" : __DIR__"shiroom13",
                "south" : __DIR__"shiroom14",
                "east"  : __DIR__"shiroom15",
                "west"  : __DIR__"shiroom16",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3090);
        set("coor/y", -25400);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}