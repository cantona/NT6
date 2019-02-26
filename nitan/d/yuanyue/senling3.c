// This program is a part of NITAN MudLIB

inherit ROOM;
void create()
{
        set("short", "松林盡頭"); 
        set("long", @LONG
終於走到了松林盡頭，你不禁長長舒了口氣，可是愈往前走，四
周草木漸稀，惡石猙獰，路旁依稀可以看見幾具小動物的骸骨，一種
刺鼻的惡臭幾乎讓人忍不住想要嘔吐，撥開蔓藤，前方赫然便是個漆
黑的山洞，令人眩暈的腥氣迎面撲來。
LONG );
        set("outdoors", "wansong");
        set("type","forest");
        set("exits",([
                "south":__DIR__"senling2",
                "north":__DIR__"senling4",
        ]) );
        set("objects", ([
                __DIR__"obj/skeleton" : 1,
        ]) ); 
        set("coor/x",-620);
        set("coor/y",260);
        set("coor/z",80);
        setup();
        replace_program(ROOM);
}    
