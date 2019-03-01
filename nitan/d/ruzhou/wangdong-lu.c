//Room: /d/ruzhou/wangxi-lu.c
// llm /99/07/

inherit ROOM;

void create()
{
        set("short", "望西路");
        set("long", @LONG
望西路上望西歸，自此出汝州的西城門，便是踏上西去漢中，遠
征西北的大路了。北面就是汝州城的知府衙門，雖然未經什麼修繕，
但是略略掉漆的紅木白牆卻顯現出一番更加威嚴肅穆的感覺。東去是
汝州城中心，這裡也沒有什麼店舖。
LONG
        );

        set("exits", ([
      "north" : __DIR__"yamen-damen",
                "south" : __DIR__"yingbin-lou1",
                "west" : __DIR__"ximen",
                "east" : __DIR__"ruzhou",
        ]));

        set("objects", ([
        ]));

        set("outdoors", "ruzhou");
        setup();
        replace_program(ROOM);
}


