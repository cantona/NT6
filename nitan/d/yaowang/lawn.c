inherit ROOM;

void create()
{
        set("short", "草地");
        set("long", @LONG
這裏是一片青青的草地，邊上稀稀落落的長着幾根青竹，周
圍的空氣裏散發着淡淡的草藥香味。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"xiaoyuan",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
