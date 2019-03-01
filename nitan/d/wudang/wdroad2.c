inherit ROOM;

void create()
{
        set("short", "青石大道");
        set("long", @LONG
你走在一條青石大道上，北邊隱約可見到揚州城的南城牆。
此處往東南望去，可以看到一個市鎮。
LONG);
        set("outdoors", "sanbuguan");
        set("exits", ([
                "south" : __DIR__"wdroad3",
                "north" : __DIR__"wdroad1",
                "west"  : "/d/hudie/shanbi",
                "southeast" : "/d/yixing/yixing",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
