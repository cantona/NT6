// shidao1.c

inherit ROOM;

void create()
{
        set("short", "石道");
        set("long", @LONG
一路往北行，中間僅有一道寬約五尺的石道，兩邊石壁如牆，一
路上都有日月教徒模樣的人物在走動，對往來的路人都嚴密監視。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
            "east" : __DIR__"guang",
            "north" : __DIR__"shidao2",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}