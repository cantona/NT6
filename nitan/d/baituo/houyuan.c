inherit ROOM;

void create()
{
        set("short","後院");
        set("long", @LONG
這裏是一處僻靜的後院，住着少莊主歐陽克的老奶媽張媽。由於
她年歲已高，她已經不幹活了，在這裏靜養。
LONG );
          set("outdoors", "baituo");
          set("exits", ([
                      "southeast" : __DIR__"zhuyuan",
             ]));

          set("objects", ([
                    __DIR__"npc/zhangma" : 1,
            ]));

         set("coor/x", -49980);
        set("coor/y", 20080);
        set("coor/z", 30);
        setup();
         replace_program(ROOM);
}