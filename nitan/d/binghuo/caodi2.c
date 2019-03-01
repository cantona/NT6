// Room: /binghuo/caodi1.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "草地");
        set("long", @LONG
一片平緩的草地一直沿岸延伸，間或有些許巖石露出地面，挺立
浪頭，忍受海潮千年來不盡的沖刷。一些叫不出名目的大鳥小獸在草
叢中出沒，十分自在地遊嬉。西北望去，遠遠可以看到高高的火山口
正在噴煙吐火。
LONG );
        set("outdoors", "binghuo");
        set("no_clean_up", 0);
        set("exits", ([
                "southwest"  : __DIR__"caodi1",
                "northwest"  : __DIR__"yuanye1",
        ]));
        setup();
        replace_program(ROOM);
}
