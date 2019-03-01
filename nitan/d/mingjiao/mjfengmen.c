// Room: /d/mingjiao/mjfengmen.c
// Date: Java 97/05/11

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "竹林");
        set("long", @LONG
這是一條碎石舖成的小道，曲曲折折地通向前方。兩邊是密密的
竹林。這裡人跡罕至，惟聞足底叩擊路面，僧敲木魚聲，道頌道德經，
微風吹拂竹葉，如簌簌禪唱。令人塵心為之一滌，真是絕佳的禪修所
在。
LONG );
    set("exits", ([
        "northwest" : __DIR__"mjsimen1",
        "southeast" : __DIR__"mjfengmen1",
    ]));
    set("outdoors", "mingjiao");
    set("no_clean_up", 0);
    setup();
    replace_program(ROOM);
}
