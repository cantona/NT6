
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "兵營");
        set("long", @LONG
這裡是兵營，密密麻麻到處都是官兵，有的在武將的指揮下列隊操
練，有的獨自在練功，有的坐著、躺著正在休息。南牆下坐著主帥，不
動聲色地尋視著四周。看到你進來，他們全都向你包圍了過來，形勢看
來不太妙。
LONG);

        
        set("exits", ([
                "north" : __DIR__"bingyingdamen",
        ]));
 setup();
        replace_program(ROOM);
}        
