inherit ROOM;
 
void create()
{
        set("short", "洞口");
        set("long", @LONG
這是一條後山上的一個小山洞。洞口很小，但能容一個人鑽進去。裏
面黑黝黝的什麼也看不見。
LONG );
        set("exits", ([
                "west"   : __DIR__"road3",
                "enter"  : __DIR__"dong",
        ]));
        set("outdoors", "taohua");
 
        set("coor/x", 8990);
        set("coor/y", -2930);
        set("coor/z", 0);
        setup();
}