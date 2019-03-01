// yanxiadong.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "煙霞洞");
        set("long", @LONG
據說站在山頭，清晨觀看山村繚繞炊煙，傍晚仰望藍天彩霞，景
色優美，故稱“煙霞”。洞口兩旁有精美的“觀音”和“大勢至菩薩”
洞內兩壁的天然巖穴裡有各代的石刻。往東是下山的路。西邊是去龍
井。
LONG);
        set("exits", ([
                "west"     : __DIR__"shanlu5",
                "eastdown" : __DIR__"shuiledong",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 780);
	set("coor/y", -2110);
	set("coor/z", 40);
	setup();
        replace_program(ROOM);
}