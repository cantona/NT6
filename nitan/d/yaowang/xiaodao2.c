inherit ROOM;

void create()
{
        set("short", "叢林小道");
        set("long", @LONG
這是一條僻靜的叢林小道，小道上滿是枯枝敗葉，踩上去非
常鬆軟，四周靜悄悄的，偶爾傳來幾聲鳥鳴。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "southeast" : __DIR__"xiaodao1",
  "northwest" : __DIR__"xiaodao3",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
