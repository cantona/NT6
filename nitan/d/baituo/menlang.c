inherit ROOM;

void create()
{
        set("short", "門廊");
        set("long", @LONG
這是個門廊，門廊的飛檐上掛着一串串的小銅鈴，在清風中發出
清脆動聽的鈴聲。
LONG );
        set("exits", ([
                "north" : __DIR__"huayuan",
                "south" : __DIR__"liangong",
        ]));
        set("objects", ([
                __DIR__"npc/guanjia" : 1,
        ]));
        set("outdoors", "baituo");
        set("coor/x", -49980);
        set("coor/y", 20040);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}