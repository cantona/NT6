 inherit ROOM;
void create()
{
        set("short", "山路"); 
        set("long", @LONG
這是條崎嶇的山路，路旁雜草不生，生跡罕見，惡石猙獰，路旁
依稀可以看見幾具小動物的骸骨，一種刺鼻的惡臭幾乎讓人忍不住想
要嘔吐，撥開蔓籐，前方赫然便是個漆黑的山洞，令人幾乎眩暈的腥
氣迎面撲來。
LONG );
        set("outdoors", "wansong");
        set("type","mountain");
        set("exits",([
                "south":__DIR__"senling3",
                "west":__DIR__"shangou",
                "northeast":__DIR__"dongkou",
        ]) ); 
        set("objects",([
                CLASS_D("mojiao/tongtuo") : 1,
        ]));

        set("coor/x",-620);
        set("coor/y",270);
        set("coor/z",80);
        setup();
        replace_program(ROOM);
}      
