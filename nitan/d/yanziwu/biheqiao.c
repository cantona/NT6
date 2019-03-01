//ROOM: /d/yanziwu/biheqiao.c

inherit ROOM;

void create()
{
        set("short", "碧荷橋");
        set("long", @LONG
密密匝匝的荷葉上面，一條曲曲折折的小橋通向水中的一片小洲，
洲上花紅柳綠，似乎別有洞天。
LONG );
        set("outdoors", "yanziwu");
        set("exits", ([
            "west" : __DIR__"huayuan",
            "east" : __DIR__"tingxiang",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}