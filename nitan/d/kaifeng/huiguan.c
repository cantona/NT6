inherit ROOM;

void create()
{
        set("short", "山陝甘會館");
        set("long", @LONG
山陝甘會館是山西，陝西，甘肅的富商巨賈建造的，是旅汴同鄉
聚會的場所，就是給這三地的人聚會的。當然也有在此來商談生意的。
裏面就是關帝廟。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"eroad2",
                  "east" : __DIR__"paifang",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5020);
	set("coor/y", 2240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}