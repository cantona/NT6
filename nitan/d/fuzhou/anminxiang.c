// Room: /d/fuzhou/anminxiang.c
// Last Modifyed by Evil on Sep. 10 2002

inherit ROOM;

void create()
{
        set("short", "安民巷");
        set("long", @LONG
因唐代農民起義軍黃巢入閩時，到此巷即告示安民，故名。舊有錫
類坊，以宋劉藻以孝聞，後太宰余深居此改曰：“元台育德”。歷史上
巷內人家多為社會賢達。元行省都事賈訥居之。巷西側民居舊宅仍保留
勻稱格局和古樸風韻。
LONG );
        set("exits", ([
                "west" : __DIR__"nanhoujie5",
        ]));
        set("objects", ([
                "/d/village/npc/boy" : random(2),
                "/d/village/npc/girl" : random(2),
        ]));
        set("outdoors", "fuzhou");
        set("no_clean_up", 0);
	set("coor/x", -80);
	set("coor/y", -6230);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}