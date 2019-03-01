inherit ROOM;

void create()
{
        set("short", "小院子");
        set("long", @LONG
這裡是一處靜靜的小院，院子裡滿是嫩綠的小草，中間是一
個石桌，上面還擺著沒下玩的棋局，給人一種靜謐、悠閒的感覺，
很難想象出這裡就是唐門弟子沒事也不願意來的唐家堡藥莊。
LONG
        );
        set("exits", ([ /* sizeof() == 3 */
  "north" : __DIR__"yz_ku",
  "south" : __DIR__"yz_door",
  "east" : __DIR__"yz_tang",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
