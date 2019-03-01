inherit ROOM;

void create()
{
        set("short", "翔鶴門");
        set("long", @LONG
這是通往天龍寺後寺的門戶。你低頭看看地上，只見銅門檻早已
被踩踏得□亮，足見此寺香火之盛了。抬頭向南可以望見點蒼山聳立
雲天。
LONG );
        set("outdoors","tianlongsi");
        set("exits", ([
            "south": __DIR__"wulege",
            "north": __DIR__"wujingge",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}