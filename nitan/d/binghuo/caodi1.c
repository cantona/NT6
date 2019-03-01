// Room: /binghuo/caodi1.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "草地");
        set("long", @LONG
一片平緩的草地一直沿岸延伸，間或有些許巖石露出地面，挺立
浪頭，忍受海潮千年來不盡的沖刷。一些叫不出名目的大鳥小獸在草
叢中出沒，十分自在地遊嬉。西去有一片沙灘。
LONG );
        set("outdoors", "binghuo");
        set("no_clean_up", 0);
        set("exits", ([
                "west"      : __DIR__"haitan",
                "northeast" : __DIR__"caodi2",
        ]));
        setup();
        replace_program(ROOM);
}
