// Room: /d/huanggong/dadao.c

inherit ROOM;

void create()
{
        set("short", "大道");
        set("long", @LONG
這是通往宮中的大道. 北邊遠遠能望見先農壇. 西邊有一片獵場, 
是皇家的上林囿. 每年皇上都會去狩獵. 平時就比較冷清, 倒是那些動
物們, 樂得個安閒.
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([ /* sizeof() == 2 */
                 "west" : __DIR__"lie1",
                 "east" : __DIR__"humen",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2860);
	set("coor/y", 7721);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}