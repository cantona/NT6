inherit ROOM;

void create()
{
        set("short", "小竹橋");
        set("long", @LONG
這是一座青竹小橋，清澈見底的溪水從橋下流過，對岸是一
排竹子紮成的籬笆，兩隻小鳥落在上面歌唱，來到這裏讓人有一
種超然脱俗的感覺。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"xiaoyuan",
  "south" : __DIR__"door",
]));

        set("outdoors", "yaowang");

        setup();
        replace_program(ROOM);
}
