inherit ROOM;

void create()
{
        set("short", "廚房");
        set("long", @LONG
這裡是鐵掌幫內的廚房。你的正面是一個大爐灶，幾乎佔去了一大半的
房間。灶上留有很多火眼，可同時做很多種菜。幾位幫中的廚子正在來回忙
碌著。整間屋內彌漫著各種飯菜的香味，聞了讓人垂涎欲滴。
LONG    );
        set("exits", ([
                "south" : __DIR__"zoulang-3",
        ]));

        set("objects", ([ 
                __DIR__"obj/hsnr" : 2,
                __DIR__"obj/ruzhu" : 1,
                __DIR__"obj/fan" : 2,
        ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}