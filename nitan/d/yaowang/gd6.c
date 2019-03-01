inherit ROOM;

void create()
{
        set("short", "過道");
        set("long", @LONG
這裡是一條寬敞的過道，用青磚舖就的地面非常整潔，兩旁
是漢白玉的雕花欄桿，分外的華貴，每隔幾步就有一個僕人打扮
的青年侍立兩旁，看起來都身具武功，絕非等閒之輩。置身于此，
讓人感覺到莫名的壓力。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "northeast" : __DIR__"gd5",
  "southwest" : __DIR__"gd7",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
