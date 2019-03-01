// Room: /tangmen/ndajie1.c

inherit ROOM;

void create()
{
        set("short", "南大街");
        set("long",
"這就是唐家鎮的南大街了，向東西兩頭延伸。西邊就是回春堂的分店\n"
"了，平常賣一些個跌打藥。唐門自己是不賣藥，因為祖上傳下來的。只可\n"
"自己人用。東邊人去的就少一些了，大多是匆匆而來，急急忙忙而去。是\n"
"什麼地方呢，自己一進去就知道了。\n"
);
        set("outdoors", "tangmen");
        set("no_clean_up", 0);
        set("exits", ([ 
                "west"  : __DIR__"hcfdian",
                "north" : __DIR__"zhongxin",
                "east"  : __DIR__"tmbingqi",
        ]));

        setup();
        replace_program(ROOM);
}
