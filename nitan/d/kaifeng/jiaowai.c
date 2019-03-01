inherit ROOM;

void create ()
{
          set ("short","郊外");
        set("long", @LONG
此處是開封北郊，由于離開封很近，治安相對穩定，由此去嵩山
進香的客人絡繹不絕，一幅太平景象。
LONG );
          set("outdoors", "kaifeng");
          set("exits", ([
                  "south" : __DIR__"xuandemen",
		"westup" : __DIR__"shanlu1",
        ]));
	set("coor/x", -5060);
	set("coor/y", 2270);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}