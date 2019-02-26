inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
這裏是一條上山的小路，小路向西分出一條岔道。山路周圍很是
寂靜，北邊是山賊的老窩，常常有土匪出沒於此。
LONG );
        set("outdoors", "baituo");
        set("exits", ([
                "north"     : __DIR__"dongkou",
                "southwest" : __DIR__"xiaolu3",
        ]));
        set("objects", ([
                __DIR__"npc/shanzei2" : 1,
        ]));
        set("coor/x", -49950);
        set("coor/y", 20030);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}