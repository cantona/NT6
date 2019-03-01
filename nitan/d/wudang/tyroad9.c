inherit ROOM;

void create()
{
        set("short", "桃園小路");
        set("long", @LONG
眼前豁然開朗，你輕鬆地走在桃園邊的小路上。兩邊是桃樹林，
樹上盛開著粉紅的桃花，紅雲一片，望不到邊。不時有蜜蜂「嗡嗡」
地飛過，消失在在花叢中；幾只猴子在樹上互相追逐著，嘰嘰喳喳地
爭搶桃子。
LONG );
        set("outdoors", "wudang");
        set("exits", ([
                "east" : __DIR__"tyroad10",
                "west" : __DIR__"tyroad8",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -300);
        set("coor/y", -310);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}