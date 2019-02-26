inherit ROOM;
 
void create()
{
        set("short", "洞口");
        set("long", @LONG
這是一條後山上的一個小山洞。洞口很小，但能容一個人
鑽進去。裏面黑黝黝的什麼也看不見。
LONG);
        set("exits", ([
            "west"   : __DIR__"road4",
            "enter"  : __DIR__"dong",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taohua");
        setup();
        replace_program(ROOM);
}