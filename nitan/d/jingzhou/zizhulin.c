inherit ROOM;

void create()
{
        set("short", "紫竹林");
        set("long", @LONG
你來到一片翠綠的紫竹林中，四周全被紫竹所包圍，你仿似迷失
了方向。耳旁不時傳來一陣陣悅耳的鳥叫聲，不禁讓人感到心曠神怡。
LONG );
        set("outdoors", "jingzhou");

        set("exits", ([
                "northup" : __DIR__"shijie",
                "south" : __DIR__"zizhulin1",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("coor/x", -7090);
	set("coor/y", -2090);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}