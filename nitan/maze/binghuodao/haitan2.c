inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "海灘");
        set("long",
"這裡是冰火島西岸海灘，海浪拍打著海邊巨石。周圍是一望無\n"
"際的大海，東邊傳來陣陣巨大的聲響，地動山搖一般，似乎島上的\n"
"火山在不斷地噴發，釋放出巨大的能量。\n"
);
        set("exits", ([ 
                "north"    : __DIR__"shadi",
        ]));
        
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裡
        set("binghuo", 1);           // 表示在冰火島    
        set("outdoors", "battle4");
        
        set("objects", ([
        ]));
        
        set("no_fight", 1);
        
        setup();
}
