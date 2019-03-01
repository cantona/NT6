#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW"馬軍大營"NOR);
        set("long", @LONG
這裡就是「大宋」馬軍大營，營內軍馬嘶鳴，塵土飛揚，為了應
對蒙古精銳的騎兵，大宋早已開始了騎兵的訓練，較場中央指揮的將
領雖然早已汗流浹背，可是絲毫也不敢懈怠。
LONG );
        set("train", "cavalry");  
        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */
               "west"  :   __DIR__"sying1",
        ]));

        set("objects", ([

        ]));

        setup();
}
