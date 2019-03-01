#include <ansi.h>
#include <room.h>
inherit RIVER;

void create()
{
        set("short", "泊舟塢");
        set("long", @LONG
此處一片蘆葦，茭白叢中現出一座船塢，大小船只依次排開。菱
花荷葉叢中條條水道 (river)四通八達，由此可乘船離開燕子塢。湖
面系著尾小舟。北面遠遠望過去有個梯子。
LONG );
        //set("arrive_room", "/d/yanziwu/hupan");
        set("to", __DIR__"hupan");
        set("exits", ([
                "east"      : __DIR__"pindi",
                "northdown" : __DIR__"muti",
        ]));
        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));

        set("outdoors", "yanziwu");
        replace_program(RIVER);
}
