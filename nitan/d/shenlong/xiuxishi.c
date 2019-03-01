// Room: xiuxishi.c

inherit ROOM;

void init();

void create()
{
        set("short", "休息室");
        set("long", @LONG
這是間整潔的小房，房裡別無他物，只有中間放著一張收拾得幹
幹凈凈的床，這是神龍島弟子的休息場所。
LONG );
	set("exits", ([
	    "south"  : __DIR__"zoulang",
	]));

        set("sleep_room", 1);
        set("no_fight", 1);

        setup();
	replace_program(ROOM);
}
