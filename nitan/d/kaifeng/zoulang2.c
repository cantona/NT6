inherit ROOM;

void create()
{
        set("short", "明廊");
        set("long", @LONG
硫璃瓦舖的一條明廊，地面的地板離開地面三尺，擦洗得很幹凈。
每隔一段的廊檻上都鏤刻了精致的佛像。明廊至此中斷，東面過去就
是菜園，南邊的空地上也種了幾棵菜。北面是個小柴房。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"zoulang",
                  "east" : __DIR__"caidi",
                  "south" : __DIR__"caidi2",
                  "north" : __DIR__"caifang",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5010);
	set("coor/y", 2210);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}