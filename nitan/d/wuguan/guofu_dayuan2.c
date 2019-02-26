inherit ROOM;

void create()
{
        set("short", "郭府大院");
        set("long", @LONG
這是個大院子，東西兩邊都是練武場，不少人在這裏習武
強身，大院裏很是吵鬧，亂烘烘的，你看見不時有扛着東西的
挑着水的人匆匆而過，北面上了台階就是郭府的大廳。
LONG);
        set("no_fight", 1);
        set("exits", ([
                "south" : __DIR__"guofu_dayuan",
                "north" : __DIR__"guofu_dating",
        ]));
        set("objects", ([
           	__DIR__"npc/yelvqi" : 1,
        ]));
        setup();
        replace_program(ROOM);
}