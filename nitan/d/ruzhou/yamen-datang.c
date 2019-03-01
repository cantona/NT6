// Room: /d/ruzhou/yamen-datang.c
// llm 1999/07/04

inherit ROOM;

void create()
{
        set("short", "知府大堂");
        set("long", @LONG
正中一面明鏡高懸的大匾，是各地的衙門必備的家當。大堂的地上擦得逞亮卻
隱約能看到一點點的血痕，看來是大堂用刑時留下的痕跡。兩邊各各一些肅靜、回
避的牌子，竟有些不威自怒的感覺。
LONG
        );
        set("exits", ([
           "south" : __DIR__"yamen-damen",
        ]));
        set("objects", ([
                __DIR__"npc/jiang-yaoting":1,
      __DIR__"npc/yayi":4,
        ]));
        set("no_fight", 1);

	set("coor/x", -6770);
	set("coor/y", 1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
