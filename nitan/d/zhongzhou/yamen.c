inherit ROOM;

void create()
{
        set("short", "中州衙門");
        set("long", @LONG
這就是中州縣衙門，兩旁的肅靜和威武的牌子讓你有點心
驚膽顫。兩邊的侍衞冷冷的看着你，看你要狀告何人。
LONG);
        set("outdoors", "zhongzhou");
        set("exits", ([
                "east" : __DIR__"wendingbei3",
                "west" : __DIR__"zoulang",
                
        ]));

        set("objects", ([
                __DIR__"npc/yayi" : 2,
        ]));

        set("coor/x", -9050);
	set("coor/y", -970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}