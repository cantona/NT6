// Room: /d/wuxi/chongandadian.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "崇安寺大殿");
        set("long", @LONG
殿內正中供着塑金佛象，僧人誦經之聲不絕於耳。進出的香客顯
得十分地虔誠，四周一圈是五輪大藏佛像。高高的殿堂裏，幃幔飄垂
香火繚繞，顯得特別地神祕。無錫人都説，在這裏許願十分地靈驗。
LONG );
        set("no_beg", 1);
        set("exits", ([
                "out"  : __DIR__"chongansi",
        ]));
        set("objects", ([
                __DIR__"npc/laoheshang": 1,
        ]));
        set("coor/x", 1049);
	set("coor/y", -721);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}