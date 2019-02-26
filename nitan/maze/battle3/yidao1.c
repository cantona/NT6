inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "城外驛道");
        set("long", @LONG
這裏是通往大宋京城的驛道，由於連年來戰火不止，顯得格外地
荒涼，不時有來往的馬匹飛奔而過，濺起一土塵煙，沿途不時有土匪
大盜出現，還是少作停留的好。
LONG );
        set("outdoors", "xiangyang");
        set("no_fly",1);

        set("exits", ([
                "east"  : "/d/xiangyang/westgate2", 
                "west"  : __DIR__"yidao2",
        ]));
        setup();
}
