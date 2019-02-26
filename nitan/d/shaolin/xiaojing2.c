// Room: /d/shaolin/xiaojing2.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "田埂邊");
        set("long", @LONG
轉過山坡只見幾棵果實累累的大棗樹孤零零地栽在田埂賄，上面
掛滿了紅熟的棗子，使人忍不住想摘下幾顆嚐嚐。田裏種着半熟的青
稞麥。西首有三間簡陋的土屋。
LONG );
        set("exits", ([
                "southdown" : __DIR__"xiaojing1",
                "west" : __DIR__"houshan",
        ]));
        set("outdoors", "shaolin");
        setup();
        replace_program(ROOM);
}
