#include <ansi.h>
inherit ROOM;

int is_chat_room() { return 1; }

void create() {
        set("short", "比武看台");
        set("long", @LONG
這裏是比武場的看台。現在已經是人聲鼎沸，羣雄議論紛紛，都在猜
測誰能折桂。四周有些桌子。
LONG
    );
        set("exits", ([
                "down"  : "/d/huashan/houzhiwangyu",
        ]));
        
        set("no_fight", 1);
        set("outdoors", "huashan" ); 

        setup();
}

