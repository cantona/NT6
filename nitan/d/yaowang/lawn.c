inherit ROOM;

void create()
{
        set("short", "草地");
        set("long", @LONG
這裡是一片青青的草地，邊上稀稀落落的長著幾根青竹，周
圍的空氣裡散發著淡淡的草藥香味。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"xiaoyuan",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
