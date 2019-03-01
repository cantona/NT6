inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
這裡是一條上山的小路。山路周圍很是僻靜，連個人影也沒有。
周圍常有山賊土匪出沒，行路需得小心謹慎。
LONG );
        set("outdoors", "baituo");
        set("exits", ([
                "northup"   : __DIR__"xiaolu3",
                "southdown" : __DIR__"xiaolu1",
        ]));
        set("objects", ([
                __DIR__"npc/man" : 1,
        ]));

        set("coor/x", -49960);
        set("coor/y", 20010);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}