inherit ROOM;

void create()
{
        set("short", "官道");
        set("long", @LONG
此處往東不遠是開封，往西可到中州，不少遊人順著這條路遊玩。
LONG);
        set("exits", ([
                "east": "/d/kaifeng/ximen",
                "west" : __DIR__"eroad2",
        ]));
        set("outdoors", "zhongzhou");

        set("coor/x", -8970);
	set("coor/y", -1010);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}