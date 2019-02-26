inherit ROOM;

void create()
{
        set("short", "草地");
        set("long", @LONG
這裏是林中的一片空地，四周被參天的古鬆環抱着，當中是一片
綠油油的草地。草地中央地上有一個拳頭大小的小洞，旁邊丈許方圓
寸草不生，露出紅褐色的土壤。四周一片寂靜，草地上陽光明媚，但
你的心情卻一也不輕鬆，這裏該不會有什麼危險吧？
LONG );
        set("outdoors", "wudujiao");

        set("exits", ([
                "south" : __DIR__"sl7",
        ]));

        if (random(3) > 1)
                set("objects", ([
                        "/clone/beast/jinshewang" : 1,
                ]));

        setup();
        replace_program(ROOM);
}