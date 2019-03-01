// Room: /city/biaojuhc.c

inherit ROOM;

void create()
{
        set("short", "貨倉");
        set("long", @LONG
福威鏢局武功並無出色之處，但福字當頭，和黑白兩道均極交好，
從未失鏢。顧主的貨物在這裡堆積如山。鏢局的伙計們正在手忙腳亂的
往鏢車上裝載貨物。雖然每個伙計都已盡力而為，但還是忙不過來。
LONG
        );
        set("exits", ([
                "west"  : __DIR__"biaojudy",
                "north" : __DIR__"biaojuzf",
        ]));
        set("objects", ([
                __DIR__"npc/qian" : 1,
                __DIR__"npc/huo" : 1,
        ]));
	set("coor/x", -91);
	set("coor/y", -6171);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}