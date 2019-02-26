#include <room.h>

inherit ROOM;

void create()
{
        set("short", "過道");
        set("long", @LONG
這裏是一條寬敞的過道，用青磚鋪就的地面非常整潔，兩旁
是漢白玉的雕花欄杆，分外的華貴，每隔幾步就有一個僕人打扮
的青年侍立兩旁，看起來都身具武功，絕非等閒之輩。置身於此，
讓人感覺到莫名的壓力。
LONG
        );
        set("exits", ([ /* sizeof() == 3 */
  "north" : __DIR__"xiaolu1",
  "east" : __DIR__"hqdoor",
  "west" : __DIR__"tulu2",
]));

        set("outdoors", "yaowang");
        setup();
        create_door("north", "木門", "south", DOOR_CLOSED);
}
